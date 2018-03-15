//
// Created by andrey on 10.03.18.
//

#ifndef LAB6_SYMSECHEME_H
#define LAB6_SYMSECHEME_H


#include "SolveMethod.h"
#include "tests.h"
#include "cassert"

// hard code; только для шарика с пружинкой
class SymScheme: public SolveMethod {
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
                nVariables[1]= (variables[1] - (k*tau/m)*( variables[0]+(tau/4)*variables[1] ) ) / (k*tau*tau/(4*m) +1) ;
                nVariables[0]=(tau/2) * (variables[1]+nVariables[1]) + variables[0];
                variables=nVariables;
                for (int j = 0; j < U.size(); j++){
                    U[j].push_back(nVariables[j]); // сейчас кол-во элементов равно i
                }
                //cout<<t<<endl;
                t+=tau;
            }
            return U;
        };

};


#endif //LAB6_SYMSECHEME_H
