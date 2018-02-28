//
// Created by andrey on 28.02.18.
//

#ifndef LAB6_SOLVEMETHOD_H
#define LAB6_SOLVEMETHOD_H

#define N 200
#define T0 0
#define TAU 0.01

#include <vector>
using namespace std;

class SolveMethod { //interface
public:
    virtual vector<vector<double>> solve(vector<double>(*F)(vector<double>),const vector<double> &initVariables)=0;


};


#endif //LAB6_SOLVEMETHOD_H
