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

void place_inverse(fftw_complex* signal, std::vector<double> source_real, std::vector<double> source_imag, int numSamples) {
  for (int i = 0; i < numSamples; ++i) {
        signal[i][REAL] = source_real[i];
        signal[i][IMAG] = source_imag[i];
    }
}

std::vector<AudioFile<double>> fastFourierTransform(AudioFile<double> wav) {
  std::cout << "computing fast fourier transform of file..." << std::endl;

  std::vector<AudioFile<double>> wavs;
  
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  // if(numChannels != 2) {
  //   std::cout << "file must be 2 channels!" << std::endl;
  //   exit(0);
  // }

  AudioFile<double>::AudioBuffer buffer_real;
    buffer_real.resize(numChannels);

  for (auto &channel : buffer_real)
    channel.resize(numSamples);

  AudioFile<double>::AudioBuffer buffer_imag;
    buffer_imag.resize(numChannels);

  for (auto &channel : buffer_imag)
    channel.resize(numSamples);

  for (int channel = 0; channel < numChannels; channel++) {
    fftw_complex *signal;
    fftw_complex *result;

    // signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * numSamples);
    result = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * numSamples);


    // place(signal, wav.samples[channel], numSamples);

    double* a = &wav.samples[channel][0];

    fftw_plan plan = fftw_plan_dft_r2c_1d(numSamples, a, result, FFTW_ESTIMATE);
    
    fftw_execute(plan);

    

    for (int i = 0; i < numSamples; i++) {
      buffer_real[channel][i] = result[REAL][i];
      buffer_imag[channel][i] = result[IMAG][i];
    }

    fftw_destroy_plan(plan);
    fftw_free(signal); fftw_free(result);

  }

  AudioFile<double> wav_real;
  AudioFile<double> wav_imag;

  wav_real.setAudioBuffer(buffer_real);
    wav_real = normalize(wav_real);
    wavs.push_back(wav_real);

  wav_imag.setAudioBuffer(buffer_imag);
    wav_imag = normalize(wav_imag);
    wavs.push_back(wav_imag);
  
  return wavs;
}

AudioFile<double> inverseFastFourierTransform(AudioFile<double> wav_real, AudioFile<double> wav_imag) {
  std::cout << "computing inverse fast fourier transform of file..." << std::endl;
  
  int numSamples;
  int numChannels;

  AudioFile<double> result_wav;

  if (wav_real.getNumChannels() != wav_imag.getNumChannels()) {
    std::cout << "files must have the same number of channels!" << std::endl;
    exit(0);
  }

  numChannels = wav_real.getNumChannels();

  if (wav_real.getNumSamplesPerChannel() != wav_imag.getNumSamplesPerChannel()) {
    numSamples = std::min(wav_real.getNumSamplesPerChannel(), wav_imag.getNumSamplesPerChannel());
  } else {
    numSamples = wav_real.getNumSamplesPerChannel();
  }

  AudioFile<double>::AudioBuffer result_buffer;
    result_buffer.resize(numChannels);

  for (auto &channel : result_buffer)
    channel.resize(numSamples);

  for (int channel = 0; channel < numChannels; channel++) {
    fftw_complex *signal;
    // fftw_complex *result;
    double* result = new double[numSamples];

    signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * numSamples);
    // result = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * numSamples);


    fftw_plan plan = fftw_plan_dft_c2r_1d(numSamples, signal, result, FFTW_ESTIMATE);

    place_inverse(signal, wav_real.samples[channel], wav_imag.samples[channel], numSamples);

    fftw_execute(plan);

    for (int i = 0; i < numSamples; i++) {
      result_buffer[channel][i] = result[i];
    }

    fftw_destroy_plan(plan);
    fftw_free(signal); fftw_free(result);
  
  }

  result_wav.setAudioBuffer(result_buffer);
  result_wav = normalize(result_wav);
  
  return result_wav;

}