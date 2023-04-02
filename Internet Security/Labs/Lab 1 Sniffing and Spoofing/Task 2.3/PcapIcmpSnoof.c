#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pcap.h>

/* ethernet headers are always exactly 14 bytes */
#define SIZE_ETHERNET 14

/* Ethernet addresses are 6 bytes */
#define ETHER_ADDR_LEN	6

/* Ethernet header */
struct ethernetheader {
        u_char  ether_dhost[ETHER_ADDR_LEN];    /* destination host address */
        u_char  ether_shost[ETHER_ADDR_LEN];    /* source host address */
        u_short ether_type;                     /* IP? ARP? RARP? etc */
};

/* IP Header */
struct ipheader {
  unsigned char      iph_ihl:4, //IP header length
                     iph_ver:4; //IP version
  unsigned char      iph_tos; //Type of service
  unsigned short int iph_len; //IP Packet length (data + header)
  unsigned short int iph_ident; //Identification
  unsigned short int iph_flag:3, //Fragmentation flags
                     iph_offset:13; //Flags offset
  unsigned char      iph_ttl; //Time to Live
  unsigned char      iph_protocol; //Protocol type
  unsigned short int iph_chksum; //IP datagram checksum
  struct  in_addr    iph_sourceip; //Source IP address
  struct  in_addr    iph_destip;   //Destination IP address
};

/* ICMP Header  */
struct icmpheader {
  unsigned char icmp_type; // ICMP message type
  unsigned char icmp_code; // Error code
  unsigned short int icmp_chksum; //Checksum for ICMP Header and data
  unsigned short int icmp_id;     //Used for identifying request
  unsigned short int icmp_seq;    //Sequence number
};


// calculate the checksum of the ICMP packet header
unsigned short in_cksum (unsigned short *buf, int length)
{
   unsigned short *w = buf;
   int nleft = length;
   int sum = 0;
   unsigned short temp=0;

   /*
    * The algorithm uses a 32 bit accumulator (sum), adds
    * sequential 16 bit words to it, and at the end, folds back all
    * the carry bits from the top 16 bits into the lower 16 bits.
    */
   while (nleft > 1)  {
       sum += *w++;
       nleft -= 2;
   }

   /* treat the odd byte at the end, if any */
   if (nleft == 1) {
        *(u_char *)(&temp) = *(u_char *)w ;
        sum += temp;
   }

   /* add back carry outs from top 16 bits to low 16 bits */
   sum = (sum >> 16) + (sum & 0xffff);  // add hi 16 to low 16
   sum += (sum >> 16);                  // add carry
   return (unsigned short)(~sum);
}

/*************************************************************
  Given an IP packet, send it out using a raw socket.
**************************************************************/
void send_raw_ip_packet(struct ipheader* ip)
{
    struct sockaddr_in dest_info;
    int enable = 1;

    // Step 1: Create a raw network socket.
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if(sock < 0){
        printf("Error opening raw socket\n");
    }

    // Step 2: Set socket option.
    setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &enable, sizeof(enable));

    // Step 3: Provide needed information about destination.
    dest_info.sin_family = AF_INET;
    dest_info.sin_addr = ip->iph_destip;

    // Step 4: Send the packet out.
    sendto(sock, ip, ntohs(ip->iph_len), 0, (struct sockaddr *)&dest_info, sizeof(dest_info));
    close(sock);
}

// upon receiving a packet, call this function.
// The function will determine the protocol within the IP packet.
// If it is an ICMP packet, it will trigger a spoofed response to the
// source ICMP request machine.
void got_packet(u_char* args, const struct pcap_pkthdr* header, const u_char* packet)
{
    struct ethernetheader* eth = (struct ethernetheader*)packet;

    if (ntohs(eth->ether_type) == 0x0800) { // 0x0800 is IP type
        struct ipheader* ip = (struct ipheader*)(packet + SIZE_ETHERNET);
        int size_ip = ip->iph_ihl * 4;

        printf("       From: %s\n", inet_ntoa(ip->iph_sourceip));
        printf("         To: %s\n", inet_ntoa(ip->iph_destip));

        /* determine protocol */
        switch (ip->iph_protocol) {
        case IPPROTO_TCP:
            printf("   Protocol: TCP\n");
            return;
        case IPPROTO_UDP:
            printf("   Protocol: UDP\n");
            return;
        case IPPROTO_ICMP:
            printf("   Protocol: ICMP\n");
            
            // decode the ICMP request by casting it to a struct.
            struct icmpheader* icmpReq = (struct icmpheader*)(packet + SIZE_ETHERNET + sizeof(struct ipheader));

            // create a buffer that is the size of the packet
            char buffer[1500];
            memset(buffer, 0, 1500);

            /*********************************************************
            Step 1: Fill in the ICMP header.
            ********************************************************/
            struct icmpheader *icmp = (struct icmpheader *) (buffer + sizeof(struct ipheader));
            icmp->icmp_type = 0; //ICMP Type: 8 is request, 0 is reply.

            // Calculate the checksum for integrity
            icmp->icmp_chksum = 0;
            icmp->icmp_chksum = in_cksum((unsigned short *)icmp, sizeof(struct icmpheader));
			
            // copy the sequence and ID from the received ICMP request.
            icmp->icmp_id = icmpReq->icmp_id;
            icmp->icmp_seq = icmpReq->icmp_seq;

            /*********************************************************
            Step 2: Fill in the IP header.
            ********************************************************/
            struct ipheader *ipNew = (struct ipheader *) buffer;
            ipNew->iph_ver = 4;
            ipNew->iph_ihl = 5;
            ipNew->iph_ttl = 20;
            ipNew->iph_sourceip.s_addr = ip->iph_destip.s_addr; // the destination IP is the source
            ipNew->iph_destip.s_addr = ip->iph_sourceip.s_addr; // the source IP is the destination

            printf("       New From: %s\n", inet_ntoa(ipNew->iph_sourceip));
            printf("       New To: %s\n", inet_ntoa(ipNew->iph_destip));
            
            ipNew->iph_protocol = IPPROTO_ICMP;
            ipNew->iph_len = htons(sizeof(struct ipheader) + sizeof(struct icmpheader));

            /*********************************************************
            Step 3: Finally, send the spoofed packet
            ********************************************************/
            send_raw_ip_packet (ipNew);
            return;
        default:
            printf("   Protocol: others\n");
            return;
        }
    }
}

/******************************************************************
  Spoof an ICMP echo request using an arbitrary source IP Address
*******************************************************************/
int main() {
	
	pcap_t* handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct bpf_program fp;
    char filter_exp[] = "icmp[icmptype] == icmp-echo";
    bpf_u_int32 net;

    // Step 1: Open live pcap session on NIC with name enp0s3
    handle = pcap_open_live("enp0s3", BUFSIZ, 1, 1000, errbuf);

    // Step 2: Compile filter_exp into BPF psuedo-code
    pcap_compile(handle, &fp, filter_exp, 0, net);
    if (pcap_setfilter(handle, &fp) != 0) {
        pcap_perror(handle, "Error:");
        exit(EXIT_FAILURE);
    }

    // Step 3: Capture packets
    pcap_loop(handle, -1, got_packet, NULL);

    pcap_close(handle);   //Close the handle

   return 0;
}
