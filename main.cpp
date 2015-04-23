#include <iostream>


#include "lib/discrete/DirectForm_II.h"
#include "lib/generator/Step.h"
#include "lib/math/Matrix.h"
#include "lib/math/Vector.h"
#include "lib/math/Vector2D.h"





using namespace std;

template <class T>
void print(geox::Matrix<T> const &M) {
    for (int i = 0; i < M.getRows(); ++i) {
        for (int j = 0; j < M.getColumns(); ++j) {
            cout << M(i,j);
            if (j < M.getColumns()-1) cout << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void testFunc1() { // 1/(s(s+1))
    double nom[] = {0.3679,0.2642}; 
    double den[] = {1,-1.3680,0.3679};
    geox::DirectForm_II tf(nom,2,den,3);

    geox::Step gen;

    for (int time = 0; time < 20; ++time) {
        cout << "in: " << gen(time) << ", out: " << tf(gen(time)) << endl;
    }
}


void testMatrices1() {
    geox::Vector<double> v1(3);
//    v1.transpose();
    geox::Matrix<double> m1(3,3);

    geox::Vector<double> v2(v1);

    print(v1*m1);
}

int main() {

    testMatrices1();

    return 0;
}
