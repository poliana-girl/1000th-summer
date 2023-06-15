#include <iostream>

#include "../../libs/AudioFile/AudioFile.h"
#include "tools.h"

AudioFile<double> leftShift(AudioFile<double> wav, int shift) {
  // find length of given audio file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  for (auto &channel : buffer)
    channel.resize(numSamples);

  uint64_t b;
  for (int i = 0; i < numSamples; i++) {
    for (int channel = 0; channel < numChannels; channel++) {
      double a = wav.samples[channel][i];
      // std::cout << a << std::endl;
      std::memcpy(&b, &a, sizeof(uint64_t));
      b = b << shift;
      std::memcpy(&a, &b, sizeof(uint64_t));
      // std::cout << a << std::endl;
      buffer[channel][i] = a;
    }
  }

  wav.setAudioBuffer(buffer);
  wav = normalize(wav);
  return wav;
}