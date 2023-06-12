#ifndef IMG_H
#define IMG_H

#include "../../../libs/AudioFile/AudioFile.h"
#include "../../../libs/CImg/CImg.h"

using namespace cimg_library;

CImg<double> wavToImage(AudioFile<double> wav);
AudioFile<double> imageToWav(CImg<double> img);

#endif