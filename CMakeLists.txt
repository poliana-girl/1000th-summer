cmake_minimum_required(VERSION 3.5)
project(1000th-summer
    VERSION
        0.1
    LANGUAGES
        CXX
)

find_library(fftw3 libfftw3.a PATHS /usr/local/)

find_package(X11 REQUIRED)

file(GLOB_RECURSE sources 
    src/*.cpp 
    src/tools/*.cpp 
    src/tools/*.h
    src/cli-utils/*.cpp
    src/cli-utils/*.h
)

file(GLOB_RECURSE libs
    libs/AudioFile/AudioFile.h
    libs/CImg/CImg.h
    libs/uberswitch/include/uberswitch/uberswitch.hpp
)

add_executable(1000th-summer ${sources} ${libs})

target_link_libraries(1000th-summer ${fftw3} ${X11_LIBRARIES})