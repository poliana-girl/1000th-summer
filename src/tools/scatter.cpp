#include "../../libs/AudioFile/AudioFile.h"
#include <filesystem>
#include <random>

// TODO: make splitSize be seconds, not samples
AudioFile<double> scatter(AudioFile<double> wav, int splitSize) {
  std::cout << "scattering file with split size of " << splitSize << "..."
            << std::endl;

  // obtain a time-based seed
  std::cout << "obtaining random seed..." << std::endl;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine e(seed);

  // find length of given audio file
  std::cout << "finding length of audio file..." << std::endl;
  int numSamples = wav.getNumSamplesPerChannel();

  // find number of splits to be made
  int numSplits = numSamples / splitSize;

  // create new audio buffer
  std::cout << "creating new buffer..." << std::endl;
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(2);

  // create shuffled vector with all splits
  std::cout << "creating vector to randomize splits..." << std::endl;
  std::vector<int> splitVec(numSplits);
  std::iota(splitVec.begin(), splitVec.end(), 0);
  std::shuffle(splitVec.begin(), splitVec.end(), e);

  // randomly add sections of the song into the buffer
  std::cout << "adding randomized splits to new buffer..." << std::endl;
  for (int channel = 0; channel < 2; channel++) {
    for (int i = 0; i < numSplits; i++) {
      buffer[channel].insert(
          buffer[channel].begin() + i * splitSize,
          wav.samples[channel].begin() + splitVec[i] * splitSize,
          wav.samples[channel].begin() + (splitVec[i] + 1) * splitSize);
    }
  }

  buffer[0].resize(numSamples);
  buffer[1].resize(numSamples);
  wav.setAudioBuffer(buffer);
  return wav;
}