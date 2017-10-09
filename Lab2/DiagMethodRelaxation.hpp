//
// Created by andrey on 21.09.17.
//

#ifndef LAB2_DIAGMETHODRELAXATION_H
#define LAB2_DIAGMETHODRELAXATION_H


#include <iostream>
#include "MethodJacobi.hpp"
#include <typeinfo>
#include "cassert"
#include "cmath"
#include "DiagIterativeMethod.hpp"
using namespace std;

template <typename T>
class DiagMethodRelaxation : public DiagIterativeMethod<T> {

protected:
     T w;
    bool flagW;//1 или нет

    void shiftXm(T &Xm, const T &prevXm){
        if(flagW) return;
        Xm=w*Xm + (1.0-w)*prevXm;
    }
public:
    DiagMethodRelaxation(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b, const T w) :
            DiagIterativeMethod<T>(eps, x, A, b) {
        this->w=w;
        flagW=IterativeMethods<T>::compareWithZero(this->w);
    };
private:
    vector<T> modificationX(const vector<T> &prevX) {
        vector<T> x(prevX.size());
        for (int m = 0; m < x.size(); m++) {
            x[m]=0;
            if(m==0) x[m]+=this->A[m][2]*prevX[m+1];
            else {
                if(m==x.size()-1) x[m]+=this->A[m][0]*x[m-1];
                else{
                    x[m]+=this->A[m][0]*x[m-1]+this->A[m][2]*prevX[m+1];
                }
            }
            x[m]+=this->b[m];
           shiftXm(x[m],prevX[m]);
        }
        return x;
    }
};

#endif //LAB2_METHODRELAXATION_H
