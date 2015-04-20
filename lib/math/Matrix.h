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
#include <type_traits>
#include "Vector.h"
#include "myMath.h"



namespace geox {

    template<class T>
    class Matrix {
        static_assert(std::is_arithmetic<T>::value || std::is_same<T, complex>::value,
                      "\nMatrix<T> template is not supported.\n");

        T *elements_;
        size_t rows_;
        size_t columns_;

        Matrix(): elements_(nullptr), rows_(0), columns_(0) {}

        class Exception : public std::exception {
            char const *info;
        public:
            explicit Exception(char const *info) : info(info) { }
            virtual char const *what() const throw() { return info; }
        };

    protected:

        inline T *elementsPtr() { return elements_; }
        inline void swapMatrices(Matrix &m) {
            // pointers
            T *tmpElements = m.elements_;
            m.elements_ = elements_;
            elements_ = tmpElements;
            // rows
            size_t tmp = m.rows_;
            m.rows_ = rows_;
            rows_ = tmp;
            // columns
            tmp = m.columns_;
            m.columns_ = columns_;
            columns_ = tmp;
        }

    public:

        Matrix(size_t rows, size_t columns): rows_(rows), columns_(columns) {
            elements_ = std::calloc(rows_*columns_, sizeof(T));
            if (elements_ == nullptr) throw Exception("Cannot allocate memory, function: Matrix<T>::Matrix(size_t,size_t)");
        }
        Matrix(Matrix const &m): rows_(m.rows_), columns_(m.columns_) {
            size_t size = rows_*columns_*sizeof(T);
            elements_ = std::malloc(size);
            if (elements_ == nullptr) throw Exception("Cannot allocate memory, function: Matrix<T>::Matrix(Matrix<T> const &)");
            std::memcpy(elements_, m.elements_, size);
        }
        Matrix(Vector<T> const &v): rows_(v.getRows()), columns_(v.getColumns()) {
            size_t size = rows_*columns_*sizeof(T);
            elements_ = std::malloc(size);
            if (elements_ == nullptr) throw Exception("Cannot allocate memory, function: Matrix<T>::Matrix(Vector<T> const &)");
            std::memcpy(elements_, v.elements_, size);
        }
        ~Matrix() { if (elements_ != nullptr) free(elements_); }

        Matrix &operator=(Matrix const &matrix) {
            if (rows_ != m.rows_ || columns_ != m.columns_) throw Exception("Size of matrices are different, function: Matrix<T>::operator=(Matrix<T> const &)");
            memcpy(elements_, matrix.elements_, rows_*columns_*sizeof(T));
            return *this;
        }

        inline T const &operator[](size_t i) const {
            if (i >= columns_*rows_) Exception("Cannot access to memory, function: Matrix<T>::operator[](size_t)");
            return elements_[i];
        }
        inline T &operator[](size_t i) {
            if (i >= columns_*rows_) Exception("Cannot access to memory, function: Matrix<T>::operator[](size_t)");
            return elements_[i];
        }

        inline T const &operator()(size_t i) const { return elements_[i]; }
        inline T &operator()(size_t i) { return elements_[i]; }
        inline T const &operator()(size_t row, size_t col) const { return elements_[row*columns_+col]; }
        inline T &operator()(size_t row, size_t col) { return elements_[row*columns_+col]; }

        inline size_t getRows() const { return rows_; }
        inline size_t getColumns() const { return columns_; }
        inline size_t size() const { return columns_ * rows_; }

        inline bool isVector() const { return columns_ == 1 || rows_ == 1; }
        inline bool isScalar() const { return columns_ == 1 && rows_ == 1; }



        Matrix &transpose() {
            Matrix<T> matrix(columns_, rows_);
            for (size_t i = 0; i < rows_; ++i)
                for (size_t j = 0; j < columns_; ++j)
                    matrix.table[j][i] = table[i][j];
            swapMatrices(matrix);
            return *this;
        }



