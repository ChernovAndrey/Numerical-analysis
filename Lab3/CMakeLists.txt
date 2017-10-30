cmake_minimum_required(VERSION 3.8)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES main.cpp Grids/Grid.h Grids/UniformGrid.h Interpolating/Interpolate.h Interpolating/Lagrange.h tests/functions.h Grids/ChebyshevGrid.h
         helping/vectorOperations.h helping/workWithConsole.h
        Interpolating/CubicSpline.h helping/matrixOperations.h solveSystem/Sweep.h)

add_executable(Lab3 ${SOURCE_FILES})