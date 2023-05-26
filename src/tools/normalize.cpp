#include <iostream>
#include "../../libs/AudioFile/AudioFile.h"


AudioFile<double> normalize(AudioFile<double> wav) {
    std::cout << "normalizing file..." << std::endl;

    std::vector<double> maxAmps;
    
    //find length of given audio file
    int numSamples = wav.getNumSamplesPerChannel();

    for (int channel = 0; channel < 2; channel++) {
        maxAmps.push_back(*std::max_element(wav.samples[channel].begin(), wav.samples[channel].end()));
        maxAmps.push_back(std::abs(*std::min_element(wav.samples[channel].begin(), wav.samples[channel].end())));
    }

    double normalFactor = *std::max_element(maxAmps.begin(), maxAmps.end());

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