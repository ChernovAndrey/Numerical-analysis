cmake_minimum_required(VERSION 3.6)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp gauss.cpp sourceMatrices.cpp workWithConsole.h sourceMatrices.h
        gauss.h QR.cpp QR.h generalMethods.h generalMethods.cpp workWithConsole.cpp invertibleMatrixGauss.cpp)
add_executable(Lab1 ${SOURCE_FILES})