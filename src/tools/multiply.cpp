#include <iostream>
#include <algorithm>
#include "../../libs/AudioFile/AudioFile.h"

AudioFile<double> multiply(AudioFile<double> wav1, AudioFile<double> wav2) {

    int numSamples1 = wav1.getNumSamplesPerChannel();
    int numChannels1 = wav1.getNumChannels();
    int sampleRate1 = wav1.getSampleRate();

    int numSamples2 = wav2.getNumSamplesPerChannel();
    int numChannels2 = wav2.getNumChannels();
    int sampleRate2 = wav2.getSampleRate();

    int bufSamples = std::min(numSamples1, numSamples2);
    int bufChannels = std::min(numChannels1, numChannels2);
    
    // create new audio buffer
    AudioFile<double>::AudioBuffer buffer;
    
    buffer.resize(bufChannels);
    for (auto &channel : buffer)
        channel.resize(bufSamples);

    
    for (int channel = 0; channel < bufChannels; channel++) {
        for (int i = 0; i < bufSamples; i++) {
            //std::cout << "multiplying #" << i << "\r";
            buffer[channel][i] = wav1.samples[channel][i] * wav2.samples[channel][i];
        }
    }
    
    // for ( auto channel : buffer) {
    //     std::cout << *std::max(channel.begin(), channel.end());
    // }

    AudioFile<double> wav;
    wav.setAudioBuffer(buffer);

    return wav;
}