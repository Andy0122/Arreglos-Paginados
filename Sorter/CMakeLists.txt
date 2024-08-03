cmake_minimum_required(VERSION 3.28)
project(sorter)

set(CMAKE_CXX_STANDARD 17)

add_executable(sorter main.cpp
        PagedArray.cpp
        PagedArray.h
        Page.cpp
        Page.h
        SortingAlgorithms.cpp
        SortingAlgorithms.h)
