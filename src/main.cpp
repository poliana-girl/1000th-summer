#include <filesystem>
#include <string>
#include "../libs/AudioFile/AudioFile.h"
#include "tools/tools.h"

int main(int argc, char **argv) { 
    
    #ifdef __unix__
        std::filesystem::path p(argv[1]);
    #elif _WIN64
        std::string p = argv[1];
    #endif

    AudioFile<double> wav; wav.load(p);
    //wav = softClip(wav, 5);
    //wav.save(p.stem().string() + "-softclipped.wav");

    //wav = scatter(wav, 44100 / 10);
    //wav.save(p.stem().string() + "-scattered.wav");

    int numFrags = 20;
    std::vector<AudioFile<double>> frags = transientFinder(wav, numFrags);
    std::filesystem::create_directories("./frags");
    for (int i = 0; i < numFrags; i++) {
        frags[i].save("./frags/" + std::to_string(i) + "-test.wav");
    }

    // wav = monoToStereo(wav);
    // wav.save("keybd-double channel");
}
