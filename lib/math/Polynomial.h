//
// Created by szymek on 20/04/15.
//

#ifndef DISCRETELIB_POLYNOMIAL_H
#define DISCRETELIB_POLYNOMIAL_H


#include "Vector.h"


namespace geox {

    class Polynomial: Vector<double> {

    public:

        Polynomial(geox::Vector<double> const &vector): Vector(vector) {}

        double calculate(double const &input) {
            double out = 0.0;
            for (size_t i = 0; i < length; ++i) {
                out += table[i] * pow(input,length-i);
            }
            return out;
        }

    };

}

#endif //DISCRETELIB_POLYNOMIAL_H
