#include "udpSend.h"

struct sockaddr_in servaddr;

UdpSend::UdpSend(char bufferSize) {
    this->bufferSize = bufferSize;
    this->waveValues = {};

    if ( (this->sockfd = socket(AF_INET, SOCK_DGRAM, 0) < 0)) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(this->port); 
    servaddr.sin_addr.s_addr = INADDR_ANY;
}

void UdpSend::send(float sample) {
    char value[this->bufferSize];

    std::snprintf(value, sizeof value, "%f", sample);

    sendto(this->sockfd, (const char *)value, strlen(value), MSG_CONFIRM,
            (const struct sockaddr*) &servaddr, sizeof(servaddr));
}
