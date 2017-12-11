cmake_minimum_required(VERSION 3.8)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Grids matrixOperations.h sourceMatrices.h vectorOperations.cpp vectorOperations.h matrixOperations.cpp
        sourceMatrices.cpp Equation.h tests Solve)
add_executable(Lab5 ${SOURCE_FILES})