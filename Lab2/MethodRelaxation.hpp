//
// Created by andrey on 21.09.17.
//

#ifndef LAB2_METHODRELAXATION_H
#define LAB2_METHODRELAXATION_H

#include <iostream>
#include <vector>
#include "IterativeMethods.hpp"
using namespace std;
template <typename T>
class MethodRelaxation : IterativeMethods<T> {

private:
    MethodRelaxation(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b) :
            IterativeMethods<T>(eps, x, A, b) {};

    void convertToIterativeMatrix() { //C в уравнении x=C*x + b
        T omega = 1.0;
        for (int i = 0; i < this->A.size(); i++) {
            auto coef  = 1 / this->A[i][i];
            this->b[i] = (this->b[i]) / (this->A[i][i]);
            for (int j = 0; j < this->A.size(); j++) {
                if (i == j) this->A[i][j] = 0.0;
                else {
                    this->A[i][j] = this->A[i][j] * coef;
                }

            }
        }
    }

public:
    static vector<T> solveSystem(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b) {
        IterativeMethods<T> *instance = new MethodRelaxation(eps, x, A, b);
        auto result = IterativeMethods<T>::solveSystem(instance);

        delete instance;
        return result;
    }
};


#endif //LAB2_METHODRELAXATION_H
