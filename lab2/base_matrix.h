#ifndef base_matrix_h
#define base_matrix_h

#include <iostream>

namespace matrix_core
{
    class base_matrix //хотя бы один виртуальный метод
    {
    public:
        explicit base_matrix();
        explicit base_matrix(size_t);
        virtual ~base_matrix() = 0;
        bool is_empty() const;
        size_t get_rows() const {return this->rows;}
        size_t get_columns() const {return this->columns;}
        size_t size() const;
    protected:
        size_t columns;
        size_t rows;
        size_t elements_count;
    };
}
#endif // base_matrix_h
