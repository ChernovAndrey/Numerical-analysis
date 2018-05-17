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
    Var(double h1, double h2, double tau): h1(h1), h2(h2), tau(tau){}


    double h1;
    double h2;

    double tau;

    vector<vector<vector<double>>> U;

    vector<double> X1;
    vector<double> X2;
    vector<double> T;


    void setX(Params *XPar1, Params *XPar2){

        for (int i = 0; i < XPar1->n; ++i) {
            X1.push_back(XPar1->start + i * XPar1->step);
        }


        for (int i = 0; i < XPar2->n; ++i) {
            X2.push_back(XPar2->start + i * XPar2->step);
        }
    }

    void setT(Params *TPar){
        for (int i = 0; i < TPar->n; ++i) {
            T.push_back(TPar->start + i * TPar->step);
        }
    }

};


#endif //LAB9_Var_H
