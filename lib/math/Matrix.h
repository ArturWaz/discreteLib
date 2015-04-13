/*
 * Matrix.h
 *
 *  Created on: 15.02.15
 *      Author: artur
 */


#ifndef Matrix_H_
#define Matrix_H_


#include <cstring>
#include <cstdlib>
#include "Vector.h"
#include "myMath.h"



namespace geox {

    template<class Type>
    class Matrix {
    protected:

        Type **table;
        Type *ptrTable;
        size_t rows;
        size_t columns;

        Matrix() { }

        void swapMatrices(Matrix<Type> &m) {
            Type *tmp_ptrTable = ptrTable;
            size_t tmp_rows = rows;
            size_t tmp_columns = columns;
            ptrTable = m.ptrTable;
            rows = m.rows;
            columns = m.columns;
            m.ptrTable = tmp_ptrTable;
            m.rows = tmp_rows;
            m.columns = tmp_columns;
            Type **tmp_table = table;
            table = m.table;
            m.table = tmp_table;
        }

    public:

        class Exception : public std::exception {
            char const *info;
        public:
            explicit Exception(char const *info) : info(info) { }

            virtual char const *what() const throw() { return info; }
        };

        Matrix(size_t rows, size_t columns) : rows(rows), columns(columns) {
            if (rows == 0 || columns == 0) throw -2;
            ptrTable = (Type *) calloc(rows * columns, sizeof(Type));
            table = (Type **) malloc(rows * sizeof(Type *));
            if (ptrTable == NULL || table == NULL) throw Exception("Cannot allocate memory, function Matrix<T>::Matrix(size_t,size_t)");
            for (size_t i = 0; i < rows; ++i)
                table[i] = &ptrTable[i * columns];
        }

        Matrix(Matrix<Type> const &m) : rows(m.rows), columns(m.columns) {
            ptrTable = (Type *) malloc(rows * columns * sizeof(Type));
            table = (Type **) malloc(rows * sizeof(Type *));
            if (ptrTable == NULL || table == NULL) throw Exception("Cannot allocate memory, function Matrix<T>::Matrix(Matrix<T> const &)");
            memcpy(ptrTable, m.ptrTable, rows * columns * sizeof(Type));
            for (size_t i = 0; i < rows; ++i)
                table[i] = &ptrTable[i * columns];
        }

        Matrix(Vector<Type> const &v) : rows(v.getRows()), columns(v.getColumns()) {
            ptrTable = (Type *) malloc(v.getLength() * sizeof(Type));
            table = (Type **) malloc(rows * sizeof(Type *));
            if (ptrTable == NULL || table == NULL) throw Exception("Cannot allocate memory, function Matrix<T>::Matrix(Vector<T> const &)");
            for (size_t i = 0; i < rows; ++i)
                table[i] = &ptrTable[i * columns];
            memcpy(ptrTable, v.tablePtr(), v.getLength() * sizeof(Type));
        }

        ~Matrix() {
            free(ptrTable);
            free(table);
        }

        Matrix<Type> const &operator=(Matrix<Type> const &m) {
            if (rows != m.rows || columns != m.columns) throw Exception("Size of matrices are different, function Matrix<T>::operator=(Matrix<T> const &)");
            memcpy(ptrTable, m.ptrTable, rows * columns * sizeof(Type));
        }

        inline Type const &operator()(size_t row, size_t col) const { return table[row][col]; }
        inline Type &operator()(size_t row, size_t col) { return table[row][col]; }

        inline size_t getRows() const { return rows; }
        inline size_t getColumns() const { return columns; }

        inline Type const &operator()(size_t i) const { return ptrTable[i]; }
        inline Type &operator()(size_t i) { return ptrTable[i]; }

        inline size_t length() const { return columns * rows; }

        inline bool isVector() const { return columns == 1 || rows == 1; }

        inline bool isScalar() const { return columns == 1 && rows == 1; }

        Matrix<Type> const &transpose() {
            Matrix<Type> matrix(columns, rows);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    matrix.table[j][i] = table[i][j];
            swapMatrices(matrix);
            return *this;
        }

        Matrix<Type> const &operator+=(Matrix<Type> const &m) {
            if (rows != m.rows || columns != m.columns) throw Exception("Size of matrices are different, function Matrix<T>::operator+=(Matrix<T> const &)");
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    table[i][j] += m.table[i][j];
            return *this;
        }

        Matrix<Type> const &operator-=(Matrix<Type> const &m) {
            if (rows != m.rows || columns != m.columns) throw Exception("Size of matrices are different, function Matrix<T>::operator-=(Matrix<T> const &)");
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    table[i][j] -= m.table[i][j];
            return *this;
        }

        Matrix<Type> const &operator*=(Matrix<Type> const &m) {
            if (columns != m.rows) throw Exception("Size of matrices are different, function Matrix<T>::operator*=(Matrix<T> const &)");
            Matrix<Type> matrix(rows, m.columns);
            for (size_t i = 0; i < matrix.rows; ++i)
                for (size_t j = 0; j < matrix.columns; ++j)
                    for (size_t k = 0; k < columns; ++k)
                        matrix.table[i][j] += table[i][k] * m.table[k][j];
            swapMatrices(matrix);
            return *this;
        }

        Matrix<Type> const &operator*=(Type const &m) {
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    table[i][j] *= m;
            return *this;
        }

        Matrix<Type> const &operator/=(Type const &m) {
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    table[i][j] /= m;
            return *this;
        }


        Matrix<Type> operator+(Matrix<Type> const &m) const {
            if (rows != m.rows || columns != m.columns) throw Exception("Size of matrices are different, function Matrix<T>::operator+(Matrix<T> const &)");
            Matrix<Type> matrix(*this);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    matrix.table[i][j] += m.table[i][j];
            return matrix;
        }

        Matrix<Type> operator-(Matrix<Type> const &m) const {
            if (rows != m.rows || columns != m.columns) throw Exception("Size of matrices are different, function Matrix<T>::operator+(Matrix<T> const &)");
            Matrix<Type> matrix(*this);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    matrix.table[i][j] -= m.table[i][j];
            return matrix;
        }

        Matrix<Type> operator*(Matrix<Type> const &m) const {
            if (columns != m.rows) throw Exception("Size of matrices are different, function Matrix<T>::operator*(Matrix<T> const &)");
            Matrix<Type> matrix(rows, m.columns);
            for (size_t i = 0; i < matrix.rows; ++i)
                for (size_t j = 0; j < matrix.columns; ++j)
                    for (size_t k = 0; k < columns; ++k)
                        matrix.table[i][j] += table[i][k] * m.table[k][j];
            return matrix;
        }

        Matrix<Type> operator*(Type const &m) const {
            Matrix<Type> matrix(*this);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    matrix.table[i][j] *= m;
            return matrix;
        }

        Matrix<Type> operator/(Type const &m) const {
            Matrix<Type> matrix(*this);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    matrix.table[i][j] /= m;
            return matrix;
        }

    };

}

#endif //__Matrix_H_