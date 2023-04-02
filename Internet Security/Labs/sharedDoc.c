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