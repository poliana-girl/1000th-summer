#include <algorithm>
#include <cmath>
#include <iostream>

#include "../../libs/AudioFile/AudioFile.h"
#include "tools.h"

AudioFile<double> integral(AudioFile<double> wav, size_t loop) {
  std::cout << "finding " << loop << "th integral of file..." << std::endl;

  // info about wav file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();
  int sampleRate = wav.getSampleRate();

  int offset =
      sampleRate /
      30000; // rate of change offset; ROC = sample[x + offset] - sample[x]

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer = wav.samples;

  double area;

  for (int r = 0; r < loop; r++) {
    std::cout << "iteration #" << r << std::endl;
    for (int channel = 0; channel < numChannels; channel++) {
      area = 0;
      for (int i = 0; i < numSamples && i + 1 + offset < numSamples; i++) {
        area += wav.samples[channel][i];
        buffer[channel][i] = area;
      }
    }
  }

  wav.setAudioBuffer(buffer);
  wav = normalize(wav);

  return wav;
}