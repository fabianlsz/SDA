cmake_minimum_required(VERSION 3.30)
project(Lab3_Matrix1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab3_Matrix1
    App.cpp
    ExtendedTest.cpp
    ExtendedTest.h
    Matrix.cpp
    Matrix.h
    ShortTest.cpp
    ShortTest.h)
