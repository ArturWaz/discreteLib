/*
 * Vector.h
 *
 *  Created on: 14.02.15
 *      Author: artur
 */


#ifndef Vector_H_
#define Vector_H_

#include <cstring>
#include <cstdlib>
#include "Matrix.h"
#include "myMath.h"


namespace geox {

    template<class T>
    class Vector: public Matrix<T> {
        static_assert(std::is_arithmetic<T>::value, "\nVector<T> template is not supported.\n");

        class Exception : public std::exception {
            char const *info;
        public:
            explicit Exception(char const *info) : info(info) { }
            virtual char const *what() const throw() { return info; }
        };

    public:

        inline Vector(size_t length): Matrix<T>(1,length) { }
        inline Vector(const Vector<T> &v) : Matrix<T>(v) { }
        Vector<T> const &operator=(const Vector<T> &v) {
            if (Matrix<T>::getColumns() != Matrix<T>::v.getColumns() || Matrix<T>::getRows() != Matrix<T>::v.getRows())
                throw Exception("Size of vectors are different, function Vector::operator=(Vector const &)");
            memcpy(Matrix<T>::elementsPtr(), v.Matrix<T>::elementsPtr(), Matrix<T>::size() * sizeof(T));
            return *this;
        }
        ~Vector() { }

        inline size_t getLength() const { return Matrix<T>::size(); }

        inline Vector<T> &transpose() {
            size_t tmp = Matrix<T>::rows();
            Matrix<T>::rows() = Matrix<T>::columns();
            Matrix<T>::columns() = tmp;
            return *this;
        }

        T norm() const {
            T norm(0);
            for (int i = 0; i < Matrix<T>::size(); ++i) norm += (Matrix<T>::elementsPtr())(i) * (Matrix<T>::elementsPtr())(i);
            return sqrt(norm);
        }

        T dotProduct(Vector<T> const &v) const {
            T result(0);
            for (int i = 0; i < Matrix<T>::size(); ++i) result += (Matrix<T>::elementsPtr())(i) * v(i);
            return result;
        }



        Vector<T> operator+(Vector<T> const &v) const {
            if (Matrix<T>::getColumns() != v.Matrix<T>::getColumns() || Matrix<T>::getRows() != v.Matrix<T>::getRows())
                throw Exception("Size of vectors are different, function Vector::operator+(Vector const &)");
            Vector<T> vector(*this);
            for (size_t i = 0; i < Matrix<T>::size(); ++i)
                (vector.Matrix<T>::elementsPtr())[i] += (v.Matrix<T>::elementsPtr())[i];
            return vector;
        }

        Vector<T> operator-(Vector<T> const &v) const {
            if (Matrix<T>::getColumns() != v.Matrix<T>::getColumns() || Matrix<T>::getRows() != v.Matrix<T>::getRows())
                throw Exception("Size of vectors are different, function Vector::operator-(Vector const &)");
            Vector<T> vector(*this);
            for (size_t i = 0; i < Matrix<T>::size(); ++i)
                (vector.Matrix<T>::elementsPtr())[i] -= (v.Matrix<T>::elementsPtr())[i];
            return vector;
        }

        Vector<T> operator*(T const &v) const {
            Vector<T> vector(*this);
            for (size_t i = 0; i < Matrix<T>::size(); ++i)
                (vector.Matrix<T>::elementsPtr())[i] *= v;
            return vector;
        }

        Vector<T> operator/(T const &v) const {
            Vector<T> vector(*this);
            for (size_t i = 0; i < Matrix<T>::size(); ++i)
                (vector.Matrix<T>::elementsPtr())[i] /= v;
            return vector;
        }



        Vector<T> const &operator+=(Vector<T> const &v) {
            if (Matrix<T>::getColumns() != v.Matrix<T>::getColumns() || Matrix<T>::getRows() != v.Matrix<T>::getRows())
                throw Exception("Size of vectors are different, function Vector::operator+=(Vector const &)");
            for (size_t i = 0; i < Matrix<T>::size(); ++i)
                (Matrix<T>::elementsPtr())[i] += (v.Matrix<T>::elementsPtr())[i];
            return *this;
        }

        Vector<T> const &operator-=(Vector<T> const &v) {
            if (Matrix<T>::getColumns() != v.Matrix<T>::getColumns() || Matrix<T>::getRows() != v.Matrix<T>::getRows())
                throw Exception("Size of vectors are different, function Vector::operator-=(Vector const &)");
            for (size_t i = 0; i < Matrix<T>::size(); ++i)
                (Matrix<T>::elementsPtr())[i] -= (v.Matrix<T>::elementsPtr())[i];
            return *this;
        }

        Vector<T> const &operator*=(T const &v) {
            for (size_t i = 0; i < Matrix<T>::size(); ++i)
                (Matrix<T>::elementsPtr())[i] *= v;
            return *this;
        }

        Vector<T> const &operator/=(T const &v) {
            for (size_t i = 0; i < Matrix<T>::size(); ++i)
                (Matrix<T>::elementsPtr())[i] /= v;
            return *this;
        }



        inline Matrix<T> operator*(Matrix<T> const &m) const {
            return (static_cast<Matrix<T>>(*this)) * m;
        }

    };

}

#endif //__Vector_H_