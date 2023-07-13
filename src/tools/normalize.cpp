#include "../../libs/AudioFile/AudioFile.h"
#include <iostream>

AudioFile<double> normalize(AudioFile<double> wav) {
  std::cout << "normalizing file..." << std::endl;

  std::vector<double> maxAmps;

  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  double normalFactor = 0;
  for (auto channel : wav.samples) {
    for (auto sample : channel) {
      if (std::abs(sample) > normalFactor) {
        normalFactor = std::abs(sample);
      }
    }
  }

  // create new audio buffer
  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  for (auto &channel : buffer)
    channel.resize(numSamples);

  for (int channel = 0; channel < numChannels; channel++) {
    for (int i = 0; i < numSamples; i++) {
      buffer[channel][i] = wav.samples[channel][i] / normalFactor;
    }
  }

  wav.setAudioBuffer(buffer);
  return wav;
}