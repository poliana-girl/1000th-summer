
#include "../../../libs/AudioFile/AudioFile.h"
#include "../../../libs/CImg/CImg.h"

using namespace cimg_library;

AudioFile<double> imageToWav(CImg<double> img) {

    int width = img.width();
    int height = img.height();
    int numSamples = width * height;

    
    int numChannels = 1;

    // create new audio buffer
    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(numChannels);

    for (auto &channel : buffer) 
        channel.resize(numSamples);

    int channel = 0;
    int i = 0;
    for (CImg<double>::iterator it = img.begin(); it < img.end(); ++it) {
        
        if (i > numSamples) break;
        buffer[channel][i] = 2.0/255 * *it - 1;
        i++;
    }

    AudioFile<double> wav;
    wav.setAudioBuffer(buffer);
    return wav;
}