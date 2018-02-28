//
// Created by andrey on 28.02.18.
//

#ifndef LAB6_IMPLICITEULER_H
#define LAB6_IMPLICITEULER_H

#include <vector>
#include "SolveMethod.h"
#include "Newton/SystemSolveNewton.h"

vector<double> variables;
double tau= TAU;

vector<double> EulerF (vector<double> nVar){
    vector<double> res(nVar.size());
    for (int j = 0; j < nVar.size(); j++) {
        res[j] = nVar[j] - tau * (F(nVar)[j]) - variables[j];
    }
    return res;
}

class ImplicitEuler : public SolveMethod{
   // vector<double> variables;
   // double tau= TAU;

    vector<vector<double>> solve(vector<double>(*F)(vector<double>),const vector<double> &initVariables) override{
        variables = initVariables;
        vector<vector<double>> U(variables.size());
        double t = T0;
 //       double tau = TAU;
        for(int i=0;i<variables.size();i++) U[i].push_back(variables[i]); // заполнение вектора начальным данными


        for(int i=1;i<N;i++) {
           //vector<double> nVariables(variables.size());
            auto FValue = F(variables);
//            vector<double> (*EulerF)(vector<double>) = [this,F, tau, variables](vector<double> nVar) {
//                    vector<double> res(nVar.size());
//                    for (int j = 0; j < nVar.size(); j++) {
//                        res[j] = nVar[j] - tau * (F(nVar)[j]) - variables[j];
//                    }
//                    return res;
//                };

            auto nVariables=(new SystemSolveNewton(variables,EulerF))->execute();
            for (int j = 0; j < U.size(); j++) {
                U[j].push_back(nVariables[j]); // сейчас кол-во элементов равно i
                t+=tau;
            }
            variables=nVariables;
        }
        return U;
    };

};



#endif //LAB6_IMPLICITEULER_H
