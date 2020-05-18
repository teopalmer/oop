#include <iostream>
#include "matrix.cpp"

int main() {
    Matrix<float> A(2, 2, 3);

    Matrix<int> B(1, 1);
    Matrix<char> C;

    A.printMatrix();
    return 0;
}