//
// Created by andrey on 29.03.18.
//

#ifndef LAB7_Var_H
#define LAB7_Var_H

#include <iostream>
#include <vector>
#include "Solve.h"
#include "Params.h"

using namespace std;

class Var {
public:
    Var(double h, double tau) : h(h), tau(tau) {}

// параметры по умолчанию закончились

    double h;

    double tau;

    vector<vector<double>> U;

    vector<double> X;
    vector<double> T;


    void setX(Params *XPar) {

        for (int i = 0; i < XPar->n; ++i) {
            X.push_back(XPar->start + i * XPar->step);
        }
    }

    void setT(Params *TPar) {
        for (int i = 0; i < TPar->n; ++i) {
            T.push_back(TPar->start + i * TPar->step);
        }
    }

};


#endif //LAB7_Var_H
