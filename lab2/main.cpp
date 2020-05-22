#include <iostream>
#include <cstdlib>

#include "matrix.h"
#include "base_iterator.h"
#include "const_iterator.h"
#include "matrix_math.h"

using namespace std;

int main() {
    try {
        cout << "Constructors\n\n";

        Matrix<int> A(4, 4); //обычный
        cout << A;
        Matrix <float> K({{1, 0.5, 2}, {3, 3.2, 5}}); //ручной ввод
        cout << K;

        Matrix <int> P(2, 3, 0); //с заполнением
        cout << P;

        Matrix<int> B(A); //копирование
        cout << B;

        cout << "Addition\n\n";
        B += A;
        cout << B;

        cout << "Substraction\n\n";
        B -= A;
        cout << B;

        B.mult(A);
        cout << B;

        Matrix<int> Pk(2, 2);
        Pk.clone_matrix(B);
        cout << Pk;

        A = {{0, 1}, {2,3}};
        cout << A;


        Matrix<int> C({{1, 2, 3},
                          {4, 5, 6}});

        cout << "Get value by index\n\n";
        int value = C.get_value_by_index(0, 0);
        int val = C[0][0];
        std::cout << val;
        std::cout << value << std::endl;

        cout << "\nIs square?\n\n";
        bool issquare = C.is_square();
        cout << C << (issquare ? "Square" : "Not square") << std::endl;

        cout << "\nTransposition\n\n";
        Matrix<int> F({{1, 1, 1, 1, 1},
                          {2, 2, 2, 2, 2},
                          {3, 3, 3, 3, 3},
                          {4, 4, 4, 4, 4},
                          {5, 5, 5, 5, 5}});
        F.transposition();
        cout << F;
        Matrix<int> FT = F.transposition();
        cout << FT;

        FT.inverse_gauss();
        cout << FT;

        cout << "\nMultiplication\n\n";
        Matrix<int> D(4, 4);
        A = A * D;
        cout << D;
        Matrix<int> E(2, 2);
        B = D * E;
        cout << B;

    }
    catch (base_exception &exception) {
        cout << exception.what();
    }

    return 0;
}