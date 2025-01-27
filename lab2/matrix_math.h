#ifndef matrix_math_h
#define matrix_math_h

#include <math.h>

#include "matrix.h"
#include "base_iterator.h"
#include "const_iterator.h"
#include "matrix_iterator.h"
#include "matrix_iterator_math.h"
#include "const_math.h"

using namespace iterator_core;

//конструкторы
template <typename T>
Matrix<T>::Matrix(unsigned int n, unsigned int m)
{
    time_t t_time;
    t_time = time(nullptr);
    if (n == 0 || m == 0) throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Incorrect size");
    this->elements_count = n * m;
    this->n = n;
    this->m = m;
    
    try
    {
        this->mtr = std::shared_ptr<T>(new T[elements_count]);
        this->auto_fill();
    }
    
    catch (std::bad_alloc)
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &mtr):base_matrix()
{
    time_t t_time;
    t_time = time(nullptr);
    this->n = mtr.get_row();
    this->m = mtr.get_column();
    this->elements_count = mtr.size();
    
    try
    {
        this->mtr = std::shared_ptr<T>(new T[elements_count]);
    }
    
    catch(std::bad_alloc)
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
    }
    for (unsigned int i = 0; i < this->n; ++i)
    {
        for (unsigned int j = 0; j < this->m; ++j)
        {
            this->mtr.get()[i * m + j] = mtr.mtr.get()[i * m + j];
        }
    }
}
template<typename T>
Matrix<T>::Matrix(Matrix<T>&& mtr) noexcept
{
    time_t t_time;
    t_time = time(nullptr);
    this->n = mtr.get_row();
    this->m = mtr.get_column();
    this->elements_count = mtr.size();
    try
    {
        this->mtr = std::shared_ptr<T>(new T[n * m]);
    }
    
    catch (std::bad_alloc)
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
    }
    
    for (unsigned int i = 0; i < n; ++i)
    {
        for (unsigned int j = 0; j < m; ++j)
        {
            this->mtr.get()[i * m + j] = mtr.mtr.get()[i * m + j];
        }
    }
}

/*template<typename T>
Matrix<T>::Matrix(unsigned int n, unsigned int m, T **matrix)
{
    time_t t_time;
    t_time = time(nullptr);
    if (n == 0 || m == 0) throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Zero size");
    this->elements_count = n * m;
    this->n = n;
    this->m = m;
    
    try
    {
        this->mtr = new T[elements_count];
        this->auto_fill();
        *matrix = this->mtr;
    }
    
    catch (std::bad_alloc)
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
    }
}*/

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> lst)
{
    time_t t_time;
    t_time = time(nullptr);
    this->n = lst.size();
    this->m = lst.begin()->size();
    this->elements_count = n * m;
    auto iter_i = lst.begin();
    try
    {
        this->mtr = std::shared_ptr<T>(new T[n * m]);
    }
    catch (std::bad_alloc&)
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
    }
    
    for (unsigned int i = 0; iter_i != lst.end(); i++, iter_i++)
    {
        if (this->m != iter_i->size()) throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
        else
        {
            auto iter_j = iter_i->begin();
            for (unsigned int j = 0; iter_j != iter_i->end(); ++j, ++iter_j)
            {
                this->mtr.get()[i * this->m + j] = *iter_j;
            }
        }
    }
}

template<typename T>
const T& Matrix<T>::get_value_by_index(unsigned int i, unsigned int j) const
{
    time_t t_time;
    t_time = time(nullptr);
    if (i >= this->n || j >= this->m)
    {
        throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
    }
    
    else
    {
        if (this->mtr)
        {
            return mtr.get()[i * this->m + j];
        }
        
        else
        {
            throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
        }
    }
}

template<typename T>
void Matrix<T>::set_value_by_index(unsigned int i, unsigned int j, const T &value)
{
    time_t t_time;
    t_time = time(nullptr);
    if (i >= this->n || j >= this->m)
    {
        throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
    }
    
    else
    {
        if (this->mtr)
        {
            this->mtr.get()[i * this->m + j] = value;
        }
        
        else
        {
            throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
        }
    }
}

