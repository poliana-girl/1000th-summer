#include <iostream>
#include "../../libs/AudioFile/AudioFile.h"


AudioFile<double> normalize(AudioFile<double> wav) {
    std::cout << "normalizing file..." << std::endl;

    std::vector<double> maxAmps;
    
    int numSamples = wav.getNumSamplesPerChannel();

    double normalFactor = 0;
    for (auto channel : wav.samples) {
        for (auto sample : channel) {
            if (std::abs(sample) > normalFactor) {
                normalFactor = std::abs(sample);
                //std::cout << normalFactor << std::endl;
            }
        }
    }

    // create new audio buffer
    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(2);
    buffer[0].resize(numSamples);
    buffer[1].resize(numSamples);

    for (int channel = 0; channel < 2; channel++) {
        for (int i = 0; i < numSamples; i++) {
            buffer[channel][i] = wav.samples[channel][i] / normalFactor;
        }
    }

    wav.setAudioBuffer(buffer);
    return wav;
}