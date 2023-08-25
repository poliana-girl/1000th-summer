#ifndef TOOLS_H
#define TOOLS_H
#include "../../libs/AudioFile/AudioFile.h"

AudioFile<double> distort(AudioFile<double> wav, double threshold);
AudioFile<double> normalize(AudioFile<double> wav);
AudioFile<double> monoToStereo(AudioFile<double> wav);
AudioFile<double> flanger(AudioFile<double> wav, size_t delay);
AudioFile<double> scatter(AudioFile<double> wav, int splitSize);
std::vector<AudioFile<double>> transientFinder(AudioFile<double> wav,
                                               int numFrags);
AudioFile<double> derivative(AudioFile<double> wav, size_t loop);
AudioFile<double> multiply(AudioFile<double> wav1, AudioFile<double> wav2);
AudioFile<double> integral(AudioFile<double> wav, size_t loop);
AudioFile<double> exponent(AudioFile<double> wav, double power);
AudioFile<double> hypotenuse(AudioFile<double> wav, size_t loop);
AudioFile<double> softClip(AudioFile<double> wav, double mult);
AudioFile<double> modulo(AudioFile<double> wav1, AudioFile<double> wav2);
AudioFile<double> randGen(double length);
AudioFile<double> minimum(AudioFile<double> wav1, AudioFile<double> wav2);
AudioFile<double> maximum(AudioFile<double> wav1, AudioFile<double> wav2);
AudioFile<double> leftShift(AudioFile<double> wav, int shift);
AudioFile<double> sortAscending(AudioFile<double> wav, double length);
AudioFile<double> rawData(std::ifstream file);
std::vector<AudioFile<double>> fastFourierTransform(AudioFile<double> wav);
AudioFile<double> weirdFn(AudioFile<double> wav);
AudioFile<double> bang(AudioFile<double> wav);
AudioFile<double> epic(AudioFile<double> wav);
AudioFile<double> inverseFastFourierTransform(AudioFile<double> wav1, AudioFile<double> wav2);
AudioFile<double> newBlur(AudioFile<double> wav, double sd);

// TEMPLATE FUNCTION

// AudioFile<double> template(AudioFile<double> wav) {

//     //find length of given audio file
//     int numSamples = wav.getNumSamplesPerChannel();
//     int numChannels = wav.getNumChannels();

//     // create new audio buffer
//     AudioFile<double>::AudioBuffer buffer;
//     buffer.resize(numChannels);

//     for (auto &channel : buffer)
//         channel.resize(numSamples);

//     for (int i = 0; i < numSamples; i++) {
//         for (int channel = 0; channel < numChannels; channel++) {
//             buffer[channel][i] = wav.samples[channel][i];
//         }
//     }

//     wav.setAudioBuffer(buffer);
//     return wav;
// }

#endif