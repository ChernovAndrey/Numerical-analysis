//
// Created by andrey on 21.09.17.
//

#ifndef LAB2_METHODJACOBI_H
#define LAB2_METHODJACOBI_H


#include <iostream>
#include "IterativeMethods.hpp"

using namespace std;

template <typename T>
class MethodJacobi : public IterativeMethods<T>{

public:
    MethodJacobi(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b) :
            IterativeMethods<T>(eps,x,A,b){};

protected:
    void convertToIterativeMatrix(){ //C в уравнении x=C*x + b
        for(int i=0;i<this->A.size();i++){
            auto coef = -1/this->A[i][i];
            this->b[i]= (this->b[i])/(this->A[i][i]);
            for(int j=0;j<this->A.size();j++){
                if (i==j) this->A[i][j] = 0.0;
                else{
                    this->A[i][j] = this->A[i][j]* coef;
                }

            }
        }
    }

private:
    vector<T> modificationX(const vector<T> &prevX) {
        return sumVector(multiMatrixVector(this->A,prevX),this->b);
    }
};


#endif //LAB2_METHODJACOBI_H
