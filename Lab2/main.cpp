#include <iostream>
#include <vector>
#include <cmath>
#include "sourceMatrices.h"
#include "workWithConsole.h"
#include "matrixOperations.h"
#include "vectorOperations.h"
#include "SimpleIteration.hpp"
#include "MethodJacobi.hpp"
#include "MethodSeidel.hpp"
#include "MethodRelaxation.hpp"
#include "IterativeMethods.hpp"
using namespace std;
using number = double;


int main() {
    vector<vector<number>> matrix;
   // setMatrixEx1(matrix);
    matrix=ReadFile(matrix,2);
   // auto result = IterativeMethods<number>::solveSystem(new SimpleIteration<number>(0.0001,{0,0,0,0},getMatrixA(matrix),getVectorB(matrix),0.059));
    //auto result = IterativeMethods<number>::solveSystem(new MethodJacobi<number>(0.0001,{0,0,0,0},getMatrixA(matrix),getVectorB(matrix)));
  //auto result = IterativeMethods<number>::solveSystem(new MethodSeidel<number>(0.0001,{0,0,0,0},getMatrixA(matrix),getVectorB(matrix)));
  auto result = IterativeMethods<number>::solveSystem(new MethodRelaxation<number>(0.0001,{0,0,0,0},getMatrixA(matrix),getVectorB(matrix),1.25));
    printVector(result);
}