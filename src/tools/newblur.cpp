#include "../../libs/AudioFile/AudioFile.h"
#include "tools.h"
#include <algorithm>
#include <cmath>
#include <iostream>

AudioFile<double> newBlur(AudioFile<double> wav, double sd) {
  std::cout << "blurring file..." << std::endl;

  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;

  buffer.resize(numChannels);
  for (auto &channel : buffer)
    channel.resize(numSamples);

  for (int channel = 0; channel < numChannels; channel++) {
    for (int i = 0; i < numSamples; i++) {
      buffer[channel][i] = 1 / sqrt(2 * M_PI * pow(sd, 2)) * pow(M_E, -wav.samples[channel][i] / 2 * pow(sd, 2));
      
      //wav1.samples[channel][i] 
    }
  }

  wav.setAudioBuffer(buffer);

  return wav;
}