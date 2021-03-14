cmake_minimum_required(VERSION 3.17)
project(classMatrix)

set(CMAKE_CXX_STANDARD 17)

add_library(matrix.hpp matrix.cpp)
add_executable(classMatrix main.cpp matrix.cpp)