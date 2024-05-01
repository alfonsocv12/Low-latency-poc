#include "./main.h"
#include "./deviceEntity.h"
#include "./udpSend/udpSend.h"
#include <iostream>

UdpSend udpSend = UdpSend(8);

SParams setUpSParams(DeviceType deviceType, DeviceEntity device) {
    SParams deviceParameters;
    deviceParameters.deviceId = device.id;
    deviceParameters.nChannels = INPUT_CHANNELS;

    if (deviceType == DeviceType::INPUT) {
        deviceParameters.firstChannel = device.channelId;
    }

    return deviceParameters;
}

int audioCallback(void *outputBuffer, void *inputBuffer,
                  unsigned int nBufferFrames, double streamTime,
                  RtAudioStreamStatus status, void *userData) {
    // Copy input buffer to output buffer
    if (status)
        std::cout << "Stream underflow detected!" << std::endl;

    float *inBuffer = static_cast<float *>(inputBuffer);

    for (unsigned int i = 0; i < nBufferFrames; ++i) {
        float sample = *inBuffer++;

        udpSend.send(sample);

        inBuffer += INPUT_CHANNELS;
    }

    return 0;
}

int main() {
    RtAudio dac;

    DeviceEntity inputDevice(DeviceType::INPUT, INPUT_DEVICE_ID); 
    inputDevice.channelId = INPUT_CHANNEL_ID;

    SParams inputParameters = setUpSParams(DeviceType::INPUT, inputDevice);

    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 256;

    // Set up stream
    try {
        dac.openStream(nullptr, &inputParameters, RTAUDIO_FLOAT32, sampleRate,
                       &bufferFrames, &audioCallback, nullptr);
    } catch (RtAudioError &e) {
        std::cout << "Error opening RtAudio stream: " << e.getMessage()
                  << std::endl;
        exit(1);
    }

    // Start stream
    try {
        dac.startStream();
    } catch (RtAudioError &e) {
        std::cout << "Error starting RtAudio stream: " << e.getMessage()
                  << std::endl;
        exit(1);
    }

    // Keep stream going until user presses a key
    std::cout << "Audio stream running. Send exit to exit" << std::endl;

    while (dac.isStreamRunning()) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") {
            try {
                dac.stopStream();
                dac.closeStream();
            } catch (RtAudioError &e) {
                std::cout << "Error stopping RtAudio stream: " << e.getMessage()
                          << std::endl;
                exit(1);
            }
        }
    }

}
