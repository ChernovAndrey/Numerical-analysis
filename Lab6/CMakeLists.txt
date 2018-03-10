cmake_minimum_required(VERSION 3.8)
project(Lab6)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp  SolveMethod.h tests.h
         matrixOperations.cpp matrixOperations.h vectorOperations.h
        vectorOperations.cpp RK.h Adams4.h PredCor.h  Euler SymScheme.h)
add_executable(Lab6 ${SOURCE_FILES})