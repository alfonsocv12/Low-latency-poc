#include <RtAudio.h>
#include <iostream>

enum DeviceType { INPUT = 0, OUTPUT = 1 };

class DeviceEntity {
  public:
    DeviceEntity(DeviceType deviceType, int deviceId) {
        RtAudio dac;

        RtAudio::DeviceInfo deviceInfo = dac.getDeviceInfo(deviceId);

        this->id = deviceId;
        this->name = deviceInfo.name;
        this->channels = deviceType == DeviceType::INPUT
                             ? deviceInfo.inputChannels
                             : deviceInfo.outputChannels;
        this->sampleRate = deviceInfo.preferredSampleRate;
    }

    int id;
    std::string name;
    int channels;
    int sampleRate;
    // Input device only
    int channelId;
};
