#include <iostream>
#include <cmath>

#include "../../libs/AudioFile/AudioFile.h"
#include "tools.h"

unsigned int factorial(unsigned int n) {
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

double nthDerivative(int n, std::vector<double> dataVector, int point) {
    int deltaX = 40;

    if (n == 0) {
        std::cout << "this should not happen!" << std::endl;
    }

    if (n == 1) {
        return (dataVector[point + deltaX] - dataVector[point]) / deltaX;
    } else {
        std::vector<double> derivVector;
        derivVector.resize(dataVector.size());
        for (int i; i  + deltaX < dataVector.size(); i++) {
            derivVector[i] = (dataVector[i + deltaX] - dataVector[i]) / deltaX;
        }

        nthDerivative(n - 1, derivVector, point);
    }
}

AudioFile<double> taylorSeriesApproximation(AudioFile<double> wav, int maxTaylorSeriesDepth) {
  std::cout << "computing taylor series at depth " << maxTaylorSeriesDepth << "..."
            << std::endl;

  // find length of given audio file
  int numSamples = wav.getNumSamplesPerChannel();
  std::cout << numSamples << std::endl;
  int numChannels = wav.getNumChannels();

//   int midpoint = numSamples / 2 - 1;

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  for (auto &channel : buffer)
    channel.resize(numSamples);

    for (int channel = 0; channel < numChannels; channel++) {
        for (int sample = 0; sample < numSamples; sample++) {
            buffer[channel][sample] = 0;
            
            for (int currentTaylorSeriesDepth = 1; currentTaylorSeriesDepth < maxTaylorSeriesDepth + 1; currentTaylorSeriesDepth++) {
                // a = sample
                // x = sample
                // n = currentTaylorSeriesDepth

                buffer[channel][sample] += nthDerivative(currentTaylorSeriesDepth, wav.samples[channel], sample) / factorial(currentTaylorSeriesDepth - 1) * pow(sample, currentTaylorSeriesDepth - 1);
            }   
            std::cout << sample << "\r";
        }
    }
  

  wav.setAudioBuffer(buffer);
  wav = normalize(wav);
  return wav;
}