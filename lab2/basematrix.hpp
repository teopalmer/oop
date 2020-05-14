#pragma once
#include <cstdio>

class BaseMatrix
{
    public:
        explicit BaseMatrix(): rows(0), columns(0), size(0){};
        virtual ~BaseMatrix() = default;

        void setRows(size_t rows) {this->rows = rows;}
        void setColumns(size_t columns) {this->columns = columns;}
        void setSize(size_t size) {this->size = this->columns * this->rows;}

        size_t getRows() const {return this->rows;}
        size_t getColumns() const {return this->columns;}
        size_t getSize() const {return this->size;}

        bool isEmpty() const {return this->size == 0;}

    private:
        size_t columns;
        size_t rows;
        size_t size;
};
