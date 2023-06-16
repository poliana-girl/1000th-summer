#include <cstring>
#include <string>
#include <iostream>

#include "../../../libs/AudioFile/AudioFile.h"
#include "../../../libs/CImg/CImg.h"

#include "img.h"

AudioFile<double> laplaceTransform(AudioFile<double> wav) {
  std::cout << "finding laplace transform of file..." << std::endl;

  // find length of given audio file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  for (auto &channel : buffer)
    channel.resize(numSamples);

  auto imgs = wavToImage(wav);

  const char *test = "yxzc";
  int i = 0;
  for (auto &img : imgs) {
    img = img.laplacian();
    // auto filename = std::to_string(i) + "cool.bmp";
    // img.save(filename.c_str());
    // i++;
  }

  return imageToWav(imgs);
}