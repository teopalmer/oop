#pragma once
#include <cstdio>

class BaseMatrix
{
    public:
        explicit BaseMatrix(): rows(0), cols(0), size(0){};
        virtual ~BaseMatrix() = default;

        void setRows(size_t r) {this->rows = r;}
        void setCols(size_t c) {this->cols = c;}
        void setSize() {this->size = this->cols * this->rows;}

        size_t getRows() const {return this->rows;}
        size_t getCols() const {return this->cols;}
        size_t getSize() const {return this->size;}

        bool isEmpty() const {return this->size == 0;}

    private:
        size_t cols;
        size_t rows;
        size_t size;
};
