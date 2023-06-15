
#include "../../../libs/AudioFile/AudioFile.h"
#include "../../../libs/CImg/CImg.h"

#ifdef _WIN32
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "Shell32.lib")
#endif

using namespace cimg_library;

std::vector<CImg<double>> wavToImage(AudioFile<double> wav) {
  std::vector<CImg<double>> imgs;

  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  int width = 3000;
  int height = numSamples / width;

  for (int channel = 0; channel < numChannels; channel++) {
    CImg<double> img(width, height, 1, 1, 0);
    int i = 0;
    for (CImg<double>::iterator it = img.begin(); it < img.end(); ++it) {

      if (i > numSamples)
        break;
      *it = (wav.samples[channel][i] + 1.0) / 2.0 * 255.0;
      i++;
    }
    imgs.push_back(img);
  }

  // img.fill(100);

  return imgs;
}