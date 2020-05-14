#pragma once
#include <cstdlib>
#include <iostream>
#include "basematrix.hpp"

template <class T>
class Matrix: public BaseMatrix
{
    public:
        explicit Matrix(): Matrix(nullptr) {setRows(0); setColumns(0);}
        explicit Matrix(size_t rows, size_t cols);
        explicit Matrix(size_t rows, size_t cols, const T& fill);

    private:
        T **matrix;
};

template<class T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
    this->setRows(rows);
    this->setColumns(cols);
    this->setSize();
    this->matrix = (T**)malloc(rows * sizeof(T*) + rows * cols * sizeof(T));
    for (int i = 0; i < this->rows; i++)
    {
        this->matrix[i] = (T*)(this->matrix + rows * sizeof(T*) + i * cols * sizeof(T));
    }
}

template<class T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T &fill)
{
    this->setRows(rows);
    this->setColumns(cols);
    this->setSize();
    this->matrix = (T**)malloc(rows * sizeof(T*) + rows * cols * sizeof(T));
    for (int i = 0; i < this->rows; i++)
    {
        this->matrix[i] = (T*)(this->matrix + rows * sizeof(T*) + i * cols * sizeof(T));
        for (int j = 0; j < this->cols; j++)
        {
            this->matrix[i][j] = fill;
        }
    }
};
