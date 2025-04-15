cmake_minimum_required(VERSION 3.30)
project(Lab2_MultiMap20)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab2_MultiMap20
    App.cpp
#    ExtendedTest.cpp
#    ExtendedTest.h
    MultiMap.cpp
    MultiMap.h
    MultiMapIterator.cpp
    MultiMapIterator.h
    ShortTest.cpp
    ShortTest.h)
