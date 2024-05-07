#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>

#if defined(__MACOSX_CORE__)
    #include <arpa/inet.h>
#endif

#define SERVER_IP "127.0.0.1" // Assuming server is running on localhost
#define PORT 5432
#define MAX_BUFFER_SIZE 24

int main() {
    int sockfd;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "ERROR: creating an endpoint for communication" << std::endl;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        std::cerr << "ERROR: refreshing socket" << std::endl;
    }

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "ERROR: binding name to socket" << std::endl;
    }

    while (true) {
        char buffer[MAX_BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));

        struct sockaddr_in cli_addr;
        socklen_t addr_size = sizeof(cli_addr);

        int n = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE,
                        0, (struct sockaddr *)&cli_addr, &addr_size);
        if (n < 0) {
            std::cerr << "ERROR: receiving a message from socket" << std::endl;
        }
        
        float bufferValue = std::atof(buffer);
        std::cout << "Received: " << buffer << std::endl;
        std::cout << "Received as float: " << bufferValue << std::endl;
    }

    close(sockfd);
}
