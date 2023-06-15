#include "../../libs/AudioFile/AudioFile.h"
#include <iostream>

AudioFile<double> monoToStereo(AudioFile<double> wav) {
  std::cout << "converting file from mono to stereo..." << std::endl;

  // find length of given audio file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  if (numChannels == 2) {
    std::cout << "file already has 2 channels!" << std::endl;
    return wav;
  }

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(2);
  buffer[0].resize(numSamples);
  buffer[1].resize(numSamples);

  // iterate over each channel and sample
  for (int i = 0; i < numSamples; i++) {
    buffer[0][i] = wav.samples[0][i];
    buffer[1][i] = wav.samples[0][i];
  }

  wav.setAudioBuffer(buffer);
  return wav;
}