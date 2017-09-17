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


number getNormMatrix1(const vector<vector<number>> &matrix){ //по столбцам
    number norm;
    bool flagInit = false;
    for(int j=0; j<matrix[0].size();j++){
        number max = 0.0;
        for (auto &el : matrix) {
            max+=abs(el[j]);
        }
        if(!flagInit) {
            norm = max;
            flagInit =true;
        }else {
            if (norm < max) norm = max;
        }
    }
}


number getNormMatrix3(const vector<vector<number>> &matrix){ // по строкам
    number norm ;
    bool flagInit = false;
    for (auto str : matrix) {
        number max = 0.0;
        for (auto el : str) {
            max+=abs(el);
        }
        if(!flagInit) {
            norm = max;
            flagInit =true;
        }else {
            if (norm < max) norm = max;
        }
    }
    return norm;
}

number getConditionNumber(const vector<vector<number>> &matrix,int nNorm){//nNorm- номер нормы
    if(nNorm==1){
            return getNormMatrix1(matrix)*getNormMatrix1(getInvertibleMatrix(matrix));
        }
    if(nNorm==3){
        return getNormMatrix3(matrix)*getNormMatrix3(getInvertibleMatrix(matrix));
    }
    assert(false);
}

int main() {
    vector<vector<number>> matrix;
    //getMatrixEx4(matrix);
    matrix=readFile(matrix,1);
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
 /*   auto inverseA=getInvertibleMatrix(A);
    cout<<"inverse";
    BasicInterface<number>::printMatrix(inverseA);
    auto E =BasicInterface<number>::matrixMultiplication(inverseA,A);
    BasicInterface<number>::printMatrix(E);*/
    return 0;
}