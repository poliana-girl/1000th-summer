#include "../../../libs/AudioFile/AudioFile.h"
#include "../../../libs/CImg/CImg.h"

#include "img.h"

// img = img.blur(1, 1, 1, 3, true);

AudioFile<double> blur(AudioFile<double> wav, double intensity) {
  std::cout << "blurring file with intensity " << intensity << "..."
            << std::endl;

  // find length of given audio file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  for (auto &channel : buffer)
    channel.resize(numSamples);

  auto imgs = wavToImage(wav);

  for (auto &img : imgs) {
    img = img.blur(intensity, intensity, intensity, intensity, true);
  }

  return imageToWav(imgs);
}