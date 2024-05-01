#include <iostream>
#include <vector>

class UdpSend {
    private:
        int bufferSize;
        std::vector<float> waveValues;

    public:
        UdpSend(int bufferSize);
        void send(float sample);
};
