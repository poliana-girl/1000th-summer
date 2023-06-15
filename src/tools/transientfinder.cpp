#include "../../libs/AudioFile/AudioFile.h"
#include <iostream>
#include <queue>

std::vector<AudioFile<double>> transientFinder(AudioFile<double> wav,
                                               int numFrags) {
  std::cout << "finding transients of file..." << std::endl;

  // info about wav file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();
  int sampleRate = wav.getSampleRate();

  // how often to check for rates of change in original file
  int istep = sampleRate / 10;
  // rate of change offset; ROC = sample[x + offset] - sample[x]
  int offset = sampleRate / 30000;

  // rate of change buffer
  AudioFile<double>::AudioBuffer rocBuffer;
  // size of each channel in rocBuffer
  int bufChannelSize = numSamples / istep;

  // stores each channel's rates of change and index
  std::priority_queue<std::pair<double, int>> sortedBuf[numChannels];
  // sample position in file of max rate of change in channel of sortedBuf
  int sortedTopIdx;
  // stores sample positions of the highest rates of change
  std::vector<int> transHolder;

  // variables used in finding fragments
  int posTracker = 0; // tracks the position of transHolder
  int fragProg = 0;   // tracks current fragment
  int start;          // start of current fragment (a position (index) in wav)
  int end;            // end of current fragment   (a position (index) in wav)

  // stores produced fragments of original file
  std::vector<AudioFile<double>> frags;

  //=============================================================

  rocBuffer.resize(numChannels);
  for (auto &channel : rocBuffer)
    channel.resize(bufChannelSize);

  // find rate of change between samples
  for (int channel = 0; channel < numChannels; channel++) {
    for (int i = 0; i < numSamples && i + 1 + offset < numSamples; i += istep) {
      rocBuffer[channel][i / istep] =
          wav.samples[channel][i + 1 + offset] - wav.samples[channel][i];
    }
  }

  // sort rates of change
  for (int channel = 0; channel < numChannels; channel++) {
    for (int i = 0; i < numSamples / istep; i++) {
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
  transHolder.erase(unique(transHolder.begin(), transHolder.end()),
                    transHolder.end());

  // parse sample positions as fragments
  while (fragProg < numFrags) {
    AudioFile<double> temp;
    AudioFile<double>::AudioBuffer tempbuf;
    tempbuf.resize(numChannels);

    // starting condition: first fragment starts at sample 0
    if (posTracker == 0 && transHolder[posTracker] != 0 && fragProg == 0) {
      start = 0;
      end = transHolder[posTracker];
    }
    // ending condition: last fragment ends at last sample of file
    else if (fragProg == numFrags - 1) {
      start = transHolder[posTracker];
      end = numSamples;
    }
    // default condition: any other fragment starts at a sample in transHolder
    // and ends at the next sample
    else {
      start = transHolder[posTracker];
      end = transHolder[posTracker + 1];
    }

    // put fragment in audio file
    for (int channel = 0; channel < numChannels; channel++) {
      tempbuf[channel].insert(tempbuf[channel].begin(),
                              wav.samples[channel].begin() + start,
                              wav.samples[channel].begin() + end);
      tempbuf[channel].resize(end - start);
    }
    temp.setAudioBuffer(tempbuf);
    frags.push_back(temp);

    // don't move onto the next sample position if this is the first fragment
    if (start != 0)
      posTracker++;
    fragProg++;
    tempbuf.clear();
  }
  return frags;
}