#include "udpSend.h"

UdpSend::UdpSend(int bufferSize) {
    this->bufferSize = bufferSize;
    this->waveValues = {}; 
}

void UdpSend::send(float sample) {
    if (this->waveValues.size() < bufferSize) {
        this->waveValues.push_back(sample);

        return;
    }

    system("nb");
}
