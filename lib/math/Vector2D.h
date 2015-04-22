//
// Created by artur on 22/04/15.
//

#ifndef DISCRETELIB_VECTOR2D_H
#define DISCRETELIB_VECTOR2D_H


#include "Vector.h"


namespace geox {

    template <class T>
    class Vector2D : public Vector<T> {
    public:

        Vector2D() : Vector<T>(2) {}
        ~Vector2D() {}


        inline T norm() {
            return sqrt((Matrix<T>::elementsPtr())(0)*(Matrix<T>::elementsPtr())(0) + (Matrix<T>::elementsPtr())(1)*(Matrix<T>::elementsPtr())(1));
        }

        inline T dotProduct(Vector2D<T> const & v) {
            return (Matrix<T>::elementsPtr())(0)*v(0) + (Matrix<T>::elementsPtr())(1)*v(1);
        }



        Vector2D operator+(Vector2D const &v) const {
            Vector2D vector;
            vector(0) = (Matrix<T>::elementsPtr())(0) + v(0);
            vector(1) = (Matrix<T>::elementsPtr())(1) + v(1);
            return vector;
        }

        Vector2D operator-(Vector2D const &v) const {
            Vector2D vector;
            vector(0) = (Matrix<T>::elementsPtr())(0) - v(0);
            vector(1) = (Matrix<T>::elementsPtr())(1) - v(1);
            return vector;
        }

        Vector2D operator*(T const &scalar) const {
            Vector2D vector;
            vector(0) = (Matrix<T>::elementsPtr())(0) * scalar;
            vector(1) = (Matrix<T>::elementsPtr())(1) * scalar;
            return vector;
        }

        Vector2D operator/(T const &scalar) const {
            Vector2D vector;
            vector(0) = (Matrix<T>::elementsPtr())(0) / scalar;
            vector(1) = (Matrix<T>::elementsPtr())(1) / scalar;
            return vector;
        }



        Vector2D const &operator+=(Vector2D const &v) {
            (Matrix<T>::elementsPtr())(0) += v(0);
            (Matrix<T>::elementsPtr())(1) += v(1);
            return *this;
        }

        Vector2D const &operator-=(Vector2D const &v) {
            (Matrix<T>::elementsPtr())(0) -= v(0);
            (Matrix<T>::elementsPtr())(1) -= v(1);
            return *this;
        }

        Vector2D const &operator*=(T const &scalar) {
            (Matrix<T>::elementsPtr())(0) *= scalar;
            (Matrix<T>::elementsPtr())(1) *= scalar;
            return *this;
        }

        Vector2D const &operator/=(T const &scalar) {
            (Matrix<T>::elementsPtr())(0) /= scalar;
            (Matrix<T>::elementsPtr())(1) /= scalar;
            return *this;
        }

    };

}

#endif //DISCRETELIB_VECTOR2D_H
