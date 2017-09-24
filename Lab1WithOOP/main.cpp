#include <iostream>
#include "BasicInterface.hpp"
#include "sourceMatrices.h"
#include "QR.hpp"
#include<cmath>
#include "matrixOperations.h"
#include "vectorOperations.h"
using namespace std;
using number = double;


number getConditionalityAssessment(const vector<number> &result, const vector<number> &resultDisturbance,
                                   const vector<number> &b, const vector<number> &bDisturbance){
    auto deltaResult = getResidual(result,resultDisturbance);
    auto deltaB = getResidual(b,bDisturbance);
    return deltaResult/deltaB;
}

int main() {

    number coefDisturbance = 0.01;
    vector<vector<number>> matrix;
    //getMatrixEx4(matrix);
    //matrix = readFile(matrix,1);
    auto A = getMatrixA(matrix);
    auto b = getVectorB(matrix);

    auto result = QR<number>::solveSystem(A,b);

    cout<< "CondA="<<getConditionNumber(A,1)<<endl;

    printVector(result);

    for (int i = 0; i < b.size(); ++i) {
        auto bDisturbance = b;
        bDisturbance[i]+=coefDisturbance;
       // printVector(bDisturbance);
        auto resultDisturbance = QR<number>::solveSystem(A,bDisturbance);
        printVector(resultDisturbance);
        cout << "CondA>=" << getConditionalityAssessment(result, resultDisturbance, b, bDisturbance)<<endl;
    }

   return 0;
}