#ifndef CLI_H
#define CLI_H

#include "../../libs/AudioFile/AudioFile.h"

std::vector<AudioFile<double>> parse(int argc, char* argv[], std::string& filename);

#endif