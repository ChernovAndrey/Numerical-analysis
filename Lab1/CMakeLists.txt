cmake_minimum_required(VERSION 3.6.3)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(Lab1WithOOP ${SOURCE_FILES} BasicInterface.hpp Gauss.hpp sourceMatrices.h QR.hpp sourceMatrices.cpp)