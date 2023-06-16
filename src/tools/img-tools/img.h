#ifndef IMG_H
#define IMG_H

#include "../../../libs/AudioFile/AudioFile.h"
#include "../../../libs/CImg/CImg.h"

using namespace cimg_library;

std::vector<CImg<double>> wavToImage(AudioFile<double> wav);
AudioFile<double> imageToWav(std::vector<CImg<double>> imgs);

AudioFile<double> blur(AudioFile<double> wav, double intensity);
AudioFile<double> test(AudioFile<double> wav);
AudioFile<double> laplaceTransform(AudioFile<double> wav);

#endif