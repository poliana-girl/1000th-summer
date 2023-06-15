#include <fstream>
#include <iostream>

#include "../../libs/AudioFile/AudioFile.h"
#include "tools.h"

AudioFile<double> rawData(std::ifstream file) {

  char *test;
  long size = file.tellg();
  std::cout << size << std::endl;

  file.seekg(0, std::ios::beg);
  test = new char[size];
  file.read(test, size);

  // std::cout << sizeof(double) << " " << sizeof(char) << std::endl;
  int numSamples = size / sizeof(double);

  int numChannels = 1;

  // create new audio buffer
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize(numChannels);

  for (auto &channel : buffer)
    channel.resize(numSamples);

  double dbl_test;
  for (int i = 0; i < numSamples; i++) {
    for (int channel = 0; channel < numChannels; channel++) {
      memcpy(&dbl_test, test + (sizeof(double) * i), sizeof(double));
      buffer[channel][i] = dbl_test;
    }
  }

  //
  // for (int i = 0; i < numSamples; i++) {

  //     std::cout << dbl_test << std::endl;
  // }

  // for (int i = 0; i < size; i++)
  //     std::cout << test[i] << std::endl;

  AudioFile<double> wav;
  wav.setAudioBuffer(buffer);
  // wav = normalize(wav);
  return wav;
}