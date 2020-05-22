#ifndef matrix_h
#define matrix_h

#include <stdio.h>
#include <memory>
#include <typeinfo>
#include <time.h>

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
    Matrix(unsigned int n, unsigned int m);
    Matrix(unsigned int n, unsigned int m, float fill);
    //Matrix(unsigned int n, unsigned int m, T** matrix);
    Matrix(const Matrix<T> &mtr);
    Matrix(Matrix<T>&& mtr);
    Matrix(std::initializer_list<std::initializer_list<T>> lst);
    
    ~Matrix();
    
    Matrix<T>& operator =(const Matrix<T> &mtr);
    Matrix<T>& operator =(Matrix<T> &&mtr);
    //Matrix<T>& operator =(std::initializer_list<std::initializer_list<T>> lst);
    
    unsigned int get_n() const;
    unsigned int get_m() const;
    
    const T& get_value_by_index(unsigned int i, unsigned int j) const;
    T& operator ()(unsigned int i, unsigned int j);
    const T& operator ()(unsigned int i, unsigned int j) const;
    
    Matrix<T> operator -(const Matrix<T> &mtr1) const;
    Matrix<T> operator -(const T& num) const;
    
    Matrix<T> operator +(const Matrix<T>& mtr1) const;
    Matrix<T> operator +(const T& num) const;
    
    Matrix<T> operator *(const Matrix<T>& mtr1) const;
    Matrix<T> operator *(const T& num) const;
    
    Matrix<T> operator /(const T& num) const;
    
    Matrix<T>& operator +=(const Matrix<T>& mtr);
    
    Matrix<T>& operator -=(const Matrix<T>& mtr);
    Matrix<T>& operator *=(const Matrix<T>& mtr);
    
    template<typename _T>
    friend std::ostream& operator <<(std::ostream& os, const Matrix<_T>& matr);

    void add(Matrix<T>& A);
    void add(T element);
    void sub(Matrix<T>& A);
    void sub(T element);
    void mult(Matrix<T>& A);
    void mult(T element);
    void divide(T element);
    
    matrix_iterator<T> begin();
    matrix_iterator<T> end();
    
    const_iterator<T> begin() const;
    const_iterator<T> end() const;
    
    void clone_matrix(const Matrix<T>& matrix);
    Matrix<T> inverse_gauss();
    Matrix<T> &transposition();
  
    static Matrix<T> matrix_det(size_t count, size_t exclude_row, size_t exclude_column, const Matrix<T>& matrix);
    static T determinant_value(const size_t count, const Matrix<T>& matrix);
    T determinant();
    
    void set_value_by_index(unsigned int i, unsigned int j, const T& value);
    bool is_square();
    void identity_matrix();
    
    class Row
    {
        friend class Matrix;
    public:
        const T& operator[](size_t col) const
        {
            if (col >= this->parent.get_columns())
            {
                time_t t_time;
                t_time = time(nullptr);
                throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
            }
            return parent.mtr.get()[row * parent.m + col];
        }

        T& operator[](size_t col)
        {
            if (col >= this->parent.get_columns())
            {
                time_t t_time;
                t_time = time(nullptr);
                throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
            }
            return parent.mtr.get()[row * parent.m + col];
        }
    private:
        Row(const Matrix<T> &parent, size_t row) : parent(parent), row(row) {}
        const Matrix& parent;
        size_t row;
    };
    
    const Row operator[] (size_t row) const
    {
        if (row >= this->get_rows())
        {
            time_t t_time;
            t_time = time(nullptr);
            throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
        }
        return Row(*this, row);
    }
    
private:
    void auto_fill();
    void fill(float fill);
    unsigned int n{};
    unsigned int m{};
    std::shared_ptr<T> mtr;
};


#endif /* matrix_h */
