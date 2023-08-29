/*
SYNTAX FOR cli:

1000th-summer --distort song.wav
*/

#include <cstddef>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <utility>

#include "../../libs/AudioFile/AudioFile.h"
#include "../../libs/uberswitch/include/uberswitch/uberswitch.hpp"
#include "../tools/img-tools/img.h"
#include "../tools/tools.h"

// noArgsSingleInput
// intArgSingleInput
// noArgsTwoInput
// intArgMultioutput

std::string remove_extension(const std::string &path) {
  if (path == "." || path == "..")
    return path;

  size_t pos = path.find_last_of("\\/.");
  if (pos != std::string::npos && path[pos] == '.')
    return path.substr(0, pos);

  return path;
}

std::string nameSingleInput(char **argv) {
  std::string stem = remove_extension(argv[2]);
  std::string op = argv[1];
  op.erase(0, 1);

  return stem + op;
}

std::string nameTwoInput(char **argv) {
  std::string stem1 = remove_extension(argv[2]);
  std::string stem2 = remove_extension(argv[3]);
  std::string op = argv[1];
  op.erase(0, 1);

  return stem1 + "-" + stem2 + op;
}

// TODO: split args into ones that are mandatory and ones that are optional

void dblArgSingleInput(int argc, char *argv[], std::string command,
                       AudioFile<double> &wav, double &arg) {
  if (argc != 4)
    throw std::runtime_error(command +
                             ": incorrect amount of input parameters!");
  std::string file = argv[2];
  wav.load(file);
  arg = std::stod(argv[3]);
}

void intArgSingleInput(int argc, char *argv[], std::string command,
                       AudioFile<double> &wav, int &arg) {
  if (argc != 4)
    throw std::runtime_error(command +
                             ": incorrect amount of input parameters!");
  std::string file = argv[2];
  wav.load(file);
  arg = std::stoi(argv[3]);
}

void noArgsSingleInput(int argc, char *argv[], std::string command,
                       AudioFile<double> &wav) {
  if (argc != 3)
    throw std::runtime_error(command +
                             ": incorrect amount of input parameters!");
  std::string file = argv[2];
  wav.load(file);
}

void noArgsTwoInput(int argc, char *argv[], std::string command,
                    AudioFile<double> &wav1, AudioFile<double> &wav2) {
  if (argc != 4)
    throw std::runtime_error(command +
                             ": incorrect amount of input parameters!");
  std::string file1 = argv[2];
  std::string file2 = argv[3];
  wav1.load(file1);
  wav2.load(file2);
}

std::vector<AudioFile<double>> parse(int argc, char *argv[],
                                     std::string &filename) {

  std::vector<AudioFile<double>> wavs;

  std::string command = argv[1];
  AudioFile<double> wav1;
  AudioFile<double> wav2;

  std::ifstream file;

  double dbl_arg;
  int int_arg;

  uswitch(command) {

    ucase("--flgr") : intArgSingleInput(argc, argv, command, wav1, int_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(flanger(wav1, int_arg));
    break;

    ucase("--dist") : dblArgSingleInput(argc, argv, command, wav1, dbl_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(distort(wav1, dbl_arg));
    break;

    ucase("--mtos") : noArgsSingleInput(argc, argv, command, wav1);
    filename = nameSingleInput(argv);
    wavs.push_back(monoToStereo(wav1));
    break;

    ucase("--norm") : noArgsSingleInput(argc, argv, command, wav1);
    filename = nameSingleInput(argv);
    wavs.push_back(normalize(wav1));
    break;

    ucase("--deriv") : intArgSingleInput(argc, argv, command, wav1, int_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(derivative(wav1, int_arg));
    break;

    ucase("--intgl") : intArgSingleInput(argc, argv, command, wav1, int_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(integral(wav1, int_arg));
    break;

    ucase("--exp") : dblArgSingleInput(argc, argv, command, wav1, dbl_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(exponent(wav1, dbl_arg));
    break;

    ucase("--sctr") : dblArgSingleInput(argc, argv, command, wav1, dbl_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(scatter(wav1, dbl_arg));
    break;

    ucase("--sfclp") : dblArgSingleInput(argc, argv, command, wav1, dbl_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(softClip(wav1, dbl_arg));
    break;

    ucase("--hypot") : intArgSingleInput(argc, argv, command, wav1, int_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(hypotenuse(wav1, int_arg));
    break;

    ucase("--strans") : intArgSingleInput(argc, argv, command, wav1, int_arg);
    filename = nameSingleInput(argv);
    return transientFinder(wav1, int_arg);

    ucase("--mul") : noArgsTwoInput(argc, argv, command, wav1, wav2);
    filename = nameTwoInput(argv);
    wavs.push_back(multiply(wav1, wav2));
    break;

    ucase("--mod") : noArgsTwoInput(argc, argv, command, wav1, wav2);
    filename = nameTwoInput(argv);
    wavs.push_back(modulo(wav1, wav2));
    break;

    ucase("--rand") : dbl_arg = std::stod(argv[2]);
    filename = nameSingleInput(argv);
    wavs.push_back(randGen(dbl_arg));
    break;

    ucase("--min") : noArgsTwoInput(argc, argv, command, wav1, wav2);
    filename = nameTwoInput(argv);
    wavs.push_back(minimum(wav1, wav2));
    break;

    ucase("--max") : noArgsTwoInput(argc, argv, command, wav1, wav2);
    filename = nameTwoInput(argv);
    wavs.push_back(maximum(wav1, wav2));
    break;

    ucase("--lsh") : intArgSingleInput(argc, argv, command, wav1, int_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(leftShift(wav1, int_arg));
    break;

    ucase("--asc") : dblArgSingleInput(argc, argv, command, wav1, dbl_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(sortAscending(wav1, dbl_arg));
    break;

    ucase("--raw")
        : file.open(argv[2], std::ios::in | std::ios::binary | std::ios::ate);
    filename = nameSingleInput(argv);
    wavs.push_back(rawData(std::move(file)));
    break;

    ucase("--fft") : noArgsSingleInput(argc, argv, command, wav1);
    filename = nameSingleInput(argv);
    return fastFourierTransform(wav1);
    break;

    ucase("--ifft") : noArgsTwoInput(argc, argv, command, wav1, wav2);
    filename = nameTwoInput(argv);
    wavs.push_back(inverseFastFourierTransform(wav1, wav2));
    break;

    ucase("--weird") : noArgsSingleInput(argc, argv, command, wav1);
    filename = nameSingleInput(argv);
    wavs.push_back(weirdFn(wav1));
    break;

    ucase("--blur") : dblArgSingleInput(argc, argv, command, wav1, dbl_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(blur(wav1, dbl_arg));
    break;

    ucase("--lapl") : noArgsSingleInput(argc, argv, command, wav1);
    filename = nameSingleInput(argv);
    wavs.push_back(laplaceTransform(wav1));
    break;

    ucase("--bang") : noArgsSingleInput(argc, argv, command, wav1);
    filename = nameSingleInput(argv);
    wavs.push_back(bang(wav1));
    break;

    ucase("--epic") : noArgsSingleInput(argc, argv, command, wav1);
    filename = nameSingleInput(argv);
    wavs.push_back(epic(wav1));
    break;

    ucase("--tay") : intArgSingleInput(argc, argv, command, wav1, int_arg);
    filename = nameSingleInput(argv);
    wavs.push_back(taylorSeriesApproximation(wav1, int_arg));
    break;


  default:
    throw std::runtime_error("command not found!");
  }

  return wavs;
}