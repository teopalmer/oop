cmake_minimum_required(VERSION 3.8)
project(oop_lab_02)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp )
add_executable(lab2 base_matrix.cpp base_matrix.h
         const_math.h errors.h main.cpp matrix.h matrix_math.h)