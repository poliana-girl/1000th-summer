#include <filesystem>
#include <string>
#include "../libs/AudioFile/AudioFile.h"
#include "tools/tools.h"

int main(int argc, char **argv) { 
    
    #ifdef __unix__
        std::filesystem::path p(argv[1]);
        std::filesystem::path p2(argv[2]);
    #elif _WIN64
        std::string p = argv[1];
    #endif

    AudioFile<double> wav; wav.load(p);
    AudioFile<double> wav2; wav2.load(p2);
    //wav = softClip(wav, 5);
    //wav.save(p.stem().string() + "-softclipped.wav");

    //wav = scatter(wav, 44100 / 10);
    //wav.save(p.stem().string() + "-scattered.wav");

    // int numFrags = 20;
    // std::vector<AudioFile<double>> frags = transientFinder(wav, numFrags);
    // std::filesystem::create_directories("./frags");
    // for (int i = 0; i < numFrags; i++) {
    //     frags[i].save("./frags/" + std::to_string(i) + "-test.wav");
    // }

    // wav = monoToStereo(wav);
    // wav.save("keybd-double channel");

    // wav = flanger(wav, 200);
    // wav.save(p.stem().string() + "-flanged.wav");

    // wav = derivative(wav, 10);
    // wav.save(p.stem().string() + "-deriv.wav");

    wav = multiply(wav, wav2);
    wav = normalize(wav);
    wav.save(p.stem().string() + p2.stem().string() + "-mult.wav");
}
