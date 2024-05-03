#include "udpSend.h"

UdpSend::UdpSend(char bufferSize) {
    this->bufferSize = bufferSize;
    this->waveValues = {};

    if ( (this->sockfd = socket(AF_INET, SOCK_DGRAM, 0) < 0)) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&this->servaddr, 0, sizeof(servaddr));
    this->servaddr.sin_family = AF_INET; 
    this->servaddr.sin_port = htons(this->server_port); 
    inet_pton(AF_INET, this->host, &(this->servaddr.sin_addr));

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        std::cerr << "ERROR: refreshing socket" << std::endl;
    }

    struct sockaddr_in cli_addr;
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(this->client_port);
    cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) < 0) {
        std::cerr << "ERROR: binding name to socket" << std::endl;
    }
}

void UdpSend::send(float sample) {
    char value[this->bufferSize];

    std::snprintf(value, sizeof value, "%f", sample);
    

    const char *msg = "Hello, server!";
    int n = sendto(this->sockfd, msg, strlen(msg), MSG_CONFIRM,
            (struct sockaddr *) &this->servaddr, sizeof(this->servaddr));
    if ( n < 0) {
        std::cout << "ERROR: sending a message on the socket" << std::endl;
    }
}
