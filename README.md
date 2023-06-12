# 1000th-summer
c++ (wav) audio tools! coded by chayagirl.

# Tools

## No Input

**Random Generation**: generates a new audio signal. takes a length in seconds.
```
1000th-summer --rand audio.wav length
```

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

**Sort Ascending**: Sort an audio signal by taking the average of a fragment of samples sorting them ascendingly. takes a length (in seconds) of a fragment.
```
1000th-summer --asc audio.wav length
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



# Building
```
git clone --recursive https://github.com/chayagirl/1000th-summer.git
cd 1000th-summer
make
1000th-summer
```
