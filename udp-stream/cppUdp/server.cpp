#include <iostream>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <unistd.h>

#define BUFFER_SIZE 20

void data_transfer(int sockfd) {
    struct sockaddr_in cli_addr;
    socklen_t addr_size = sizeof(cli_addr);
    char buffer[BUFFER_SIZE];

    memset(buffer, 0, sizeof(buffer));
    
    std::cout << "Waiting for a message..." << std::endl;
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cli_addr, &addr_size);
    if (n < 0) {
        std::cerr << "ERROR: receiving a message from socket" << std::endl;
    }

    std::cout << "Received: " << buffer << std::endl;
}

int main() {
    int port = 5432;

    int sockfd;

    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "ERROR: creating an endpoint for communication" << std::endl;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        std::cerr << "ERROR: refreshing socket" << std::endl;
    }

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "ERROR: binding name to socket" << std::endl;
    }

    data_transfer(sockfd); 

    close(sockfd);
}
