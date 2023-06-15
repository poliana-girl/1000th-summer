
#include "../../../libs/AudioFile/AudioFile.h"
#include "../../../libs/CImg/CImg.h"

using namespace cimg_library;

AudioFile<double> imageToWav(std::vector<CImg<double>> imgs) {

  int width = imgs[0].width();
  int height = imgs[0].height();
  int numSamples = width * height;

  int numChannels = 2;

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  for (auto &channel : buffer)
    channel.resize(numSamples);

  for (int channel = 0; channel < numChannels; channel++) {
    int i = 0;
    for (CImg<double>::iterator it = imgs[channel].begin();
         it < imgs[channel].end(); ++it) {
      if (i > numSamples)
        break;
      buffer[channel][i] = 2.0 / 255 * *it - 1;
      i++;
    }
  }

  AudioFile<double> wav;
  wav.setAudioBuffer(buffer);
  return wav;
}