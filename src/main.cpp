#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

#include "../libs/AudioFile/AudioFile.h"
#include "../libs/CImg/CImg.h"

#include "cli-utils/cli.h"
#include "tools/img-tools/img.h"
#include "tools/tools.h"

using namespace cimg_library;

int main(int argc, char **argv) {
  // regular procedure
  // ---------------------------------------------------------------

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

  // --------------------------------------------------------------------------------

  // AudioFile<double> wav; wav.load(argv[1]);
  // auto imgs = wavToImage(wav);

  // int i = 0;
  // for (auto &img : imgs) {

  //     i++;

  //     //img = img.blur(1, 1, 1, 3, true);

  //     //img = img.abs();

  //     img = img.quantize(4);

  //     std::string filename = "img-" + std::to_string(i) + ".png";
  //     auto filename_c = filename.c_str();
  //     img.save(filename_c);
  // }

  // //CImg<double> newimg("img.png");
  // AudioFile<double> newwav;
  // newwav = imageToWav(imgs);
  // newwav.save("newwav.wav");

  // ------------------------------------------------------------------------------

  // std::ifstream file(argv[1], std::ios::in|std::ios::binary|std::ios::ate);
  // AudioFile<double> wav = rawData(std::move(file));
  // printf("op done\n");
  // wav.save("raw.wav");
  // printf("saved\n");

  // -----------------------------------------------------------------------------

  // CImg<double> img(256,256,1,3);       // Define a 256x256 color image
  // cimg_forXYC(img,x,y,c) { img(x,y,c) = (x + y) * c; }
  // img.save("test.png");
}
