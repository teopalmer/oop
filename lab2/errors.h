#ifndef errors_h
#define errors_h

#include <stdio.h>
#include <exception>
#include <string.h>

class base_matrix_exception : public std::exception //base_matrix nam
{
public:
    base_matrix_exception(std::string filename, std::string classname, int line, const char *time, std::string info)
    {
        err_info = "\nError: " + info + "\nfilename: " + filename + "\nline: " + std::to_string(line)
        + "\ntime: " + time ;
    }
    const char *what() const noexcept override {return (this->err_info).c_str();}; //const
protected:
    std::string err_info;
};

class index_out_of_range_exception : public base_matrix_exception
{
public:
    index_out_of_range_exception(std::string filename, std::string classname, int line, const char *time, std::string info)
    : base_matrix_exception(filename, classname, line, time, info) {};
    const char *what() const noexcept override {return (this->err_info).c_str();}
};

class is_not_equal_exception : public base_matrix_exception
{
public:
    is_not_equal_exception(std::string filename, std::string classname, int line, const char *time, std::string info)
    : base_matrix_exception(filename, classname, line, time, info) {};
    const char *what() const noexcept override {return (this->err_info).c_str();}
};

class is_empty_exception : public base_matrix_exception
{
public:
    is_empty_exception(std::string filename, std::string classname, int line, const char *time, std::string info)
    : base_matrix_exception(filename, classname, line, time, info) {};
    const char *what() const noexcept override {return (this->err_info).c_str();}
};

class cannot_mult_matrix_exception : public base_matrix_exception
{
public:
    cannot_mult_matrix_exception(std::string filename, std::string classname, int line, const char *time, std::string info)
    : base_matrix_exception(filename, classname, line, time, info) {};
    const char *what() const noexcept override {return (this->err_info).c_str();}
};

class is_not_square_exception : public base_matrix_exception
{
public:
    is_not_square_exception(std::string filename, std::string classname, int line, const char *time, std::string info)
    : base_matrix_exception(filename, classname, line, time, info) {};
    const char *what() const noexcept override {return (this->err_info).c_str();}
};

#endif /* errors_h */
