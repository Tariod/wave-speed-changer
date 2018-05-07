#include "wave.h"

#define waveDescriptorSize 36
#define int32 sizeof(int32_t)
#define int16 sizeof(int16_t)
#define int8 sizeof(int8_t)

Wave::~Wave(){

};

void Wave::read(const char *fileName) {
    FILE* file = fopen(fileName,"rb");
    if(file){
        headerRead(file);
        formatRead(file);
        dataRead(file);
        fclose(file);
    } else {
        std::cout << "No such file." << std::endl;
    }
};

void Wave::resize(int coef) {

};

void Wave::write(const char *fileName) {
    FILE* file = fopen(fileName, "wb");
    headerWrite(file);
    formatWrite(file);
    dataWrite(file);
    fclose(file);
};

void Wave::interpolation() {

};

void Wave::headerRead(FILE* file) {
    fread(&descriptor, sizeof(riffHeader), 1, file);
};

void Wave::formatRead(FILE* file) {
    fread(&format, sizeof(subchunk1), 1, file);
};

void Wave::dataRead(FILE* file) {
    fread(&samples.subchunk2Id, int32, 1, file);
    fread(&samples.subchunk2Size, int32, 1, file);
    numSamples = samples.subchunk2Size / format.blockAlign;
    switch (format.numChannels) {
        case 1:
            samples.data16 = new int16_t[numSamples];
            for(int i = 0; i < numSamples; i++)
                fread(&samples.data16[i], int16, 1, file);
            break;
        case 2:
            samples.data32 = new int32_t[numSamples];
            for(int i = 0; i < numSamples; i++)
                fread(&samples.data32[i], int32, 1, file);
            break;
    } 
    infoSize = descriptor.chunkSize - samples.subchunk2Size - waveDescriptorSize;
    if(infoSize > 0) {
        samples.info = new int8_t[infoSize];
        for(int i = 0; i < infoSize; i++)
            fread(&samples.info[i], int8, 1, file);
    }
};

void Wave::headerWrite(FILE* file) {
    fwrite(&descriptor, sizeof(riffHeader), 1, file);
};

void Wave::formatWrite(FILE* file) {
    fwrite(&format, sizeof(subchunk1), 1, file);
};

void Wave::dataWrite(FILE* file) {
    fwrite(&samples.subchunk2Id, int32, 1, file);
    fwrite(&samples.subchunk2Size, int32, 1, file);
    switch (format.numChannels) {
        case 1:
            for(int i = 0; i < numSamples; i++)
                fwrite(&samples.data16[i], int16, 1, file);
            break;
        case 2:
            for(int i = 0; i < numSamples; i++)
                fwrite(&samples.data32[i], int32, 1, file);
            break;
    } 
    if(infoSize > 0)
        for(int i = 0; i < infoSize; i++)
            fwrite(&samples.info[i], int8, 1, file);
};
