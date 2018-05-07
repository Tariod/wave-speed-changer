#include <iostream>
#include "./lib/wave.h"

int main() {
    Wave test = Wave();
    
    test.read("./example/input.wav");
    test.resize(0.75);
    test.write("./example/output.wav");

    return 0;
}