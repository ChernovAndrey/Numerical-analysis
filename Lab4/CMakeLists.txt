cmake_minimum_required(VERSION 3.8)
project(Lab4)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp QR.hpp BasicInterface.hpp matrixOperations.h sourceMatrices.h vectorOperations.h matrixOperations.cpp
        sourceMatrices.cpp vectorOperations.cpp)
add_executable(Lab4 ${SOURCE_FILES})