template<typename T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T> &mtr)
{
    time_t t_time;
    t_time = time(nullptr);
    unsigned int n_mtr = mtr.get_row();
    unsigned int m_mtr = mtr.get_column();
    this->n = n_mtr;
    this->m = m_mtr;
    this->elements_count = mtr.elements_count;
    try
    {
        this->mtr = std::shared_ptr<T>(new T[n * m]);
    }
    
    catch (std::bad_alloc&)
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
    }
    
    if (this->m == m_mtr && this->n == n_mtr)
    {
        for (unsigned int i = 0; i < n_mtr; i++)
        {
            for (unsigned int j = 0; j < m_mtr; j++)
            {
                this->mtr.get()[i * m + j] = mtr.mtr.get()[i * m + j];
            }
        }
    }
    
    else
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
    }
    
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator =(Matrix<T> &&mtr) noexcept
{
    time_t t_time;
    t_time = time(nullptr);
    unsigned int n_mtr = mtr.get_row();
    unsigned int m_mtr = mtr.get_column();
    this->n = n_mtr;
    this->m = m_mtr;
    this->elements_count = mtr.elements_count;
    try
    {
        this->mtr = std::shared_ptr<T>(new T[n * m]);
    }
    
    catch (std::bad_alloc&)
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
    }
    
    if (this->m == m_mtr && this->n == n_mtr)
    {
        for (unsigned int i = 0; i < n_mtr; i++)
        {
            for (unsigned int j = 0; j < m_mtr; j++)
            {
                this->mtr.get()[i * m + j] = mtr.mtr.get()[i * m + j];
            }
        }
    }
    
    else
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
    }
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator +=(const Matrix<T> &mtr)
{
    time_t t_time;
    t_time = time(nullptr);
    unsigned int n_mtr = mtr.get_row();
    unsigned int m_mtr = mtr.get_column();
    if (this->m == m_mtr && this->n == n_mtr)
    {
        for (unsigned int i = 0; i < n_mtr; i++)
        {
            for (unsigned int j = 0; j < m_mtr; j++)
            {
                this->mtr.get()[i * m + j] += mtr.mtr.get()[i * m + j];
            }
        }
    }
    else
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
    }
    return *this;
}
template<typename T>
Matrix<T> &Matrix<T>::operator -=(const Matrix<T> &mtr)
{
    time_t t_time;
    t_time = time(nullptr);
    unsigned int n_mtr = mtr.get_row();
    unsigned int m_mtr = mtr.get_column();
    if (this->m == m_mtr && this->n == n_mtr)
    {
        for (unsigned int i = 0; i < n_mtr; i++)
        {
            for (unsigned int j = 0; j < m_mtr; j++)
            {
                this->mtr.get()[i * m + j] -= mtr.mtr.get()[i * m + j];
            }
        }
    }
    else
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
    }
    return *this;
}


template<typename T>
Matrix<T> Matrix<T>::operator +(const Matrix<T> &mtr1) const
{
    time_t t_time;
    t_time = time(nullptr);
    if (mtr1.get_row() == this->n && mtr1.get_row() == this->m)
    {
        
        Matrix<T> res(mtr1.get_row(), mtr1.get_column());
        for (unsigned int i = 0; i < res.get_row(); ++i)
        {
            for (unsigned int j = 0; j < res.get_column(); ++j)
            {
                res.mtr.get()[i * mtr1.get_column() + j] = this->mtr.get()[i * mtr1.get_column() + j] + mtr1.mtr.get()[i * mtr1.get_column() + j];
            }
        }
        return res;
    }
    else
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
    }
}
template<typename T>
Matrix<T> Matrix<T>::operator +(const T& num) const
{
    time_t t_time;
    t_time = time(nullptr);
    Matrix<T> res = Matrix<T>(n, m);
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            res.mtr[i * m + j] = this->mtr[i * m + j] + num;
        }
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator -(const Matrix<T> &mtr1) const
{
    time_t t_time;
    t_time = time(nullptr);
    if (mtr1.get_row() == this->n && mtr1.get_row() == this->m)
    {
        Matrix<T> res = Matrix<T>(mtr1.get_row(), mtr1.get_column());
        for (unsigned int i = 0; i < res.get_row(); ++i)
        {
            for (unsigned int j = 0; j < res.get_column(); ++j)
            {
                res.mtr.get()[i * mtr1.get_column() + j] = this->mtr.get()[i * this->m + j] - mtr1.mtr.get()[i * mtr1.get_column() + j];
            }
        }
        return res;
        
    }
    else
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator -(const T &num) const
{
    time_t t_time;
    t_time = time(nullptr);
    Matrix<T> res = Matrix<T>(n, m);
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            res.mtr[i * m + j] = this->mtr[i * m + j] - num;
        }
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(const Matrix<T> &mtr1) const
{
    time_t t_time;
    t_time = time(nullptr);
    if (mtr1.get_column() == this->n)
    {
        unsigned int n = this->n;
        unsigned int m = mtr1.get_column();
        unsigned int l = this->n;
        Matrix<T> res = Matrix<T>(n, m);
        for (unsigned int i = 0; i < n; i++)
        {
            for (unsigned int j = 0; j < m; j++)
            {
                double sum = 0;
                for (unsigned int k = 0; k < l; k++)
                {
                    sum += mtr1.mtr.get()[i * m + k] * this->mtr.get()[k * m + j];
                }
                res.mtr.get()[i * m + j] = sum;
            }
        }
        return res;
    }
    else
    {
        throw cannot_mult_matrix_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
    }
}
template<typename T>
Matrix<T> &Matrix<T>::operator *=(const Matrix<T> &mtr)
{
    *this = *this * mtr;
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator *(const T& num) const
{
    Matrix<T> res = Matrix<T>(n, m);
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            res.mtr[i * m + j] = this->mtr[i * m + j] * num;
        }
    }
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator /(const T& num) const
{
    Matrix<T> res = Matrix<T>(n, m);
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            res.mtr[i * m + j] = this->mtr[i * m + j] / num;
        }
    }
    return res;
}

