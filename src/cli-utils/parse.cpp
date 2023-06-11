/*
PROPOSED SYNTAX FOR cli:

1000th-summer --distort song.wav
*/

// code adapted from these locations:
// https://medium.com/@mostsignificant/3-ways-to-parse-command-line-arguments-in-c-quick-do-it-yourself-or-comprehensive-36913284460f
// https://www.codeguru.com/cplusplus/switch-on-strings-in-c/

#include <cstddef>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <utility>
#include "../../libs/AudioFile/AudioFile.h"
#include "../tools/tools.h"


enum Tool {
    Derivative,
    Distort,
    Exponent,
    Flanger,
    Hypotenuse,
    Integral,
    MonoToStereo,
    Multiply,
    Normalize,
    Scatter,
    SoftClip,
    TransientFinder
};

static std::map<std::string, Tool> mapTools;

void initMap() {
    mapTools["--deriv"] = Derivative;
    mapTools["--dist"] = Distort;
    mapTools["--exp"] = Exponent;
    mapTools["--flgr"] = Flanger;
    mapTools["--hypot"] = Hypotenuse;
    mapTools["--intgl"] = Integral;
    mapTools["--mtos"] = MonoToStereo;
    mapTools["--mult"] = Multiply;
    mapTools["--norm"] = Normalize;
    mapTools["--sctr"] = Scatter;
    mapTools["--sfclp"] = SoftClip;
    mapTools["--strans"] = TransientFinder;
}

AudioFile<double> parse(int argc, char* argv[]) {
    
    if (argc == 1 || argc == 2 || argc > 4)
        throw std::runtime_error("incorrect amount of input parameters!");

    initMap();

    std::string command = argv[1];
    std::string file1 = argv[2];
    std::string arg_str = argv[3];
    std::string file2 = argv[3];

    AudioFile<double> wav1; wav1.load(file1);
    AudioFile<double> wav2;
    int arg_int;
    double arg_dbl;

    AudioFile<double> out;
    

    //set arg_str to either arg_int or arg_dbl

    switch(mapTools[command]) {
        case Derivative:
            arg_int = std::stoi(arg_str);
            out = derivative(wav1, arg_int);
            break;
        case Distort:
            arg_dbl = std::stod(arg_str);
            out = distort(wav1, arg_dbl);
            break;
        case Exponent:
            arg_int = std::stoi(arg_str);
            out = exp(wav1, arg_int);
            break;
        case Flanger:
            arg_int = std::stoi(arg_str);
            out = flanger(wav1, arg_int);
            break;
        case Hypotenuse:
            arg_int = std::stoi(arg_str);
            out = hypot(wav1, arg_int);
            break;
        case Integral:
            arg_int = std::stoi(arg_str);
            out = integral(wav1, arg_int);
            break;
        case MonoToStereo:
            out = monoToStereo(wav1);
            break;
        case Multiply:
            wav2.load(file2);
            out = multiply(wav1, wav2);
            break;
        case Normalize:
            out = normalize(wav1);
            break;
        case Scatter:
            arg_int = std::stoi(arg_str);
            out = scatter(wav1, arg_int);
            break;
        case SoftClip:
            arg_dbl = std::stod(arg_str);
            softClip(wav1, arg_dbl);
            break;
        case TransientFinder:
            std::cout << "not implemented yet!~" << std::endl;
            break;
        default:
            throw std::runtime_error("command not found!");
    }

    return out;
}