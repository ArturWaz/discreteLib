#include <iostream>


#include "lib/discrete/object/TransferFunction.h"
#include "lib/generator/Step.h"





using namespace std;

void testFunc1() {
    double nom[] = {13*1,13*-0.88}; // http://www.eng.ox.ac.uk/~conmrc/dcs/dcs-lec4.pdf
    double den[] = {1,0.5};
    geox::TransferFunction tf(nom,1,den,2);

    geox::Step gen(0,1);

    for (int time = 0; time < 100; ++time) {
        cout << "in: " << gen(time) << ", out: " << tf(gen(time)) << endl;
    }
}

int main() {

    testFunc1();

    return 0;
}