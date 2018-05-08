#include <iostream>
#include "./lib/wave.h"

int main() {
    Wave cartoon = Wave();
    
    cartoon.read("./example/input.wav");
    cartoon.resize(2);
    cartoon.write("./example/output.wav");

    Wave kino = Wave();
    
    kino.read("./example/Kino.wav");
    kino.resize(0.50);
    kino.write("./example/outputKino.wav");
    kino.resize(2);
    kino.write("./example/outputKino2.wav");

    return 0;
}