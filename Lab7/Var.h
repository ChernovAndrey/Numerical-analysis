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
    Var(double h, double tau, double sigma): h(h), tau(tau), sigma(sigma){}

    const double p = 0.25;
    const double c = 2.0;
    const double alpha = 0.5;
    const double beta = 2;
    const double gamma = 2;
    const double u0 = 0.2;
    const double k1 = 2.0;
    const double k2 = 0.5;
    const double x1 = 0.5;
    const double x2 = 2.0 / 3.0;
    const double l = 1.0;
    const double Q = 10.0;
    const double t0 = 0.5;
// параметры по умолчанию закончились

    double h;

    double tau;

    double sigma;

    vector<vector<double>> U;

    vector<double> X;
    vector<double> T;


    void setX(Params *XPar){

        for (int i = 0; i < XPar->n; ++i) {
            X.push_back(XPar->start + i * XPar->step);
        }
    }

    void setT(Params *TPar){
        for (int i = 0; i < TPar->n; ++i) {
            T.push_back(TPar->start + i * TPar->step);
        }
    }

};


#endif //LAB7_Var_H
