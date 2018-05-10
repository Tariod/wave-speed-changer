#include "wave.h"

#define waveDescriptorSize 36
#define int32 sizeof(int32_t)
#define int16 sizeof(int16_t)
#define int8 sizeof(int8_t)

Wave::~Wave(){
    Wave::freeMem();
};

void Wave::read(const char *fileName) {
    Wave::freeMem();
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

void Wave::resize(double coef) {
    Wave::interpolation(coef);
    numSamples = ceil(coef * numSamples);
    samples.subchunk2Size = format.blockAlign * numSamples;
    descriptor.chunkSize = infoSize + samples.subchunk2Size + waveDescriptorSize;
};

void Wave::write(const char *fileName) {
    FILE* file = fopen(fileName, "wb");
    headerWrite(file);
    formatWrite(file);
    dataWrite(file);
    fclose(file);
};

void Wave::interpolation(double coef) {
    CubicSpline *spline = new CubicSpline [format.numChannels];
    int newsize = ceil(coef * numSamples);

    int32_t *time = new int32_t[numSamples];
    for(int i = 0; i < numSamples; i++)
        time[i] = i;

    for(int i = 0; i < format.numChannels; i++)
        spline[i].buildSpline(time, samples.data16[i], numSamples);

    int16_t **resizeData = new int16_t *[format.numChannels];
    double step = (double)(numSamples - 1) / newsize;
    for(int i = 0; i < format.numChannels; i++) {
        resizeData[i] = new int16_t[newsize];
        double value = 0;
        for(int j = 0; j < newsize; j++) {
            resizeData[i][j] = ceil(spline[i].f(value));
            value += step;
        }
    }
   
    for(int i = 0; i < format.numChannels; i++)
        delete []samples.data16[i];
    delete []samples.data16;
    samples.data16 = resizeData;

    delete []time;
    delete []spline;
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
    samples.data16 = new int16_t *[format.numChannels];
    for(int i = 0; i < format.numChannels; i++)
        samples.data16[i] = new int16_t[numSamples];
    
    for(int i = 0; i < numSamples; i++)
        for(int j = 0; j < format.numChannels; j++)
            fread(&samples.data16[j][i], int16, 1, file);

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

    for(int i = 0; i < numSamples; i++)
        for(int j = 0; j < format.numChannels; j++)
            fwrite(&samples.data16[j][i], int16, 1, file);

    if(infoSize > 0)
        for(int i = 0; i < infoSize; i++)
            fwrite(&samples.info[i], int8, 1, file);
};

void Wave::freeMem() {
    for(int i = 0; i < format.numChannels; i++)
        delete []samples.data16[i];
    delete []samples.data16;
    delete []samples.info;
};
