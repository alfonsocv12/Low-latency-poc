#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

class UdpSend {
    private:
        int port = 8080;
        char bufferSize;
        std::vector<float> waveValues;
        int sockfd;
        socklen_t len;

    public:
        UdpSend(char bufferSize);
        void send(float sample);
};
