#include <iostream>

#include "fftw3.h"

#include "../../libs/AudioFile/AudioFile.h"
#include "tools.h"

#define REAL 0
#define IMAG 1

void place(fftw_complex* signal, std::vector<double> source, int numSamples) {

    int i;
    for (i = 0; i < numSamples; ++i) {
        signal[i][REAL] = source[i];
    }
}

std::vector<AudioFile<double>> fastFourierTransform(AudioFile<double> wav) {
  std::cout << "computing fast fourier transform of file..." << std::endl;

  std::vector<AudioFile<double>> wavs;
  
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  if(numChannels != 2) {
    std::cout << "file must be 2 channels!" << std::endl;
    exit(0);
  }

  AudioFile<double>::AudioBuffer buffer;
    buffer.resize(numChannels);

  for (auto &channel : buffer)
    channel.resize(numSamples);

  for (int channel = 0; channel < numChannels; channel++) {
    fftw_complex *signal;
    fftw_complex *result;

    signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * numSamples);
    result = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * numSamples);


    place(signal, wav.samples[channel], numSamples);

    fftw_plan plan = fftw_plan_dft_1d(numSamples, signal, result, FFTW_FORWARD, FFTW_ESTIMATE);
    
    fftw_execute(plan);

    

    for (int i = 0; i < numSamples; i++) {
      buffer[channel][i] = result[REAL][i];
    }

    fftw_destroy_plan(plan);
    fftw_free(signal); fftw_free(result);

  }

  wav.setAudioBuffer(buffer);
    wav = normalize(wav);
    wavs.push_back(wav);
  
  return wavs;
}
