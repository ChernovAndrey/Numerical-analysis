#include <iostream>
#include "BasicInterface.hpp"
#include "sourceMatrices.h"
#include "QR.hpp"
using namespace std;
using number = double;

vector<vector<number>>getInvertibleMatrix(vector<vector<number>> matrix){
    vector<vector<number>> inverseMatrix(matrix.size());
    vector<number> help(matrix[0].size());
    for (int i = 0; i < matrix.size(); i++){
            vector<number> e(matrix.size(),0.0);
            e[i]=1.0;
            inverseMatrix[i] = Gauss<number>::solveSystem(matrix,e);
    }
    return QR<number>::transposeMatrix(inverseMatrix);
}

int main() {
    vector<vector<number>> matrix;
    getMatrixEx4(matrix);
    BasicInterface<number>::printMatrix(matrix);
    auto A =BasicInterface<number>::getMatrixA(matrix);
    auto result =Gauss<number>::solveSystem(A,BasicInterface<number>::getVectorB(matrix));
    if (result.empty()){
        cout<<"matrix degenerate";
    }
    else{
        cout<<"result:"<<endl;
        BasicInterface<number>::printVector(result);
    }
    auto inverseA=getInvertibleMatrix(A);
    cout<<"inverse";
    BasicInterface<number>::printMatrix(inverseA);
    auto E =BasicInterface<number>::matrixMultiplication(inverseA,A);
    BasicInterface<number>::printMatrix(E);
    return 0;
}