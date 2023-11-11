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

void place_ifft(fftw_complex* signal, std::vector<double> real_source, std::vector<double> imaginary_source, int numSamples) {

    int i;
    for (i = 0; i < numSamples; ++i) {
        signal[i][REAL] = real_source[i];
        signal[i][IMAG] = imaginary_source[i];
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

  AudioFile<double>::AudioBuffer real_buffer;
    real_buffer.resize(numChannels);
  for (auto &channel : real_buffer)
    channel.resize(numSamples);

  AudioFile<double>::AudioBuffer imaginary_buffer;
    imaginary_buffer.resize(numChannels);
  for (auto &channel : imaginary_buffer)
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
      real_buffer[channel][i] = result[REAL][i];
      imaginary_buffer[channel][i] = result[IMAG][i];
    }

    fftw_destroy_plan(plan);
    fftw_free(signal); fftw_free(result);

  }

  AudioFile<double> real_wav;
  AudioFile<double> imaginary_wav;

  real_wav.setAudioBuffer(real_buffer);
  real_wav = normalize(real_wav);

  imaginary_wav.setAudioBuffer(imaginary_buffer);
  imaginary_wav = normalize(imaginary_wav);

  wavs.push_back(real_wav);
  wavs.push_back(imaginary_wav);
   
  return wavs;
}


AudioFile<double> inverseFastFourierTransform(AudioFile<double> real_wav, AudioFile<double> imaginary_wav) {
  
  AudioFile<double> ifft_wav;

  if(real_wav.getNumSamplesPerChannel() != imaginary_wav.getNumSamplesPerChannel()) {
    std::cout << "different number of samples for the wavs! implement this behavior later..." << std::endl;
    exit(-1);
  }

  int numChannels = real_wav.getNumChannels();
  int numSamples = real_wav.getNumSamplesPerChannel();

  AudioFile<double>::AudioBuffer ifft_buffer;
    ifft_buffer.resize(numChannels);
  for (auto &channel : ifft_buffer)
    channel.resize(numSamples);

  for (int channel = 0; channel < numChannels; channel++) {
    fftw_complex *signal;
    fftw_complex *result;

    signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * numSamples);
    result = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * numSamples);

    place_ifft(signal, real_wav.samples[channel], imaginary_wav.samples[channel], numSamples);
    

    fftw_plan plan = fftw_plan_dft_1d(numSamples, signal, result, FFTW_BACKWARD, FFTW_ESTIMATE);
    
    fftw_execute(plan);

    

    for (int i = 0; i < numSamples; i++) {
      ifft_buffer[channel][i] = result[REAL][i];
    }

    fftw_destroy_plan(plan);
    fftw_free(signal); fftw_free(result);

  }

  ifft_wav.setAudioBuffer(ifft_buffer);
  ifft_wav = normalize(ifft_wav);

  return ifft_wav;
}