#include "../../libs/AudioFile/AudioFile.h"

#include "tools.h"

void mix(std::vector<double> &tree) {

  if (tree.size() < 44100)
    return;

  std::vector<double> twos;
  std::vector<double> threes;
  std::vector<double> fives;

  for (int i = 0; i < tree.size(); i++) {
    if (i % 2 == 0) {
      twos.push_back(tree[i]);
      continue;
    }
    if (i % 3 == 0) {
      threes.push_back(tree[i]);
      continue;
    }
    if (i % 5 == 0) {
      fives.push_back(tree[i]);
      continue;
    }
  }

  mix(twos);
  mix(threes);
  mix(fives);

  for (int i = 0; i + 3 < tree.size() && i + 3 < twos.size() &&
                  i + 3 < threes.size() && i + 3 < fives.size();
       i++) {
    tree[i] = twos[i + 1] + threes[i + 2] + fives[i + 3];
  }
}

AudioFile<double> bang(AudioFile<double> wav) {
  std::cout << "banging file..." << std::endl;

  // find length of given audio file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  int newLength = numSamples;

  for (auto &channel : buffer)
    channel.resize(newLength);

  for (int channel = 0; channel < numChannels; channel++) {
    mix(wav.samples[channel]);
  }

  wav = normalize(wav);
  return wav;
}