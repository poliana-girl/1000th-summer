#include <iostream>
#include <numeric>
#include <queue>
#include <utility>

#include "../../libs/AudioFile/AudioFile.h"

AudioFile<double> sortAscending(AudioFile<double> wav, double length) {
    
    //find length of given audio file
    int numSamples = wav.getNumSamplesPerChannel();
    int numChannels = wav.getNumChannels();
    int sampleRate = wav.getSampleRate();

    int length_split = sampleRate * length;
    int num_splits = numSamples / length_split;
    
    // create new audio buffer
    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(numChannels);
    
    for (auto &channel : buffer) 
        channel.resize(numSamples);

    // for (int i = 0; i < numSamples; i++) {   
    //     for (int channel = 0; channel < numChannels; channel++) {
    //         buffer[channel][i] = wav.samples[channel][i];
    //     }
    // }

    std::priority_queue<std::pair<double, int>> avgs;
    // for (int channel = 0; channel < numChannels; channel++) {
        int channel = 0;
        for (int split = 0; split < num_splits; split++) {
            double average = std::accumulate( wav.samples[channel].begin() + (split * length_split), wav.samples[channel].begin() + ((split + 1) * length_split), 0.0) / length_split;
            //std::cout << average << std::endl;
            avgs.push(std::make_pair(average, split));
        }
    // }

    for (int i = 0; i < num_splits; i++) {
        int top_split = avgs.top().second;
        //std::cout << avgs.top().first << std::endl;
        buffer[channel].insert(buffer[channel].begin(), wav.samples[channel].begin() + (top_split * length_split), wav.samples[channel].begin() + ((top_split + 1) * length_split));
        buffer[channel].resize(numSamples);
        avgs.pop();
    }



    wav.setAudioBuffer(buffer);
    return wav;
}