        Matrix &operator+=(Matrix const &m) {
            if (rows_ != m.rows_ || columns_ != m.columns_) throw Exception("Size of matrices are different, function: Matrix<T>::operator+=(Matrix<T> const &)");
            for (size_t i = 0; i < columns_*rows_; ++i) operator()(i) += m(i);
            return *this;
        }

        Matrix &operator-=(Matrix const &m) {
            if (rows_ != m.rows_ || columns_ != m.columns_) throw Exception("Size of matrices are different, function: Matrix<T>::operator-=(Matrix<T> const &)");
            for (size_t i = 0; i < columns_*rows_; ++i) operator()(i) -= m(i);
            return *this;
        }

        Matrix &operator*=(Matrix const &m) {
            if (columns_ != m.rows_) throw Exception("Size of matrices are different, function Matrix<T>::operator*=(Matrix<T> const &)");
            Matrix<T> matrix(rows_, m.columns_);
            for (size_t i = 0; i < matrix.rows_; ++i)
                for (size_t j = 0; j < matrix.columns_; ++j)
                    for (size_t k = 0; k < columns_; ++k)
                        matrix.elements_[i][j] += elements_[i][k] * m.elements_[k][j];
            swapMatrices(matrix);
            return *this;
        }

        Matrix &operator*=(T const &scalar) {
            for (size_t i = 0; i < columns_*rows_; ++i) operator()(i) += scalar;
            return *this;
        }



        Matrix operator+(Matrix const &m) const {
            if (rows_ != m.rows_ || columns_ != m.columns_) throw Exception("Size of matrices are different, function: Matrix<T>::operator+(Matrix<T> const &)");
            Matrix<T> matrix(*this);
            for (size_t i = 0; i < columns_*rows_; ++i) matrix(i) += m(i);
            return matrix;
        }

        Matrix operator-(Matrix const &m) const {
            if (rows_ != m.rows_ || columns_ != m.columns_) throw Exception("Size of matrices are different, function: Matrix<T>::operator-(Matrix<T> const &)");
            Matrix<T> matrix(*this);
            for (size_t i = 0; i < columns_*rows_; ++i) matrix(i) -= m(i);
            return matrix;
        }

        Matrix operator*(Matrix const &m) const {
            if (columns_ != m.rows_) throw Exception("Size of matrices are different, function Matrix<T>::operator*(Matrix<T> const &)");
            Matrix<T> matrix(rows_, m.columns_);
            for (size_t i = 0; i < matrix.rows_; ++i)
                for (size_t j = 0; j < matrix.columns_; ++j)
                    for (size_t k = 0; k < columns_; ++k)
                        matrix.elements_[i][j] += elements_[i][k] * m.elements_[k][j];
            return matrix;
        }

        Matrix operator*(T const &scalar) const {
            Matrix<T> matrix(*this);
            for (size_t i = 0; i < columns_*rows_; ++i) matrix(i) += scalar;
            return matrix;
        }

    };

    template<class Type>
    class Matrix2 {
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

        Matrix2(size_t rows, size_t columns) : rows(rows), columns(columns) {
            if (rows == 0 || columns == 0) throw -2;
            ptrTable = (Type *) calloc(rows * columns, sizeof(Type));
            table = (Type **) malloc(rows * sizeof(Type *));
            if (ptrTable == NULL || table == NULL) throw Exception("Cannot allocate memory, function Matrix<T>::Matrix(size_t,size_t)");
            for (size_t i = 0; i < rows; ++i)
                table[i] = &ptrTable[i * columns];
        }

        Matrix2(Matrix<Type> const &m) : rows(m.rows), columns(m.columns) {
            ptrTable = (Type *) malloc(rows * columns * sizeof(Type));
            table = (Type **) malloc(rows * sizeof(Type *));
            if (ptrTable == NULL || table == NULL) throw Exception("Cannot allocate memory, function Matrix<T>::Matrix(Matrix<T> const &)");
            memcpy(ptrTable, m.ptrTable, rows * columns * sizeof(Type));
            for (size_t i = 0; i < rows; ++i)
                table[i] = &ptrTable[i * columns];
        }

