#ifndef matrix_h
#define matrix_h

#include <cstdio>
#include <memory>
#include <typeinfo>
#include <ctime>

#include "base_matrix.h"
#include "errors.h"
#include "base_iterator.h"
#include "const_iterator.h"
#include "matrix_iterator.h"
#include "matrix_iterator_math.h"
#include "const_math.h"

using namespace iterator_core;

template <typename T>
class Matrix : public matrix_core::base_matrix
{
public:
    Matrix(unsigned int n, unsigned int m); //финализатор
    Matrix(unsigned int n, unsigned int m, T fill); //T
    //Matrix(unsigned int n, unsigned int m, T** matrix);
    explicit Matrix(const Matrix<T> &mtr);
    Matrix(Matrix<T>&& mtr) noexcept ;
    Matrix(std::initializer_list<std::initializer_list<T>> lst);
    //+ construct for c matrix
    //+ construct iterator begin end

    ~Matrix();

    Matrix<T>& operator =(const Matrix<T> &mtr);
    Matrix<T>& operator =(Matrix<T> &&mtr) noexcept ;

    unsigned int get_row() const; //row
    unsigned int get_column() const; //column

    const T& get_value_by_index(unsigned int i, unsigned int j) const;
    T& get_value_by_index(unsigned int i, unsigned int j);// not const

    void set_value_by_index(unsigned int i, unsigned int j, const T& value);
    //name
    T& operator ()(unsigned int i, unsigned int j);
    const T& operator ()(unsigned int i, unsigned int j) const;

    Matrix<T> operator -(const Matrix<T> &mtr1) const; //group
    Matrix<T> operator -(const T& num) const;
    Matrix<T>& operator -=(const Matrix<T>& mtr);
    void sub(Matrix<T>& A);
    void sub(T element);

    Matrix<T> operator +(const Matrix<T>& mtr1) const;
    Matrix<T> operator +(const T& num) const;
    Matrix<T>& operator +=(const Matrix<T>& mtr);
    void add(Matrix<T>& A);
    void add(T element);

    Matrix<T> operator *(const Matrix<T>& mtr1) const;
    Matrix<T> operator *(const T& num) const;
    Matrix<T>& operator *=(const Matrix<T>& mtr);
    void mult(Matrix<T>& A);
    void mult(T element);

    Matrix<T> operator /(const T& num) const;
    void divide(T element);

    template<typename _T>
    friend std::ostream& operator << (std::ostream& os, const Matrix<_T>& matr);

    matrix_iterator<T> begin();
    const_iterator<T> begin() const;
    matrix_iterator<T> cbegin() const;

    matrix_iterator<T> end();
    const_iterator<T> end() const;
    matrix_iterator<T> cend() const;

    void clone_matrix(const Matrix<T>& matrix);
    Matrix<T> inverse(); //name
    Matrix<T> &transposition();
    Matrix<T> transposition(Matrix<T> matr); //transpon new matrix

    static Matrix<T> matrix_det(size_t exclude_row, size_t exclude_column, const Matrix<T>& matrix);
    static T determinant_value(const Matrix<T>& matrix); //-count
    T determinant();


    bool is_square();
    void identity_matrix();

    class Row
    {
        friend class Matrix;
    public:
        const T& operator[](size_t col) const;
        T& operator[](size_t col);

    private:
        Row(const Matrix<T> &parent, size_t row) : parent(parent), row(row) {}
        const Matrix& parent;
        size_t row;
    };

    const Matrix::Row operator[] (size_t row) const;
    Matrix::Row operator[] (size_t row);
    
private:
    void auto_fill();
    void fill(float fill);
    unsigned int n{};
    unsigned int m{};
    std::shared_ptr<T> mtr;
};

template<typename T>
T &Matrix<T>::Row::operator[](size_t col) {
    if (col >= this->parent.get_columns())
    {
        time_t t_time;
        t_time = time(nullptr);
        throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
    }
    return parent.mtr.get()[row * parent.m + col];
}

template<typename T>
const T &Matrix<T>::Row::operator[](size_t col) const {
    if (col >= this->parent.get_columns())
    {
        time_t t_time;
        t_time = time(nullptr);
        throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
    }
    return parent.mtr.get()[row * parent.m + col];
}


#endif /* matrix_h */
