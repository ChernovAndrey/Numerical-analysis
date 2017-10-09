
// Created by andrey on 09.10.17.
//

#ifndef LAB2_DIAGITERATIVES_H
#define LAB2_DIAGITERATIVES_H

#include <iostream>
#include <vector>
#include "matrixOperations.h"
#include "vectorOperations.h"
#include "workWithConsole.h"
#include <typeinfo>
#include "IterativeMethods.hpp"

template<typename T>
class DiagIterativeMethod : public IterativeMethods<T> {
public:
    DiagIterativeMethod(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b) :
            IterativeMethods<T>(eps, x, A, b) {};


    void convertToIterativeMatrix() override {
        for (int i = 0; i < this->A.size(); i++) {
            if (IterativeMethods<T>::compareWithZero(this->A[i][1])) {
                this->A = IterativeMethods<T>::swapStrIMatrix(this->A, i);
                if (this->A.empty()) throw invalid_argument("invalid matrix");
            }
            auto coef = -1 / this->A[i][1];
            this->b[i] = (this->b[i]) / (this->A[i][1]);

            this->A[i][2] *=coef;
            this->A[i][0] *=coef;

            this->A[i][1]=0.0;
        }
    }
};

#endif //LAB2_DIAGITERATIVES_H
