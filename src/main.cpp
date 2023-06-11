#include <filesystem>
#include <string>

#include "../libs/AudioFile/AudioFile.h"
#include "tools/tools.h"
#include "cli-utils/cli.h"

int main(int argc, char **argv) { 
    auto out = parse(argc, argv);
    printf("op done\n");
    out.save("./test.wav");
    printf("saved\n");

}
