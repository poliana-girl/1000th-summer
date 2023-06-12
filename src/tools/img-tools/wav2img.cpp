
#include "../../../libs/AudioFile/AudioFile.h"
#include "../../../libs/CImg/CImg.h"

using namespace cimg_library;

CImg<double> wavToImage(AudioFile<double> wav) {

    int numSamples = wav.getNumSamplesPerChannel();

    int width = 3000;
    int height = numSamples / width;

    CImg<double> img(width, height, 1, 1, 0);

    int channel = 0;
    int i = 0;
    for (CImg<double>::iterator it = img.begin(); it < img.end(); ++it) {
        
        if (i > numSamples) break;
        *it = (wav.samples[channel][i] + 1.0) / 2.0 * 255.0;
        i++;
    }

    //img.fill(100);

    return img;
}