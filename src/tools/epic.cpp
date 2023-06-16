#include <cmath>

#include "../../libs/AudioFile/AudioFile.h"

#include "tools.h"

void yep(std::vector<double> &tree) {

  for (int i = 0; i < tree.size(); i++) {
    if (tree[i] > 100)
        return;
  }

  std::vector<double> backtree = tree;
  reverse(backtree.begin(), backtree.end());

  double product;
  for (int i = 0; i < tree.size(); i++) {
    product = tree[i] + backtree[i];
    tree[i] = product;
  }

  yep(tree);

  for (int i = 0; i < tree.size(); i++) {
    product = tree[i] + backtree[i];
    tree[i] = product + sin(i);
  }
}

AudioFile<double> epic(AudioFile<double> wav) {

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
    yep(wav.samples[channel]);
  }

  wav = normalize(wav);
  return wav;
}