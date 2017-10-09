//
// Created by andrey on 21.09.17.
//

#ifndef LAB2_METHODRELAXATION_H
#define LAB2_METHODRELAXATION_H

#include <iostream>
#include "MethodJacobi.hpp"
#include <typeinfo>
#include "cassert"
#include "cmath"
using namespace std;

template <typename T>
class MethodRelaxation : public MethodJacobi<T> {

protected:
     T w;
    bool flagW;//1 или нет
    void shiftXm(T &Xm, const T &prevXm){
        if(flagW) return;
        Xm=w*Xm + (1.0-w)*prevXm;
    }
public:
    MethodRelaxation(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b, const T w) :
            MethodJacobi<T>(eps, x, A, b) {
        this->w=w;
        flagW=IterativeMethods<T>::compareWithZero(this->w-1);
    };
private:
    vector<T> modificationX(const vector<T> &prevX) {
        vector<T> x(prevX.size());
        for (int m = 0; m < x.size(); m++) {
            x[m]=0;
            for (int i = 0; i < m; i++) {
                x[m] += this->A[m][i] * x[i];
            }
            for (int i = m+1; i < x.size(); i++) {
                x[m] += this->A[m][i] * prevX[i];
            }
            x[m]+=this->b[m];
            shiftXm(x[m],prevX[m]);
        }
        return x;
    }
};

#endif //LAB2_METHODRELAXATION_H
