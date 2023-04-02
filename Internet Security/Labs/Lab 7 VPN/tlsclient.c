#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>

#define PORT_NUMBER 55555
#define BUFF_SIZE 2000

#define CHK_SSL(err) if ((err) < 1) { ERR_print_errors_fp(stderr); exit(2); }
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); exit(1); }
#define CA_DIR "ca_client" 

int err;
struct sockaddr_in peerAddr;

int createTunDevice() {
   int tunfd;
   struct ifreq ifr;
   memset(&ifr, 0, sizeof(ifr));

   ifr.ifr_flags = IFF_TUN | IFF_NO_PI;  

   tunfd = open("/dev/net/tun", O_RDWR);
   ioctl(tunfd, TUNSETIFF, &ifr);       

   return tunfd;
}

// Message received from the TUN interface.
// Need to encrypt and send it using the TLS interface.
void tunSelected(int tunfd, SSL* ssl) {
    int err;
    int  lenReceivedTun;
    char buff[BUFF_SIZE];

    printf("Got a packet from TUN\n");
    bzero(buff, BUFF_SIZE);

    // READ FROM TUN
    lenReceivedTun = read(tunfd, buff, BUFF_SIZE);

    char tlsBuffer[4];
    memset(tlsBuffer, 0, 4);

    // convert int to char array
    unsigned short int length = htons(lenReceivedTun);
    tlsBuffer[0] = length & 0xff;
    tlsBuffer[1] = (length >> 8) & 0xff;
    tlsBuffer[2] = (length >> 16) & 0xff;
    tlsBuffer[3] = (length >> 24) & 0xff;

    // encrypt and send using SSL commands
    err = SSL_write(ssl, tlsBuffer, 4);
    CHK_SSL(err);
    err = SSL_write(ssl, buff, strlen(buff));
    CHK_SSL(err);
}

// Message received from the TLS interface (encrypted data).
// Need to decrypt and send to the TUN interface.
void socketSelected (int tunfd, SSL* ssl) {
    int err;
    int  lenReceivedSsl;
    char buff[BUFF_SIZE];
    bzero(buff, BUFF_SIZE);
    char* buffPntr = buff;

    printf("Got a packet from the tunnel\n");

    char tlsBuffer[4];
    memset(tlsBuffer, 0, 4);
    err = SSL_read(ssl, tlsBuffer, 4);
    CHK_SSL(err);

    unsigned short int lengthRead = ((tlsBuffer[3] << 24) &0xFF000000) | ((tlsBuffer[2] << 16) &0xFF0000) | ((tlsBuffer[1] << 8) &0xFF00) | (tlsBuffer[0] & 0xFF);
    
    unsigned short int lengthFormatted = ntohs(lengthRead);
    unsigned short int lengthCopy = lengthFormatted;
    while(lengthCopy > 0){
        int lenTemp = SSL_read(ssl, buffPntr, lengthCopy);
        buffPntr = buffPntr + lenTemp;
        lengthCopy = lengthCopy - lenTemp;
    }

    err = write(tunfd, buff, lengthFormatted);
    CHK_SSL(err);
}

int verify_callback(int preverify_ok, X509_STORE_CTX *x509_ctx)
{
    char  buf[300];

    X509* cert = X509_STORE_CTX_get_current_cert(x509_ctx);
    X509_NAME_oneline(X509_get_subject_name(cert), buf, 300);
    printf("subject= %s\n", buf);

    if (preverify_ok == 1) {
       printf("Verification passed.\n");
    } else {
       int err = X509_STORE_CTX_get_error(x509_ctx);
       printf("Verification failed: %s.\n",
                    X509_verify_cert_error_string(err));
    }
}

SSL* setupTLSClient(const char* hostname)
{
    // Step 0: OpenSSL library initialization 
   // This step is no longer needed as of version 1.1.0.
   SSL_library_init();
   SSL_load_error_strings();
   SSLeay_add_ssl_algorithms();

   SSL_METHOD *meth;
   SSL_CTX* ctx;
   SSL* ssl;

   meth = (SSL_METHOD *)TLSv1_2_method();
   ctx = SSL_CTX_new(meth);

   SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
   if(SSL_CTX_load_verify_locations(ctx,NULL, CA_DIR) < 1){
	printf("Error setting the verify locations. \n");
	exit(0);
   }
   ssl = SSL_new (ctx);

   X509_VERIFY_PARAM *vpm = SSL_get0_param(ssl); 
   X509_VERIFY_PARAM_set1_host(vpm, hostname, 0);

   return ssl;
}


int setupTCPClient(const char* hostname, int port)
{
   struct sockaddr_in server_addr;

   // Get the IP address from hostname
   struct hostent* hp = gethostbyname(hostname);

   // Create a TCP socket
   int sockfd= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   // Fill in the destination information (IP, port #, and family)
   memset (&server_addr, '\0', sizeof(server_addr));
   memcpy(&(server_addr.sin_addr.s_addr), hp->h_addr, hp->h_length);
//   server_addr.sin_addr.s_addr = inet_addr ("10.0.2.14"); 
   server_addr.sin_port   = htons (port);
   server_addr.sin_family = AF_INET;

   // Connect to the destination
   connect(sockfd, (struct sockaddr*) &server_addr,
           sizeof(server_addr));

   return sockfd;
}


int main(int argc, char *argv[])
{
   char *hostname = "redamontivpnserver.com";
   int port = 443;

   int tunfd;
   tunfd  = createTunDevice();
   printf("tun%d\n", tunfd);

   if (argc > 1) hostname = argv[1];
   if (argc > 2) port = atoi(argv[2]);

   /*----------------TLS initialization ----------------*/
   SSL *ssl   = setupTLSClient(hostname);

   /*----------------Create a TCP connection ---------------*/
   int sockfd = setupTCPClient(hostname, port);

   /*----------------TLS handshake ---------------------*/
   SSL_set_fd(ssl, sockfd);
   int err = SSL_connect(ssl); CHK_SSL(err);
   printf("SSL connection is successful\n");
   printf ("SSL connection using %s\n", SSL_get_cipher(ssl));

   /*----------------Send/Receive data --------------------*/
   // Enter the main loop
   while (1) {
        fd_set readFDSet;

        FD_ZERO(&readFDSet);
        FD_SET(sockfd, &readFDSet);
        FD_SET(tunfd, &readFDSet);
        select(FD_SETSIZE, &readFDSet, NULL, NULL, NULL);

        if (FD_ISSET(tunfd, &readFDSet)) tunSelected(tunfd, ssl);
        if (FD_ISSET(sockfd, &readFDSet)) socketSelected(tunfd, ssl);
   } // end while
}

