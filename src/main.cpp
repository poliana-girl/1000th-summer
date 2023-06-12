#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

#include "../libs/AudioFile/AudioFile.h"
#include "../libs/CImg/CImg.h"

#include "tools/tools.h"
#include "cli-utils/cli.h"
#include "tools/img-tools/img.h"

using namespace cimg_library;

int main(int argc, char **argv) { 
    std::string filename;
    
    auto out = parse(argc, argv, filename);
    printf("op done\n");

    int i = 0;
    std::string name;
    for (auto wav : out) {
        name = filename + "-" + std::to_string(i) + ".wav";
        std::cout << "saving file " << name << std::endl;
        wav.save(name);
        i++;
    }
    
    printf("saved all\n");

    // AudioFile<double> wav; wav.load(argv[1]);
    // CImg<double> img = wavToImage(wav);
    // img.save("img.png");

    // CImg<double> newimg("img.png");
    // AudioFile<double> newwav;
    // newwav = imageToWav(newimg);
    // newwav.save("newwav.wav");

    // std::ifstream file(argv[1], std::ios::in|std::ios::binary|std::ios::ate);
    // AudioFile<double> wav = rawData(std::move(file));
    // printf("op done\n");
    // wav.save("raw.wav");
    // printf("saved\n");

}

