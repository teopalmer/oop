#ifndef matrix_iterator_h
#define matrix_iterator_h

#include "base_iterator.h"
#include <iterator>
using namespace iterator_core;

#include "base_iterator.h"
using namespace iterator_core;

template<typename ValueType>
class matrix_iterator : public base_iterator<ValueType> //stlbase
{
public:
    matrix_iterator(const matrix_iterator<ValueType>&);
    ValueType &operator *();
    ValueType *operator ->();
    const ValueType &operator *() const;
    const ValueType *operator ->() const;
    
    explicit matrix_iterator(ValueType *);
};

#endif /* matrix_iterator_h */
