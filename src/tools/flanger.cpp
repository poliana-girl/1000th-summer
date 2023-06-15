#include "../../libs/AudioFile/AudioFile.h"
#include <iostream>

AudioFile<double> flanger(AudioFile<double> wav, size_t delay) {

  // info about wav file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();
  int sampleRate = wav.getSampleRate();

  delay = delay * sampleRate / 1000; // ms to samples convertion

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  for (auto &channel : buffer)
    channel.resize(numSamples);

  // iterate over each channel and sample
  for (int channel = 0; channel < numChannels; channel++) {
    for (int i = 0; i < numSamples && i + delay < numSamples; i++) {
      if ((channel + 1) % 2 == 0)
        buffer[channel][i] = wav.samples[channel][i + delay];
      else
        buffer[channel][i] = wav.samples[channel][i];
    }
  }

  wav.setAudioBuffer(buffer);
  return wav;
}