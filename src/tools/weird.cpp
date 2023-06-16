// based on code from https://rosettacode.org/wiki/Fast_Fourier_transform

#include <complex>
#include <iostream>
#include <valarray>

#include "../../libs/AudioFile/AudioFile.h"
#include "tools.h"

const double PI = 3.141592653589793238460;
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

void weird(CArray &channelVA) {
  const size_t numSamples = channelVA.size();
  if (numSamples <= 1)
    return;

  CArray even = channelVA[std::slice(0, numSamples / 2, 2)];
  CArray odd = channelVA[std::slice(1, numSamples / 2, 2)];
  CArray fives = channelVA[std::slice(1, numSamples / 5, 5)];

  weird(even);
  weird(odd);
  weird(fives);

  for (size_t k = 0; k < numSamples / 2; ++k) {
    Complex t = std::polar(1.0, -1 * PI * k / numSamples) * odd[k];
    channelVA[k] = even[k] + odd[k];
    channelVA[k + numSamples / 2] = odd[k] + t + fives[k];
  }
}

void weird2(CArray &channelVA) {
  const size_t numSamples = channelVA.size();
  if (numSamples <= 1)
    return;

  CArray even = channelVA[std::slice(0, numSamples / 2, 2)];
  CArray odd = channelVA[std::slice(1, numSamples / 2, 2)];

  weird(even);
  weird(odd);

  for (size_t k = 0; k < numSamples / 2; ++k) {
    Complex t = std::polar(odd[k].real(), even[k].real());
    channelVA[k] = (even[k] + odd[k]) * t;
    channelVA[k + numSamples / 2] = odd[k] + t;
  }
}

AudioFile<double> weirdFn(AudioFile<double> wav) {
  std::cout << "idk abt this one..." << std::endl;

  // find length of given audio file
  int numSamples = wav.getNumSamplesPerChannel();
  int numChannels = wav.getNumChannels();

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  for (auto &channel : buffer)
    channel.resize(numSamples);

  std::vector<CArray> channelVAs;
  channelVAs.resize(numChannels);

  for (auto &channelVA : channelVAs) {
    channelVA.resize(numSamples);
  }

  for (int channel = 0; channel < numChannels; channel++) {
    for (int i = 0; i < numSamples; i++) {
      channelVAs[channel][i] = Complex(wav.samples[channel][i], 0);
    }
  }

  for (int channel = 0; channel < numChannels; channel++) {
    weird2(channelVAs[channel]);
    // convert back into channel
    for (int i = 0; i < numSamples; i++) {
      buffer[channel][i] = channelVAs[channel][i].imag(); // real();
    }
  }

  wav.setAudioBuffer(buffer);
  wav = normalize(wav);
  return wav;
}