template<typename T>
const T& Matrix<T>::operator()(unsigned int i, unsigned int j) const
{
    time_t t_time;
    t_time = time(nullptr);
    if (this->n <= i || this->m <= j) throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
    
    return this->mtr[i * this->m + j];
}


template<typename T>
T &Matrix<T>::operator ()(unsigned int i, unsigned int j)
{
    time_t t_time;
    t_time = time(nullptr);
    if (this->n <= i || this->m <= j) throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
    
    return this->mtr.get()[i * this->m + j];
}

template<typename T>
Matrix<T> Matrix<T>::inverse()
{
    time_t t_time;
    t_time = time(nullptr);
    double del = 1;
    double max = this->mtr.get()[0];
    int max_pos = 0;
    int pos_n = 0;
    int pos_m = 0;
    T determinant = 1;
    double eps = 0.000001;
    if (n != m) throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
    for (unsigned int i = 0; i < n - 1; i++)
    {
        max = mtr.get()[i * m + i];
        for (unsigned int l = i + 1; l < n; l++)
        {
            if (fabs(mtr.get()[l * m + i] - max) > eps)
            {
                max = mtr.get()[l * m + i];
                pos_n = i;
                pos_m = l;
                max_pos = l;
            }
        }
        if ((unsigned int)max_pos > i)
        {
            determinant *= -1;
            double tmp;
            for (unsigned int i = 0; i < m; i++)
            {
                tmp = mtr.get()[pos_n * m + i];
                mtr.get()[pos_n * m + i] = mtr.get()[pos_m * m + i];
                mtr.get()[pos_m * m + i] = tmp;
            }
            
        }
        for (unsigned int j = i + 1; j < n; j++)
        {
            if (mtr.get()[i * m + i] != 0)
            {
                del = mtr.get()[j * m + i] / mtr.get()[i * m + i];
            }
            for (unsigned int k = i; k < n; k++)
            {
                mtr.get()[j * m + k] -= (mtr.get()[i * m + k] * del);
            }
        }
    }
    return *this;
}

template<typename T>
void Matrix<T>::clone_matrix(const Matrix<T>& matrix)
{
    *this = matrix;
}

template<typename T>
Matrix<T>& Matrix<T>::transposition()
{
    time_t t_time;
    t_time = time(nullptr);
    if (this->get_column() == this->get_row())
    {
        for (unsigned int i = 0; i < 4; i++)
        {
            for (unsigned int j = i + 1; j <= 4; j++)
            {
                T symbol = this->mtr.get()[i * m + j];
                this->mtr.get()[i * m + j] = this->mtr.get()[j * m + i];
                this->mtr.get()[j * m + i] = symbol;
            }
        }
        return *this;
    }
    else
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
    }
}

