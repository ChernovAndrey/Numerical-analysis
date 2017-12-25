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
                                   const vector<number> &b, const vector<number> &bDisturbance) {
    auto deltaResult = getResidual(result, resultDisturbance);
    auto deltaB = getResidual(b, bDisturbance);
    return deltaResult / deltaB;
}

int main() {

    vector<vector<number>> matrix;
    getMatrixEx1(matrix);
    auto eigenValues=QR<number>::findEigenValues(matrix);
    printVector(eigenValues);

    cout<<"--------------------------------------------------------(finish find eigen values)"<<endl;
    cout<<"RESSS:"<<abs(eigenValues[0]-0.997313);
  //  eigenValues[0]=0.997313;
    for(int i=0;i<eigenValues.size();i++){
        cout <<"result eigen vector:"<<endl;
        auto iterMatrix=matrix;
        auto result=QR<number>::reverseIterations(iterMatrix,eigenValues[i]);
        printVector(result);
        shiftMatrix(iterMatrix,eigenValues[i]);
        cout<<"check:"<<endl;
        printVector(multiMatrixVector(iterMatrix,result));
        cout<<"--------------------------------------------------------(finish find eigen vectors)"<<endl;
    }


    cout<<"vector find found throw ratio Relay:"<<endl;
    auto result=QR<number>::ratioRelay(matrix);
    printVector(result);
    cout<<"--------------------------------------------------------(finish find eigen vector throw ratio relay)"<<endl;

    /*  vector<vector<number>> matrix;
      getMatrixEx1(matrix);
      printMatrix(matrix);
      auto res= QR<number>::solveSystem(getMatrixA(matrix),getVectorB(matrix));
      printVector(res);*/
    /*  number coefDisturbance = 0.01;
      vector<vector<number>> matrix;
      getMatrixEx5(matrix);
      //matrix = readFile(matrix,1);
      auto A = getMatrixA(matrix);
      auto b = getVectorB(matrix);

      auto result = QR<number>::solveSystem(A,b);

      cout<< "CondA="<<getConditionNumber(A,3)<<endl;

      printVector(result);

      for (int i = 0; i < b.size(); ++i) {
          auto bDisturbance = b;
          bDisturbance[i]+=coefDisturbance;
         // printVector(bDisturbance);
          auto resultDisturbance = QR<number>::solveSystem(A,bDisturbance);
          printVector(resultDisturbance);
        / cout << "CondA>=" << getConditionalityAssessment(result, resultDisturbance, b, bDisturbance)<<endl;
      }*/

    return 0;
}