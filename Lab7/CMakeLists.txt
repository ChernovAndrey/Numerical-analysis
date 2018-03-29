cmake_minimum_required(VERSION 3.8)
project(Lab7)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Solve.h helping/matrixOperations.h helping/workWithConsole.h helping/vectorOperations.h Equations.h Params.h)
add_executable(Lab7 ${SOURCE_FILES})