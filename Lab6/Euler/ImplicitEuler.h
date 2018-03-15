//
// Created by andrey on 28.02.18.
//

#ifndef LAB6_IMPLICITEULER_H
#define LAB6_IMPLICITEULER_H

#include <vector>
#include "../SolveMethod.h"
#include <cassert>

// hard code; только для шарика с пружинкой
class ImplicitEuler : public SolveMethod{
    const double k = getK();
    const double m = getM();

    vector<vector<double>> solve(vector<double>(*F)(vector<double>, double),const vector<double> &initVariables,
                                 double t0,double tf) override{
        auto variables = initVariables;
        vector<vector<double>> U(variables.size());
        double t = t0;
        double tau = TAU;
        for(int i=0;i<variables.size();i++) U[i].push_back(variables[i]); // заполнение вектора начальным данными
        assert(U.size()==2);
        assert(variables.size()==2);

        for(int i=1;t<=tf;i++) {
           // auto FValue = F(variables); //u_{n}
            vector<double> nVariables(variables.size());
            nVariables[1]=( (variables[1]-(k*tau/m)*variables[0])/(k*tau*tau/m +1) );
            nVariables[0]=(nVariables[1]*tau+variables[0]);
            variables=nVariables;
            for (int j = 0; j < U.size(); j++){
                U[j].push_back(nVariables[j]); // сейчас кол-во элементов равно i
            }
            t+=tau;
        }
        return U;
    };

};



#endif //LAB6_IMPLICITEULER_H
