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
#include "../tools/tools.h"
#include "../../libs/uberswitch/include/uberswitch/uberswitch.hpp"

//noArgsSingleInput
//intArgSingleInput 
//noArgsTwoInput 
//intArgMultioutput 

//TODO: split args into ones that are mandatory and ones that are optional

void dblArgSingleInput(int argc, char* argv[], std::string command, AudioFile<double>& wav, double& arg) {
    if (argc != 4)
        throw std::runtime_error(command + ": incorrect amount of input parameters!");
    std::string file = argv[2];
    wav.load(file);
    arg = std::stod(argv[3]);
}

void intArgSingleInput(int argc, char* argv[], std::string command, AudioFile<double>& wav, int& arg) {
    if (argc != 4)
        throw std::runtime_error(command + ": incorrect amount of input parameters!");
    std::string file = argv[2];
    wav.load(file);
    arg = std::stoi(argv[3]);
}

void noArgsSingleInput(int argc, char* argv[], std::string command, AudioFile<double>& wav) {
    if (argc != 3)
        throw std::runtime_error(command + ": incorrect amount of input parameters!");
    std::string file = argv[2];
    wav.load(file);
}

void noArgsTwoInput(int argc, char* argv[], std::string command, AudioFile<double>& wav1, AudioFile<double>& wav2) {
    if (argc != 4)
        throw std::runtime_error(command + ": incorrect amount of input parameters!");
    std::string file1 = argv[2];
    std::string file2 = argv[3];
    wav1.load(file1);
    wav2.load(file2);
}



AudioFile<double> parse(int argc, char* argv[]) {

    std::string command = argv[1];
    AudioFile<double> wav1;
    AudioFile<double> wav2;

    double dbl_arg;
    int int_arg;

    uswitch (command) {

        ucase ("--flgr"):
            intArgSingleInput(argc, argv, command, wav1, int_arg);
            return flanger(wav1, int_arg);

        ucase ("--dist"):
            dblArgSingleInput(argc, argv, command, wav1, dbl_arg);
            return distort(wav1, dbl_arg);

        ucase ("--mtos"):
            noArgsSingleInput(argc, argv, command, wav1);
            return monoToStereo(wav1);

        ucase ("--norm"):
            noArgsSingleInput(argc, argv, command, wav1);
            return normalize(wav1);

        ucase ("--deriv"):
            intArgSingleInput(argc, argv, command, wav1, int_arg);
            return derivative(wav1, int_arg);

        ucase ("--intgl"):
            intArgSingleInput(argc, argv, command, wav1, int_arg);
            return integral(wav1, int_arg);

        ucase ("--exp"):
            intArgSingleInput(argc, argv, command, wav1, int_arg);
            return exponent(wav1, int_arg);

        ucase ("--sctr"):
            dblArgSingleInput(argc, argv, command, wav1, dbl_arg);
            return scatter(wav1, dbl_arg);

        ucase ("--sfclp"):
            dblArgSingleInput(argc, argv, command, wav1, dbl_arg);
            return softClip(wav1, dbl_arg);

        ucase ("--hypot"):
            intArgSingleInput(argc, argv, command, wav1, int_arg);
            return hypotenuse(wav1, int_arg);

        ucase ("--strans"):
            throw std::runtime_error("command not implemented yet!");

        ucase ("--mul"):
            noArgsTwoInput(argc, argv, command, wav1, wav2);
            return multiply(wav1, wav2);

        ucase ("--mod"):
            noArgsTwoInput(argc, argv, command, wav1, wav2);
            return modulo(wav1, wav2);

        ucase ("--rand"):
            dbl_arg = std::stod(argv[2]);
            return randGen(dbl_arg);
        
        default:
            throw std::runtime_error("command not found!");
    }
}