#pragma once

#include <stdio.h>

using namespace std;

namespace iterator_core
{
    template<typename ValueType>
    class base_iterator
    {
    public:
        base_iterator();
        base_iterator(const base_iterator<ValueType>&);
        explicit base_iterator(ValueType*);
        virtual ~base_iterator() = 0;
        base_iterator<ValueType>& operator =(const base_iterator<ValueType>&);
        base_iterator<ValueType>& operator ++();
        base_iterator<ValueType> operator ++(int);
        base_iterator<ValueType>& operator --();
        base_iterator<ValueType> operator --(int);
        bool operator ==(const base_iterator<ValueType>&) const;
        bool operator !=(const base_iterator<ValueType>&) const;
    protected:
        unsigned int count;
        int index;
        weak_ptr<ValueType[]> ptr; //shared weak
    };
}

#include "base_iterator_math.h"
