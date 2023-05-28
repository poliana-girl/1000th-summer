#include <iostream>
#include "../../libs/AudioFile/AudioFile.h"
#include <queue>
#include <chrono>

//TODO: replace any instances of 44100 with get sample rate
std::vector<AudioFile<double>> transientFinder(AudioFile<double> wav, int numFrags) {
    auto time0 = std::chrono::high_resolution_clock::now();
    std::cout << "finding transients of file..." << std::endl;
    
    // info about wav file
    int numSamples = wav.getNumSamplesPerChannel();
    int numChannels = wav.getNumChannels();
    int sampleRate = wav.getSampleRate();
    
    // constants
    int istep =  sampleRate /    10;                        // how often to check for rates of change in original file
    int offset = sampleRate / 30000;                        // rate of change offset; ROC = sample[x + offset] - sample[x]
    //int simGrain = 44100 / 20;                       // transient similarity grain. not enabled right now

    // rate of change buffer
    AudioFile<double>::AudioBuffer rocBuffer;          // buffer to store rates of fragschange
    int bufChannelSize = numSamples / istep;           // size of each channel in rocBuffer

    // sorting rates of change
    std::priority_queue<std::pair<double, int>>        // stores each channel's rates of change in ascending order,
        sortedBuf[numChannels];                        // along with its original position in the file
    int sortedTopIdx;                                  // sample position in file of max rate of change in channel of sortedBuf
    std::vector<int> transHolder;                      // stores sample positions of the highest rates of change

    // variables used in finding fragments
    int posTracker = 0;                                // tracks the position of transHolder
    int fragProg = 0;                                  // tracks current fragment
    int start;                                         // start of current fragment (a position (index) in wav)
    int end;                                           // end of current fragment   (a position (index) in wav)
    
    std::vector<AudioFile<double>> frags;              // stores produced fragments of original file

    //=============================================================
    
    rocBuffer.resize(numChannels);
    for (auto &channel : rocBuffer)
        channel.resize(bufChannelSize);

    // find rate of change between samples
    std::cout << "getting rate of change between samples..." << std::endl;
    for (int channel = 0; channel < numChannels; channel++) {
        for (int i = 0; i < numSamples && i + 1 + offset < numSamples; i += istep) {
            rocBuffer[channel][i / istep] = wav.samples[channel][i + 1 + offset] - wav.samples[channel][i];
        }
    }
    
    // sort rates of change
    std::cout << "sorting rates of change..." << std::endl;
    for (int channel = 0; channel < numChannels; channel++) {
        for (int i = 0; i < numSamples / istep; i++ ) {
            sortedBuf[channel].push(std::pair<double, int>(rocBuffer[channel][i], i));  
        }
    }

    // sort sample positions of rates of change 
    for (auto &channel : sortedBuf) {
        for (int i = 0; i < numFrags; ++i) {
            sortedTopIdx = channel.top().second;
            transHolder.push_back(sortedTopIdx * istep);
            channel.pop();
        }
    }
    std::sort(transHolder.begin(), transHolder.end());
    transHolder.erase( unique(transHolder.begin(), transHolder.end()), transHolder.end());
 
    // parse sample positions as fragments
    while (fragProg < numFrags) {
        AudioFile<double> temp;
        AudioFile<double>::AudioBuffer tempbuf; tempbuf.resize(numChannels);

        if (posTracker == 0 && transHolder[posTracker] != 0 && fragProg == 0) { // starting condition: first fragment starts at sample 0
            start = 0;
            end = transHolder[posTracker];
        } else if (fragProg == numFrags - 1) {                                  // ending condition: last fragment ends at last sample of file
            start = transHolder[posTracker];
            end = numSamples;
        } else {
            start = transHolder[posTracker];
            end = transHolder[posTracker + 1];                                  // default condition: any other fragment starts at a sample in transHolder and ends at the next sample
        }

        //put fragment in audio file
        for (int channel = 0; channel < numChannels; channel++) {
            tempbuf[channel].insert(tempbuf[channel].begin(), wav.samples[channel].begin() + start, wav.samples[channel].begin() + end);
            tempbuf[channel].resize(end - start);
        }
        temp.setAudioBuffer(tempbuf);
        frags.push_back(temp);

        //don't move onto the next sample position if this is the first fragment
        if(start != 0) posTracker++;
        fragProg++;
        tempbuf.clear();
    }
    
    auto time1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time1 - time0);
    float secs = (float) duration.count() / 1000;
    std::cout << "Time taken by function: " << secs << " seconds" << std::endl;
    return frags;
}