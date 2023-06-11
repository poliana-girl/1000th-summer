# 1000th-summer
c++ (wav) audio tools! coded by chayagirl.

# Tools

## Unary (taking 1 wav)

<!-- mapTools["--deriv"] = Derivative;
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
mapTools["--strans"] = TransientFinder; -->

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



## Binary (taking 2 wavs)

**Multiply**: multiply the signals of two audio files.
```
1000th-summer --mul audio1.wav audio2.wav
```

**Modulo**: find remainder of one audio signal divided by another.
```
1000th-summer --mod audio1.wav audio2.wav
```

# Building
```
git clone --recursive https://github.com/chayagirl/1000th-summer.git
cd 1000th-summer
make
1000th-summer
```
