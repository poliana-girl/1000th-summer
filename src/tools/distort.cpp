#include "../../libs/AudioFile/AudioFile.h"
#include <iostream>

AudioFile<double> distort(AudioFile<double> wav, double threshold) {
  std::cout << "distorting file at threshold " << threshold << "..."
            << std::endl;

  // info about wav file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  for (auto channel : buffer)
    channel.resize(numSamples);

  // replace any values that go over the threshold with the threshold!
  for (int i = 0; i < numSamples; i++) {
    for (int channel = 0; channel < 2; channel++) {
      if (wav.samples[channel][i] > threshold) {
        buffer[channel][i] = threshold;
      } else if (wav.samples[channel][i] < -threshold) {
        buffer[channel][i] = -threshold;
      } else {
        buffer[channel][i] = wav.samples[channel][i];
      }
    }
  }

  wav.setAudioBuffer(buffer);
  return wav;
}