#include <iostream>
#include <vector>
#include <cmath>
#include "sourceMatrices.h"
#include "workWithConsole.h"
#include "matrixOperations.h"
#include "vectorOperations.h"
#include "SimpleIteration.hpp"
#include "MethodJacobi.hpp"
#include "IterativeMethods.hpp"
using namespace std;
using number = double;


int main() {
    vector<vector<number>> matrix;
    getMatrixEx2(matrix);
    //auto result = SimpleIteration<number>::solveSystem(0.000001,{0,0,0,0},getMatrixA(matrix),getVectorB(matrix));
    auto result = IterativeMethods<number>::solveSystem(new SimpleIteration<number>(0.0001,{0,0,0,0},getMatrixA(matrix),getVectorB(matrix)));
    printVector(result);
}