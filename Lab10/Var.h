//
// Created by andrey on 29.03.18.
//

#ifndef LAB9_Var_H
#define LAB9_Var_H

#include <iostream>
#include <vector>
#include "Solve.h"
#include "Params.h"

using namespace std;

class Var {
public:
    explicit Var(double h, double hs): h(h), hs(hs){}


    double h;
    double hs;

    vector<vector<vector<double>>> U{};

    vector<double> X{};
    vector<double> S{};

    void setX(Params *XPar){
        for (int i = 0; i < XPar->n; ++i) {
            X.push_back(XPar->start + i * XPar->step);
        }
    }

    void setS(Params *SPar){
        for (int i = 0; i < SPar->n; ++i) {
            S.push_back(SPar->start + i * SPar->step);
        }
    }

};


#endif //LAB9_Var_H