        Matrix2(Vector<Type> const &v) : rows(v.getRows()), columns(v.getColumns()) {
            ptrTable = (Type *) malloc(v.getLength() * sizeof(Type));
            table = (Type **) malloc(rows * sizeof(Type *));
            if (ptrTable == NULL || table == NULL) throw Exception("Cannot allocate memory, function Matrix<T>::Matrix(Vector<T> const &)");
            for (size_t i = 0; i < rows; ++i)
                table[i] = &ptrTable[i * columns];
            memcpy(ptrTable, v.tablePtr(), v.getLength() * sizeof(Type));
        }

        ~Matrix2() {
            free(ptrTable);
            free(table);
        }

        Matrix2<Type> const &operator=(Matrix2<Type> const &m) {
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

        Matrix2<Type> const &transpose() {
            Matrix<Type> matrix(columns, rows);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    matrix.table[j][i] = table[i][j];
            swapMatrices(matrix);
            return *this;
        }

        Matrix2<Type> const &operator+=(Matrix2<Type> const &m) {
            if (rows != m.rows || columns != m.columns) throw Exception("Size of matrices are different, function Matrix<T>::operator+=(Matrix<T> const &)");
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    table[i][j] += m.table[i][j];
            return *this;
        }

        Matrix2<Type> const &operator-=(Matrix2<Type> const &m) {
            if (rows != m.rows || columns != m.columns) throw Exception("Size of matrices are different, function Matrix<T>::operator-=(Matrix<T> const &)");
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    table[i][j] -= m.table[i][j];
            return *this;
        }

        Matrix2<Type> const &operator*=(Matrix2<Type> const &m) {
            if (columns != m.rows) throw Exception("Size of matrices are different, function Matrix<T>::operator*=(Matrix<T> const &)");
            Matrix2<Type> matrix(rows, m.columns);
            for (size_t i = 0; i < matrix.rows; ++i)
                for (size_t j = 0; j < matrix.columns; ++j)
                    for (size_t k = 0; k < columns; ++k)
                        matrix.table[i][j] += table[i][k] * m.table[k][j];
            swapMatrices(matrix);
            return *this;
        }

        Matrix2<Type> const &operator*=(Type const &m) {
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    table[i][j] *= m;
            return *this;
        }

        Matrix2<Type> const &operator/=(Type const &m) {
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    table[i][j] /= m;
            return *this;
        }


        Matrix2<Type> operator+(Matrix2<Type> const &m) const {
            if (rows != m.rows || columns != m.columns) throw Exception("Size of matrices are different, function Matrix<T>::operator+(Matrix<T> const &)");
            Matrix2<Type> matrix(*this);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    matrix.table[i][j] += m.table[i][j];
            return matrix;
        }

        Matrix2<Type> operator-(Matrix2<Type> const &m) const {
            if (rows != m.rows || columns != m.columns) throw Exception("Size of matrices are different, function Matrix<T>::operator+(Matrix<T> const &)");
            Matrix2<Type> matrix(*this);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    matrix.table[i][j] -= m.table[i][j];
            return matrix;
        }

        Matrix2<Type> operator*(Matrix2<Type> const &m) const {
            if (columns != m.rows) throw Exception("Size of matrices are different, function Matrix<T>::operator*(Matrix<T> const &)");
            Matrix2<Type> matrix(rows, m.columns);
            for (size_t i = 0; i < matrix.rows; ++i)
                for (size_t j = 0; j < matrix.columns; ++j)
                    for (size_t k = 0; k < columns; ++k)
                        matrix.table[i][j] += table[i][k] * m.table[k][j];
            return matrix;
        }

        Matrix2<Type> operator*(Type const &m) const {
            Matrix2<Type> matrix(*this);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    matrix.table[i][j] *= m;
            return matrix;
        }

        Matrix2<Type> operator/(Type const &m) const {
            Matrix2<Type> matrix(*this);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < columns; ++j)
                    matrix.table[i][j] /= m;
            return matrix;
        }

    };

}

#endif //__Matrix_H_