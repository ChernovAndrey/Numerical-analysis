//
// Created by andrey on 28.02.18.
//

#ifndef LAB6_EXPLICITEULER_H
#define LAB6_EXPLICITEULER_H

#include <vector>
#include "../SolveMethod.h"
#include "../vectorOperations.h"

using namespace std;
class ExplicitEuler: public SolveMethod{
public:
    vector<vector<double>> solve(vector<double>(*F)(vector<double>, double),const vector<double> &initVariables,
                                 double t0,double tf) override{
        auto variables = initVariables;
        vector<vector<double>> U(variables.size());
        double t = t0;
        double tau = TAU;
        double eps = EPS;
        for(int i=0;i<variables.size();i++) U[i].push_back(variables[i]); // заполнение вектора начальным данными


        for(int i=1;t<=tf;i++) {
            auto FValue = F(variables, t); //u_{n}
            vector<double> nVariables(variables.size());
            for (int j = 0; j < U.size(); j++){
                U[j].push_back(variables.at(j) + tau*FValue[j]); // сейчас кол-во элементов равно i
                nVariables[j]=U[j][i];
            }

            t+=tau;
            variables=nVariables;
        }
        return U;
    };

};

#endif //LAB6_EXPLICITEULER_H
