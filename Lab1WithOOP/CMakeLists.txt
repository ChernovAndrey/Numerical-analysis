cmake_minimum_required(VERSION 3.8)
project(Lab1WithOOP)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(Lab1WithOOP ${SOURCE_FILES} BasicInterface.hpp Gauss.hpp sourceMatrices.h QR.hpp)