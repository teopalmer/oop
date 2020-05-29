#ifndef matrix_iterator_math_h
#define matrix_iterator_math_h

#include "matrix_iterator.h"
#include "base_iterator.h"
#include <iterator>
#include "errors.h"

using namespace iterator_core;
template<typename ValueType>
ValueType& matrix_iterator<ValueType>::operator *()
{
    return  *getCurPtr();
}

template<typename ValueType>
ValueType* matrix_iterator<ValueType>::operator ->()
{
    return getCurPtr();
}

template<typename ValueType>
const ValueType& matrix_iterator<ValueType>::operator *() const
{
    return  *getCurPtr();
}

template<typename ValueType>
const ValueType* matrix_iterator<ValueType>::operator ->() const
{
    return getCurPtr();
}

template<typename ValueType>
matrix_iterator<ValueType>::matrix_iterator(const matrix_iterator<ValueType> &iter)
: base_iterator<ValueType>(iter.ptr)
{
    return this;
}

template<typename ValueType>
matrix_iterator<ValueType>::matrix_iterator(ValueType *ptr)
: base_iterator<ValueType>(ptr)
{
    
}

template<typename ValueType>
ValueType *matrix_iterator<ValueType>::getCurPtr() const {
    if (!this->ptr.expired() && 0 <= this->index && this->index <= this->count)
    {
        shared_ptr<ValueType[]> shar = this->ptr.lock();
        return (shar.get() + index);
    }
    else
    {
        time_t t_time;
        t_time = time(nullptr);
        throw (__FILE__, typeid(*this).name(), __LINE__ - 4, ctime(&t_time), "Index out of range");
    }
}

template<typename ValueType>
matrix_iterator<ValueType>::~matrix_iterator() = default;

#endif /* matrix_iterator_math_h */
