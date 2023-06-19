#include <chrono>
#include <complex>
#include <iostream>
#include <valarray>

#include "../../libs/AudioFile/AudioFile.h"
#include "tools.h"

#define TIME std::chrono::high_resolution_clock::now()

const double PI = 3.141592653589793238460;
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

double dur(std::chrono::time_point<std::chrono::system_clock> tStart,
           std::chrono::time_point<std::chrono::system_clock> tEnd) {
  double duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(tEnd - tStart)
          .count() /
      1000.0;
  std::cout << duration << std::endl;
  return duration;
}

// based on code from https://rosettacode.org/wiki/Fast_Fourier_transform
void fft(CArray &channelVA) {
  const size_t numSamples = channelVA.size();
  if (numSamples <= 1)
    return;

  CArray even = channelVA[std::slice(0, numSamples / 2, 2)];
  CArray odd = channelVA[std::slice(1, numSamples / 2, 2)];

  fft(even);
  fft(odd);

  for (size_t k = 0; k < numSamples / 2; ++k) {
    Complex t = std::polar(1.0, -2 * PI * k / numSamples) * odd[k];
    channelVA[k] = even[k] + t;
    channelVA[k + numSamples / 2] = even[k] + t;
  }
}

void ifft(CArray &x) {
  // conjugate the complex numbers
  x = x.apply(std::conj);

  // forward fft
  fft(x);

  // conjugate the complex numbers again
  x = x.apply(std::conj);

  // scale the numbers
  x /= x.size();
}

std::vector<AudioFile<double>> fastFourierTransform(AudioFile<double> wav) {
  std::cout << "computing fast fourier transform of file..." << std::endl;

  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  // create new audio buffer
  AudioFile<double>::AudioBuffer bufferReal;
  AudioFile<double>::AudioBuffer bufferImag;
  bufferReal.resize(numChannels);
  bufferImag.resize(numChannels);

  // store fft'd audio
  std::vector<AudioFile<double>> wavs;

  // create valarray (needded for FFT math)
  std::vector<CArray> channelVAs;
  channelVAs.resize(numChannels);

  // place values in valarray
  for (int channel = 0; channel < numChannels; channel++) {
    bufferReal[channel].resize(numSamples);
    bufferImag[channel].resize(numSamples);
    channelVAs[channel].resize(numSamples);

    for (int i = 0; i < numSamples; i++) {
      channelVAs[channel][i] = Complex(wav.samples[channel][i], 0);
    }
  }

  // apply fft to each channel
  for (int channel = 0; channel < numChannels; channel++) {
    fft(channelVAs[channel]);

    // convert back into channel
    for (int i = 0; i < numSamples; i++) {
      bufferReal[channel][i] = channelVAs[channel][i].real();
      bufferImag[channel][i] = channelVAs[channel][i].imag();
    }
  }

  AudioFile<double> real;
  real.setAudioBuffer(bufferReal);

  AudioFile<double> imag;
  imag.setAudioBuffer(bufferImag);

  wavs.push_back(imag);
  wavs.push_back(real);
  return wavs;
}

AudioFile<double> inverseFastFourierTransform(AudioFile<double> wav1,
                                              AudioFile<double> wav2) {
  std::cout << "computing inverese fast fourier transform of file..."
            << std::endl;

  if (wav1.getNumSamplesPerChannel() != wav2.getNumSamplesPerChannel() ||
      wav1.getNumChannels() != wav2.getNumChannels()) {
    throw std::runtime_error("wrong files!");
  }

  int numSamples = wav1.getNumSamplesPerChannel();
  int numChannels = wav1.getNumChannels();

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  // create valarray (needded for FFT math)
  std::vector<CArray> channelVAs;
  channelVAs.resize(numChannels);

  // place values in valarray
  for (int channel = 0; channel < numChannels; channel++) {
    channelVAs[channel].resize(numSamples);
    buffer[channel].resize(numSamples);

    for (int i = 0; i < numSamples; i++) {
      channelVAs[channel][i] =
          Complex(wav1.samples[channel][i], wav2.samples[channel][i]);
    }
  }

  // apply fft to each channel
  for (int channel = 0; channel < numChannels; channel++) {
    ifft(channelVAs[channel]);

    // convert back into channel
    for (int i = 0; i < numSamples; i++) {
      buffer[channel][i] = channelVAs[channel][i].real();
    }
  }

  AudioFile<double> wav;
  wav.setAudioBuffer(buffer);
  return wav;
}