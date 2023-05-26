#ifndef TOOLS_H
#define TOOLS_H
#include "../../libs/AudioFile/AudioFile.h"

AudioFile<double> distort(AudioFile<double> wav, double threshold);
AudioFile<double> normalize(AudioFile<double> wav);
AudioFile<double> monoToStereo(AudioFile<double> wav);
AudioFile<double> phaser(AudioFile<double> wav);
AudioFile<double> scatter(AudioFile<double> wav, int splitSize);
std::vector<AudioFile<double>> transientFinder(AudioFile<double> wav, int numFrags);

#endif