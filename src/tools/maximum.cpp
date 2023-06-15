#include "../../libs/AudioFile/AudioFile.h"
#include "tools.h"
#include <algorithm>
#include <iostream>

AudioFile<double> maximum(AudioFile<double> wav1, AudioFile<double> wav2) {

  int numSamples1 = wav1.getNumSamplesPerChannel();
  int numChannels1 = wav1.getNumChannels();

  int numSamples2 = wav2.getNumSamplesPerChannel();
  int numChannels2 = wav2.getNumChannels();

  int bufSamples = std::min(numSamples1, numSamples2);
  int bufChannels = std::min(numChannels1, numChannels2);

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;

  buffer.resize(bufChannels);
  for (auto &channel : buffer)
    channel.resize(bufSamples);

  for (int channel = 0; channel < bufChannels; channel++) {
    for (int i = 0; i < bufSamples; i++) {
      buffer[channel][i] =
          std::max(wav1.samples[channel][i], wav2.samples[channel][i]);
    }
  }

  AudioFile<double> wav;
  wav.setAudioBuffer(buffer);

  return wav;
}