cmake_minimum_required(VERSION 3.6.3)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(Lab2 ${SOURCE_FILES} matrixOperations.h matrixOperations.cpp
        sourceMatrices.h sourceMatrices.cpp workWithConsole.cpp workWithConsole.h
        vectorOperations.cpp vectorOperations.h IterativeMethods.hpp SimpleIteration.hpp
        MethodJacobi.hpp MethodRelaxation.hpp MethodSeidel.hpp DiagIterativeMethod.hpp
        DiagMethodRelaxation.hpp DiagMethodSeidel.hpp)