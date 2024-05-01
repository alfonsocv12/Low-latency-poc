#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1" // Assuming server is running on localhost
#define PORT 12345
#define MAX_BUFFER_SIZE 20

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[MAX_BUFFER_SIZE];

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        std::cerr << "Error: Unable to create socket." << std::endl;
        return EXIT_FAILURE;
    }

    // Set server address
    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        std::cerr << "Error: Invalid address or address not supported." << std::endl;
        close(sockfd);
        return EXIT_FAILURE;
    }

    while (true) {
        std::cout << "Server running on port " << PORT << std::endl;

        // Receive response from server
        ssize_t recvBytes = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE, MSG_WAITALL,
                                    nullptr, nullptr);
        if (recvBytes == -1) {
            std::cerr << "Error: Unable to receive response." << std::endl;
            close(sockfd);
            return EXIT_FAILURE;
        }

        buffer[recvBytes] = '\0'; // Null-terminate the received data

        // Display response from server
        std::cout << "Response from server: " << buffer << std::endl;
    }

    close(sockfd);

    return EXIT_SUCCESS;
}
