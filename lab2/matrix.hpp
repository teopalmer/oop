#pragma once
#include <cstdlib>
#include <iostream>
#include "basematrix.hpp"
template <class T>
class Matrix: public BaseMatrix
{
    public:
        explicit Matrix();
        explicit Matrix(size_t rows, size_t cols);
        explicit Matrix(size_t rows, size_t cols, const T& fill);

        ~Matrix();

        void printMatrix();

    private:
        T **matrix;
};

template<class T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
    this->setRows(rows);
    this->setCols(cols);
    this->setSize();
    this->matrix = (T**)malloc(rows * sizeof(T*) + rows * cols * sizeof(T));
    for (int i = 0; i < rows; i++)
    {
        this->matrix[i] = (T*)(this->matrix + rows * sizeof(T*) + i * cols * sizeof(T));
    }
}

template<class T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T &fill)
{
    this->setRows(rows);
    this->setCols(cols);
    this->setSize();
    this->matrix = (T**)malloc(rows * sizeof(T*) + rows * cols * sizeof(T));
    for (int i = 0; i < rows; i++)
    {
        this->matrix[i] = (T*)(this->matrix + rows * sizeof(T*) + i * cols * sizeof(T));
        for (int j = 0; j < cols; j++)
        {
            this->matrix[i][j] = fill;
        }
    }
}

template<class T>
Matrix<T>::Matrix() {
    this->setRows(0);
    this->setCols(0);
    this->setSize();
    this->matrix = nullptr;
}

template<class T>
Matrix<T>::~Matrix()
{
    size_t rows = this->getRows();
    size_t cols = this->getCols();
    for (int i = 0; i < rows; i ++)
    {
        matrix[i].free();
    }
}
