#include <iostream>
#include "../../libs/AudioFile/AudioFile.h"
#include <queue>
#include <chrono>

std::vector<AudioFile<double>> transientFinder(AudioFile<double> wav, int numFrags) {
    auto time0 = std::chrono::high_resolution_clock::now();
    std::cout << "finding transients of file..." << std::endl;
    
    //info about wav file
    int numSamples = wav.getNumSamplesPerChannel();
    int numChannels = wav.getNumChannels();
    int simGrain = 44100 / 20; //transient similarity grain. not enabled right now

    int offset = 44100 / 30000; //rate of change offset: samples[offset] - 
    int istep = 44100 / 10;     //how often to check for rates of change

    int posTracker = 0;
    int fragProg = 0;
    int start;
    int end;
    

    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(numChannels);
    for (auto &channel : buffer)
        channel.resize(numSamples);
    
    std::priority_queue<std::pair<double, int>> q0; //store array of ROC
    std::priority_queue<std::pair<double, int>> q1;

    std::priority_queue<std::pair<double, int>> q[16]; // store priority queues of channels

    /*
    GAME PLAN:
        - find ROC between all samples
        - test if ROC is within a certain threshold (i.e. changes fast enough to be considered a transient)
            - within threshold -> create an AudioBuffer starting at the sample that continues until the next transient
            (the number of transients returned is depends on argument numFrags. the duration of all the transients combined should equal the initial audio file)
    */
    

    //find rate of change between samples
    std::cout << "getting rate of change between samples..." << std::endl;
    for (int channel = 0; channel < numChannels; channel++) {
        for (int i = 0; i < numSamples && i + 1 + offset < numSamples; i += istep) {
            //std::cout << "getting rate of change between " << i << " and " << i + 1 + offset << std::endl;
            buffer[channel][i / istep] = wav.samples[channel][i + 1 + offset] - wav.samples[channel][i];
            //std::cout << buffer[channel][i / istep] << std::endl;
        }
    }
    
    //sort rates of change into max-heap priority queue
    std::cout << "sorting rates of change..." << std::endl;

    // for (auto channel : buffer) {
    //     std::priority_queue<std::pair<double, int>> qChannel;
    //     for (auto sample : channel) {
    //         qChannel.push()
    //     }
    // }

    for (int i = 0; i < numSamples / istep; i++ ) {   
        //std::cout << buffer[0][i] << std::endl;
        q0.push(std::pair<double, int>(buffer[0][i], i));
        q1.push(std::pair<double, int>(buffer[1][i], i));
    }


    
    //sort indexes in min-heap priority queue
    std::vector<int> idxHolder;

    for (int i = 0; i < numFrags; ++i) {
        double kv0 = q0.top().first;
        int ki0 = q0.top().second;
        idxHolder.push_back(ki0);
        //std::cout << "channel 0: index[" << ki0 << "] = " << kv0 << std::endl;
        q0.pop();

        double kv1 = q1.top().first;
        int ki1 = q1.top().second;
        idxHolder.push_back(ki1);
        //std::cout << "channel 1: index[" << ki1 << "] = " << kv1 << std::endl;
        q1.pop();
    }

    std::sort(idxHolder.begin(), idxHolder.end());
    idxHolder.erase( unique(idxHolder.begin(), idxHolder.end()), idxHolder.end());
    for(auto i : idxHolder) {
        std::cout << "idxHolder value: " << i << std::endl;
    }

    std::vector<AudioFile<double>> frags;

    //TODO: fix this loop so that it actually sends the right values
    while ( fragProg < numFrags) {
        
        //test for first transient point. if it's the first index and the first value isn't 0...
        if (posTracker == 0 && idxHolder[posTracker] != 0 && fragProg == 0) {
            start = 0;
            end = (int) idxHolder[posTracker];
        } else if (fragProg == numFrags - 1) {
            start = (int) idxHolder[posTracker];
            end = numSamples;
        } else {
            start = (int) idxHolder[posTracker];
            end = (int) idxHolder[posTracker + 1];
        }

        // if (end - start < simGrain) {
        //     continue;
        // }

        //std::cout << "frag #" <<fragProg << " starts at " << start << " and ends at " << end << std::endl;
        AudioFile<double>::AudioBuffer tempbuf;
        tempbuf.resize(2);

        //std::cout << "inserting samples..." << std::endl;
        for (int channel = 0; channel < 2; channel++) {
            tempbuf[channel].insert(tempbuf[channel].begin(), wav.samples[channel].begin() + start, wav.samples[channel].begin() + end);
            tempbuf[channel].resize(end - start);
        }

        //std::cout << "creating new audio buffer" << std::endl;
        AudioFile<double> temp;
        temp.setAudioBuffer(tempbuf);
        frags.push_back(temp);
        tempbuf.clear();

        if(start != 0) {
            posTracker++;
        }
        fragProg++;
    }
    
    auto time1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time1 - time0);
    float secs = (float) duration.count() / 1000;
    std::cout << "Time taken by function: " << secs << " seconds" << std::endl;
    //wav.setAudioBuffer(buffer);
    return frags;
}