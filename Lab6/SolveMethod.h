//
// Created by andrey on 28.02.18.
//

#ifndef LAB6_SOLVEMETHOD_H
#define LAB6_SOLVEMETHOD_H

#define Tf 50
#define TAU 0.01
#define T0 TAU
#define EPS 1e-5

#include <vector>
using namespace std;

class SolveMethod { //interface
public:
    virtual vector<vector<double>> solve(vector<double>(*F)(vector<double>, double),const vector<double> &initVariables,
    double to, double tf)=0;//n - кол-во шагов



};


#endif //LAB6_SOLVEMETHOD_H
