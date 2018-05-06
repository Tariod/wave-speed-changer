#ifndef WaveH
#define WaveH

#include "stdint.h"

typedef struct {
    int32_t chunkId;
    int32_t chunkSize;
    int32_t format;
} riffHeader;

typedef struct {
    int32_t subchunk1Id;
    int32_t subchunk1Size;
    int32_t audioFormat;
    int16_t numChannels;
    int32_t sampleRate;
    int32_t byteRate;
    int32_t blockAlign;
    int16_t bitsPerSample;
} subchunk1;

typedef struct {
    int32_t subchunk2Id;
    int32_t subchunk2Size;
    int8_t *data;
} subchunk2;

class Wave {
public:
    Wave();

    ~Wave();

    void read(const char *fileName);

    void resize(int coef);

    void write(const char *fileName);
private:
    void interpolation();

    riffHeader descriptor;
    subchunk1 format;
    subchunk2 data;
};
#endif