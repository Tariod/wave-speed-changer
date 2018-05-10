#include <iostream>
#include <string>
#include <sstream>
#include "./lib/wave.h"
using namespace std;

int main(int val,char* args[]) {   
    const char* inputFile = args[1];
    const char* outputFile = args[2];
    double coef = atof(args[3]);
    
    Wave song = Wave();    
    song.read(inputFile);
    cout << "Read" << endl;
    song.resize(coef);
    cout << "Scaling sound file... Done." << endl;
    song.write(outputFile);
    cout << "Written result to " << outputFile << endl;    

    return 0;
}