#include <iostream>
#include <cmath>
#include "../../libs/AudioFile/AudioFile.h"

AudioFile<double> softClip(AudioFile<double> wav, double mult) {
    std::cout << "increasing loudness by factor of " << mult << " and soft clipping file..." << std::endl;
    
    //find length of given audio file
    int numSamples = wav.getNumSamplesPerChannel();
    
    // create new audio buffer
    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(2);
    buffer[0].resize(numSamples);
    buffer[1].resize(numSamples);

    for (int i = 0; i < numSamples; i++) {   
        for (int channel = 0; channel < 2; channel++){
            buffer[channel][i] = tanh(wav.samples[channel][i] * mult);
        }
    }

    wav.setAudioBuffer(buffer);
    return wav;
}