template<typename T>
bool Matrix<T>::is_square()
{
    if (this->n == this->m)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
unsigned int Matrix<T>::get_row() const
{
    return this->n;
}

template<typename T>
unsigned int Matrix<T>::get_column() const
{
    return this->m;
}

//деструктор
template <typename T>
Matrix<T>::~Matrix()
{
    this->mtr.reset();
    this->n = 0;
    this->m = 0;
}

template<typename T>
void Matrix<T>::auto_fill()
{
    for (size_t i = 0; i < this->n; i++)
        for (size_t j = 0; j < this->m; j++)
            mtr.get()[i * m + j] = rand() % 9 + 1;
}

template<typename T>
void Matrix<T>::fill(float fill) {
    for (size_t i = 0; i < this->n; i++)
        for (size_t j = 0; j < this->m; j++)
            mtr.get()[i * m + j] = fill;
}

template<typename T>
void Matrix<T>::identity_matrix()
{
    for (size_t i = 0; i < this->n; i++)
    {
        for (size_t j = 0; j < this->m; j++)
        {
            if (i != j)
                mtr.get()[i * m + j] = 0;
            else
                mtr.get()[i * m + j] = 1;
        }
    }
            
}

template <class T>
Matrix<T> Matrix<T>::matrix_det(size_t exclude_row, size_t exclude_column, const Matrix<T>& matrix)
{
    size_t count = matrix.count;
    Matrix<T> new_matrix(count - 1, count - 1);
    size_t ki = 0, kj = 0;
    for (size_t i = 0; i < count - 1; ++i)
    {
        if (i == exclude_row)
            ki = 1;
        for (size_t j = 0; j < count - 1; ++j)
        {
            if (j == exclude_column)
                kj = 1;
            new_matrix[i][j] = matrix[i + ki][j + kj];
        }
    }
    return new_matrix;
}
template <class T>
T Matrix<T>::determinant_value(const Matrix<T>& matrix)
{
    size_t count = matrix.count;
    size_t sign = 1, new_count = count - 1;
    T det = 0;
    if (count == 1)
        return matrix[0][0];
    if (count == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    if (count > 2)
        for (size_t i = 0; i < count; ++i)
        {
            Matrix<T> new_matrix = matrix_det(count, i, 0, matrix);
            det = det + sign * matrix[i][0] * determinant_value(new_count, new_matrix);
            sign = -sign;
        }
    return det;
}

template <class T>
T Matrix<T>::determinant()
{
    if (!this->IsSquare())
    {
        time_t t_time;
        t_time = time(nullptr);
        throw is_not_square_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Matrix is not square");
    }
    T det = determinant_value(this->GetRows(), *this);
    return det;
}

template<typename _T>
std::ostream& operator << (std::ostream& os, const Matrix<_T>& matr)
{
    for (unsigned int i = 0; i < matr.get_row(); i++)
    {
        for(unsigned int j = 0; j < matr.get_column(); j++)
        {
            os << matr.mtr.get()[i * matr.get_column() + j] << " ";
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}
template<typename T>
matrix_iterator<T> Matrix<T>::begin()
{
    return matrix_iterator<T>(this->mtr.get());
}

template<typename T>
matrix_iterator<T> Matrix<T>::end()
{
    return matrix_iterator<T>(this->mtr.get() + n * m);
}

template<typename T>
const_iterator<T> Matrix<T>::begin() const
{
    return const_iterator<T>(mtr);
}

template<typename T>
const_iterator<T> Matrix<T>::end() const
{
    return const_iterator<T>(mtr + n * m);
}

template<typename T>
Matrix<T>::Matrix(unsigned int n, unsigned int m, T fill) {
    time_t t_time;
    t_time = time(nullptr);
    if (n == 0 || m == 0) throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Incorrect size");
    this->elements_count = n * m;
    this->n = n;
    this->m = m;

    try
    {
        this->mtr = std::shared_ptr<T>(new T[elements_count]);
        this->fill(fill);
    }

    catch (std::bad_alloc)
    {
        throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
    }
}

template<typename T>
void Matrix<T>::add(Matrix<T> &A) {
    *this = *this + A;
}

template<typename T>
void Matrix<T>::add(T element) {
    *this = *this + element;
}

template<typename T>
void Matrix<T>::sub(Matrix<T> &A) {
    *this = *this - A;
}

template<typename T>
void Matrix<T>::sub(T element) {
    *this = *this - element;
}

template<typename T>
void Matrix<T>::mult(Matrix<T>& A) {
    *this = *this * A;
}

template<typename T>
void Matrix<T>::mult(T element) {
    *this = *this * element;
}

template<typename T>
void Matrix<T>::divide(T element)
{
    *this = *this / element;
}

template<typename T>
matrix_iterator<T> Matrix<T>::cend() const {
    return const_iterator<T>(mtr + n * m);
}

template<typename T>
matrix_iterator<T> Matrix<T>::cbegin() const {
    return const_iterator<T>(mtr + n * m);
}

template<typename T>
Matrix<T> Matrix<T>::transposition(Matrix<T> matr) {
    time_t t_time;
    t_time = time(nullptr);
    if (this->get_column() == this->get_row())
    {
        for (unsigned int i = 0; i < 4; i++)
        {
            for (unsigned int j = i + 1; j <= 4; j++)
            {
                matr->mtr.get()[i * m + j] = this->mtr.get()[j * m + i];
                matr->mtr.get()[j * m + i] = this->mtr.get()[i * m + j];
            }
        }
        return *matr;
    }
    else
    {
        throw is_empty_exception(__FILE__, typeid(*matr).name(), __LINE__ - 4, ctime(&t_time), "Sizes should be equal");
    }
}


template<typename T>
const typename Matrix<T>::Row Matrix<T>::operator[](size_t row) const {
    if (row >= this->get_rows())
    {
        time_t t_time;
        t_time = time(nullptr);
        throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
    }
    return Row(*this, row);
}

template<typename T>
typename Matrix<T>::Row Matrix<T>::operator[](size_t row){
    if (row >= this->get_rows())
    {
        time_t t_time;
        t_time = time(nullptr);
        throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
    }
    return Row(*this, row);
}

template<typename T>
T &Matrix<T>::get_value_by_index(unsigned int i, unsigned int j) {
    time_t t_time;
    t_time = time(nullptr);
    if (i >= this->n || j >= this->m)
    {
        throw index_out_of_range_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
    }

    else
    {
        if (this->mtr)
        {
            return mtr.get()[i * this->m + j];
        }

        else
        {
            throw is_empty_exception(__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Allocation memory error");
        }
    }
}



/*template <class T>
Matrix<T> add(Matrix<T>& A, Matrix<T>& B)
{
    return A + B;
}

template <class T>
Matrix<T> add(Matrix<T>& matrix, T element)
{
    if (matrix.is_empty())
    {
        time_t t_time;
        t_time = time(nullptr);
        throw is_empty_exception(__FILE__, typeid(matrix).name(), __LINE__ - 4, ctime(&t_time), "Matrix is empty");
    }
    for (size_t i = 0; i < matrix.get_rows(); ++i)
        for (size_t j = 0; j < matrix.getc_columns(); ++j)
            matrix[i][j] += element;
    return matrix;
}

template <class T>
Matrix<T> sub(Matrix<T>& A, Matrix<T>& B)
{
    if (A.is_empty())
    {
        time_t t_time;
        t_time = time(nullptr);
        throw is_empty_exception(__FILE__, typeid(A).name(), __LINE__ - 4, ctime(&t_time), "Matrix A is Empty");
    }
    if (B.is_empty())
    {
        time_t t_time;
        t_time = time(nullptr);
        throw is_empty_exception(__FILE__, typeid(B).name(), __LINE__ - 4, ctime(&t_time), "Matrix B is Empty");
    }
    if (A != B)
    {
        time_t t_time;
        t_time = time(nullptr);
        throw is_empty_exception(__FILE__, typeid(A).name(), __LINE__ - 4, ctime(&t_time), "Matrix A != B");
    }
    Matrix<T> C = A;
    for (size_t i = 0; i < B.GetRows(); ++i)
        for (size_t j = 0; j < B.GetColumns(); ++j)
            C[i][j] -= B[i][j];
    return C;
}

template <class T>
Matrix<T> sub(Matrix<T>& matrix, T element)
{
    if (matrix.is_empty())
    {
        time_t t_time;
        t_time = time(nullptr);
        throw is_empty_exception(__FILE__, typeid(matrix).name(), __LINE__ - 4, ctime(&t_time), "Matrix is empty");
    }
    for (size_t i = 0; i < matrix.get_rows(); ++i)
        for (size_t j = 0; j < matrix.getc_columns(); ++j)
            matrix[i][j] -= element;
    return matrix;
}

template<class T>
Matrix<T> mult(Matrix<T>& matrix, T element)
{
    return matrix * element;
}


template <class T>
Matrix<T> divide(Matrix<T>& matrix, T element)
{
    if (matrix.is_empty())
    {
        time_t t_time;
        t_time = time(nullptr);
        throw is_empty_exception(__FILE__, typeid(matrix).name(), __LINE__ - 4, ctime(&t_time), "Matrix is empty");
    }
    for (size_t i = 0; i < matrix.get_rows(); ++i)
        for (size_t j = 0; j < matrix.getc_columns(); ++j)
            matrix[i][j] /= element;
    return matrix;
}*/

#endif /* matrix_math_h */
