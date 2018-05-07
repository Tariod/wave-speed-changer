#ifndef WaveH
#define WaveH

#include <iostream>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include "CubicSpline.h"

typedef struct {
    int32_t chunkId;
    int32_t chunkSize;
    int32_t format;
} riffHeader;

typedef struct {
    int32_t subchunk1Id;
    int32_t subchunk1Size;
    int16_t audioFormat;
    int16_t numChannels;
    int32_t sampleRate;
    int32_t byteRate;
    int16_t blockAlign;
    int16_t bitsPerSample;
} subchunk1;

typedef struct {
    int32_t subchunk2Id;
    int32_t subchunk2Size;
    int16_t *data16;
    int32_t *data32;
    int8_t *info;
} subchunk2;

class Wave {
public:
    ~Wave();

    void read(const char *fileName);

    void resize(double coef);

    void write(const char *fileName);

private:
    void interpolation(double coef);

    void headerRead(FILE* file);

    void formatRead(FILE* file);

    void dataRead(FILE* file);

    void headerWrite(FILE* file);

    void formatWrite(FILE* file);

    void dataWrite(FILE* file);

    riffHeader descriptor;
    subchunk1 format;
    subchunk2 samples;

    int numSamples;
    int infoSize;
};

#endif