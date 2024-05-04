#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_INPUT_O 110

int main() {
    int sockfd;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "ERROR: creating an endpoint for communication" << std::endl;
    }

    int port = 5432;
    const char *host = "127.0.0.1";
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, host, &(serv_addr.sin_addr));

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        std::cerr << "ERROR: refreshing socket" << std::endl;
    }

    struct sockaddr_in cli_addr;
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(5433);
    cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) < 0) {
        std::cerr << "ERROR: binding name to socket" << std::endl;
    }
    
    const char *msg = "Hello, server!";
    int n = sendto(sockfd, msg, strlen(msg) , 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if ( n < 0)
    {
        std::cout << "ERROR: sending a message on the socket" << std::endl;
    }
}
