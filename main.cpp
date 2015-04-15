#include <iostream>


#include "lib/generator/Sinus.h"





using namespace std;

int main() {


    geox::Sinus sinGen(0.5);
    double time = 1.5;

    cout << sinGen(time);

    return 0;
}