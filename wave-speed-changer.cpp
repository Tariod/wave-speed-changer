#include <iostream>
#include "./lib/wave.h"

int main() {
    Wave test = Wave();
    
    test.read("./example/input.wav");
    test.write("./example/output.wav");

    Wave test2 = Wave();
    
    test.read("./example/Kino.wav");
    test.write("./example/outputKino.wav");


    return 0;
}