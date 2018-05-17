cmake_minimum_required(VERSION 3.8)
project(Lab9)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Equations.h Params.h Solve.h Var.h helping solveSystem)
add_executable(Lab9 ${SOURCE_FILES})