#include "../../libs/AudioFile/AudioFile.h"
#include <iostream>

AudioFile<double> derivative(AudioFile<double> wav, size_t loop) {

  // info about wav file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();
  int sampleRate = wav.getSampleRate();

  // rate of change offset; ROC = sample[x + offset] - sample[x]
  int offset = sampleRate / 30000;

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer = wav.samples;

  // can loop for as long as you want!
  for (int r = 0; r < loop; r++) {
    std::cout << "iteration #" << r << std::endl;
    for (int channel = 0; channel < numChannels; channel++) {
      for (int i = 0; i < numSamples && i + 1 + offset < numSamples; i++) {
        buffer[channel][i] =
            buffer[channel][i + 1 + offset] - buffer[channel][i] / (1 + offset);
      }
    }
  }

  wav.setAudioBuffer(buffer);

  return wav;
}