cmake_minimum_required(VERSION 3.8)
project(Lab6)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp ExplicitEuler.h SolveMethod.h tests.h ImplicitEuler.h
        Newton matrixOperations.cpp matrixOperations.h vectorOperations.h vectorOperations.cpp)
add_executable(Lab6 ${SOURCE_FILES})