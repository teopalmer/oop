#include "matrix.hpp"
#include <cstdio>

template<class T>
void Matrix<T>::printMatrix() {
    size_t rows = this->getRows();
    size_t cols = this->getCols();
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}