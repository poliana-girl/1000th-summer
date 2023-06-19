# 1000th-summer
c++ CLI (wav) audio tools! coded by chayagirl.

# Tools

## Unary (taking 1 wav)

**Flanger**: flanges the audio according to a delay value (in ms)
```
1000th-summer --flgr audio.wav delay
```

**Distort**: distorts the audio according to a threshold, which is between 0 and 1. 1 is no distortion and 0 is max distortion.
```
1000th-summer --dist audio.wav threshold
```

**Mono to Stereo**: takes mono audio and makes it dual mono (the same audio duplicated in 2 channels).
```
1000th-summer --mtos audio.wav
```

**Normalize**: increase volume to maximum w/o clipping
```
1000th-summer --norm audio.wav
```

**Derivative**: finds the derivative of the audio signal. it can find n-th derivative if given an argument.
```
1000th-summer --deriv audio.wav loop
```

**Integral**: finds the integral of the audio signal. it can find n-th integral if given an argument.
```
1000th-summer --intgl audio.wav loop
```

**Exponential**: raise the signal by an exponent value.
```
1000th-summer --exp audio.wav value
```

**Scatter**: randomly disperse fragments of the audio with a uniform size (in seconds)
```
1000th-summer --sctr audio.wav size
```

**Soft Clip**: increase loudness of audio by a certain factor.
```
1000th-summer --sfclp audio.wav factor
```

**Hypotenuse**: idk exactly how to explain the way this one works lool. you can loop its effects though.
```
1000th-summer --hypot audio.wav loop
```

**Transient Finder**: finds transients and outputs the most "hard-hitting" transients as fragments of the original file. takes a number of fragments.
```
1000th-summer --strans audio.wav numfrags
```

**Left Shift**: shift the bit value of each double precision floating point sample by a certain value.
```
1000th-summer --lsh audio.wav value
```

**Sort Ascending (currently doesnt do what i want lmfao)**: Sort an audio signal by taking the average of a fragment of samples sorting them ascendingly. takes a length (in seconds) of a fragment.
```
1000th-summer --asc audio.wav length
```

**Fast Fourier Transform**: find FFT of a given audio file.
```
1000th-summer --fft audio.wav
```

**Blur**: make the audio file sound blurry.
```
1000th-summer --blur audio.wav
```

**Laplace Transform**: find the Laplacian Transform of the audio file.
```
1000th-summer --lapl audio.wav
```

**Bang**: does some weird shit to the signal so that it creates a "bang" sound at the beginning
```
1000th-summer --bang audio.wav
```

## Binary (taking 2 wavs)

**Multiply**: multiply the signals of two audio files.
```
1000th-summer --mul audio1.wav audio2.wav
```

**Modulo**: find remainder of one audio signal divided by another.
```
1000th-summer --mod audio1.wav audio2.wav
```

**Min**: produces a signal composed of the minimum sample value at any point in each audio signal.
```
1000th-summer --min audio1.wav audio2.wav
```

**Max**: produces a signal composed of the maximum sample value at any point in each audio signal.
```
1000th-summer --max audio1.wav audio2.wav
```

**Inverse FFT**: produces inverse of FFT.
```
1000th-summer --ifft audio1.wav audio2.wav
```

## Weird Ones

**Random Generation**: generates a new audio signal. takes a length in seconds.
```
1000th-summer --rand length
```

**Raw Data**: convert a file's ones and zeroes into a wav file... fucked up.
 ```
1000th-summer --raw any-file
```

# Building
```
git clone --recursive https://github.com/chayagirl/1000th-summer.git
cd 1000th-summer
make
1000th-summer
```
