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
    if (this->waveValues.size() < bufferSize) {
        this->waveValues.push_back(sample);

        return;
    }
    
    char waveChar[this->bufferSize + 1];

    for (size_t i = 0; i < this->waveValues.size(); ++i) {
        waveChar[i] = static_cast<char>(this->waveValues[i]);
    }

    sendto(this->sockfd, (const char *)waveChar, strlen(waveChar),
            0, (const struct sockaddr*) &servaddr,
            sizeof(servaddr));

    this->waveValues.clear();
}
