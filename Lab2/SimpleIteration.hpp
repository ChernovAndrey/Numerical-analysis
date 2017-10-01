//
// Created by andrey on 21.09.17.
//

#ifndef LAB2_SIMPLEITERATION_H
#define LAB2_SIMPLEITERATION_H

#include <iostream>
#include "IterativeMethods.hpp"

using namespace std;

template <typename T>
class SimpleIteration : public IterativeMethods<T>{
private:
    T parameter;
public:
    SimpleIteration(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b, T parameter) ://parameter- итерационный параметр
            IterativeMethods<T>(eps,x,A,b){
        this->parameter=parameter;
    };

private:
    void matrixNormalizationA(){
        for(int i=0; i< this->A.size(); i++){
            this->b[i]=parameter*this->b[i];
            for(int j=0;j< this->A[0].size();j++){
                this->A[i][j]=parameter*this->A[i][j];
            }
        }
        T normA = getNormMatrix3(this->A);
        cout<<"normA="<<normA<<endl;
    }

    void convertToIterativeMatrix(){ //C в уравнении x=C*x + b
        matrixNormalizationA();
       // printMatrix(this->A);
        this->A=EMinusMatrix(this->A);
        cout<< "normC="<<getNormMatrix3(this->A)<<endl;
      //  printMatrix(this->A);
    }

    vector<T> modificationX(const vector<T> &prevX) {
        return sumVector(multiMatrixVector(this->A,prevX),this->b);
    }
};


#endif //LAB2_SIMPLEITERATION_H
