/*
 * Vector3D.h
 *
 *  Created on: 14.02.15
 *      Author: artur
 */


#ifndef Vector3D_H_
#define Vector3D_H_


#include "Vector.h"



namespace geox {

    template<class T>
    class Vector3D : public Vector<T> {
    public:

        Vector3D() : Vector<T>(3) { }
        ~Vector3D() { }


        inline T norm() {
            return sqrt((Matrix<T>::elementsPtr())(0)*(Matrix<T>::elementsPtr())(0) + (Matrix<T>::elementsPtr())(1)*(Matrix<T>::elementsPtr())(1) + (Matrix<T>::elementsPtr())(2)*(Matrix<T>::elementsPtr())(2));
        }

        inline T dotProduct(Vector3D const &v) {
            return (Matrix<T>::elementsPtr())(0)*v(0) + (Matrix<T>::elementsPtr())(1)*v(1) + (Matrix<T>::elementsPtr())(2)*v(2);
        }

        Vector3D crossProduct(Vector3D const &v) {
            Vector3D vector;
            vector(0) = (Matrix<T>::elementsPtr())(1)*v(2) - (Matrix<T>::elementsPtr())(2)*v(1);
            vector(1) = (Matrix<T>::elementsPtr())(2)*v(0) - (Matrix<T>::elementsPtr())(0)*v(2);
            vector(2) = (Matrix<T>::elementsPtr())(0)*v(1) - (Matrix<T>::elementsPtr())(1)*v(0);
            return vector;
        }


        Vector3D operator+(Vector3D const &v) const {
            Vector3D vector;
            vector(0) = (Matrix<T>::elementsPtr())(0) + v(0);
            vector(1) = (Matrix<T>::elementsPtr())(1) + v(1);
            vector(2) = (Matrix<T>::elementsPtr())(2) + v(2);
            return vector;
        }

        Vector3D operator-(Vector3D const &v) const {
            Vector3D vector;
            vector(0) = (Matrix<T>::elementsPtr())(0) - v(0);
            vector(1) = (Matrix<T>::elementsPtr())(1) - v(1);
            vector(2) = (Matrix<T>::elementsPtr())(2) - v(2);
            return vector;
        }

        Vector3D operator*(T const &scalar) const {
            Vector3D vector;
            vector(0) = (Matrix<T>::elementsPtr())(0) * scalar;
            vector(1) = (Matrix<T>::elementsPtr())(1) * scalar;
            vector(2) = (Matrix<T>::elementsPtr())(2) * scalar;
            return vector;
        }

        Vector3D operator/(T const &scalar) const {
            Vector3D vector;
            vector(0) = (Matrix<T>::elementsPtr())(0) / scalar;
            vector(1) = (Matrix<T>::elementsPtr())(1) / scalar;
            vector(2) = (Matrix<T>::elementsPtr())(2) / scalar;
            return vector;
        }



        Vector3D const &operator+=(Vector3D const &v) {
            (Matrix<T>::elementsPtr())(0) += v(0);
            (Matrix<T>::elementsPtr())(1) += v(1);
            (Matrix<T>::elementsPtr())(2) += v(2);
            return *this;
        }

        Vector3D const &operator-=(Vector3D const &v) {
            (Matrix<T>::elementsPtr())(0) -= v(0);
            (Matrix<T>::elementsPtr())(1) -= v(1);
            (Matrix<T>::elementsPtr())(2) -= v(2);
            return *this;
        }

        Vector3D const &operator*=(T const &scalar) {
            (Matrix<T>::elementsPtr())(0) *= scalar;
            (Matrix<T>::elementsPtr())(1) *= scalar;
            (Matrix<T>::elementsPtr())(2) *= scalar;
            return *this;
        }

        Vector3D const &operator/=(T const &scalar) {
            (Matrix<T>::elementsPtr())(0) /= scalar;
            (Matrix<T>::elementsPtr())(1) /= scalar;
            (Matrix<T>::elementsPtr())(2) /= scalar;
            return *this;
        }

    };

}

#endif