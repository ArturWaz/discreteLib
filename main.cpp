#include <iostream>


#include "lib/discrete/DirectForm_II.h"
#include "lib/generator/Step.h"





using namespace std;

void testFunc1() {
    double nom[] = {0.2642,0.1353}; // http://www.eng.ox.ac.uk/~conmrc/dcs/dcs-lec4.pdf
    double den[] = {1,-0.7358,0.1353};
    geox::DirectForm_II tf(nom,2,den,3);

    geox::Step gen;

    for (int time = 0; time < 20; ++time) {
        cout << "in: " << gen(time) << ", out: " << tf(gen(time)) << endl;
    }
}

int main() {

    testFunc1();

    return 0;
}