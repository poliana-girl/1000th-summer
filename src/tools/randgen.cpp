#include <iostream>
#include <ctime>

#include "../../libs/AudioFile/AudioFile.h"
#include "tools.h"

bool randomBool() { return rand() > (RAND_MAX / 2); }

AudioFile<double> randGen(double length) {
  std::cout << "generating random file " << length << "s long..." << std::endl;

  srand(time(0));
  int numSamples = length * 44100;

  AudioFile<double>::AudioBuffer buffer;
  AudioFile<double> wav;

  buffer.resize(2);
  buffer[0].resize(numSamples);
  buffer[1].resize(numSamples);

  for (auto &channel : buffer) {
    double value = 0;
    for (auto &sample : channel) {

      bool coin = randomBool();

      if (coin) {
        value = value + 0.001;
      } else {
        value = value - 0.001;
      }

      // std::cout << value << std::endl;

      sample = value;
    }
  }

  wav.setAudioBuffer(buffer);
  wav = normalize(wav);
  return wav;
}