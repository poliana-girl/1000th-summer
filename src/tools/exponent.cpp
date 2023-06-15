#include "../../libs/AudioFile/AudioFile.h"
#include <cmath>
#include <iostream>

AudioFile<double> exponent(AudioFile<double> wav, double power) {

  // info about wav file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();
  int sampleRate = wav.getSampleRate();

  // rate of change offset; ROC = sample[x + offset] - sample[x]
  int offset = sampleRate / 30000;

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer = wav.samples;

  for (int channel = 0; channel < numChannels; channel++) {
    for (int i = 0; i < numSamples && i + 1 + offset < numSamples; i++) {
      buffer[channel][i] = pow(buffer[channel][i], power);
    }
  }

  wav.setAudioBuffer(buffer);

  return wav;
}