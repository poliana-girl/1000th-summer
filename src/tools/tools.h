#ifndef TOOLS_H
#define TOOLS_H
#include "../../libs/AudioFile/AudioFile.h"

AudioFile<double> distort(AudioFile<double> wav, double threshold);
AudioFile<double> normalize(AudioFile<double> wav);
AudioFile<double> monoToStereo(AudioFile<double> wav);
AudioFile<double> flanger(AudioFile<double> wav, size_t delay);
AudioFile<double> scatter(AudioFile<double> wav, int splitSize);
std::vector<AudioFile<double>> transientFinder(AudioFile<double> wav, int numFrags);
AudioFile<double> derivative(AudioFile<double> wav);
AudioFile<double> derivative(AudioFile<double> wav, size_t loop);
AudioFile<double> multiply(AudioFile<double> wav1, AudioFile<double> wav2);

#endif