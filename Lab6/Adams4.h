//
// Created by andrey on 28.02.18.
//

#ifndef LAB6_ADAMS4_H
#define LAB6_ADAMS4_H

#include <vector>
#include <iostream>
#include "SolveMethod.h"
#include "RK.h"
#include "vectorOperations.h"
#include "matrixOperations.h"

using namespace std;
class Adams4: public SolveMethod{
public:
    vector<vector<double>> solve(vector<double>(*F)(vector<double>,double),const vector<double> &initVariables,
                                 double t0,double tf) override{
        const auto &variables = initVariables;
        double t = t0;
        double tau = TAU;
        double eps = EPS;
        auto * rk4 = new RK(false,4);
        auto initU = rk4->solve(F,initVariables,t0,t0+2*tau);
        t+=3*tau; // так как рунге-кутте сходил три раза
        delete rk4;
        vector<vector<double>> U(initU);

        vector<vector<double>> last4U(4);//последние 4 variables U
        for (int k = 0; k < 4; ++k) {
            for (int l = 0; l < U.size(); ++l) {
               last4U[k].push_back(U[l][k]);
            }
        }
        for(int i=4;t<=tf;i++) {
            vector<double> nVariables(variables.size(),1);
            nVariables= evaluateNextValue(F,tau,last4U,t);
            for (int j = 0; j < U.size(); j++){
                U[j].push_back(nVariables[j]); // сейчас кол-во элементов равно i
                //nVariables[j]=U[j][i];
            }


            t+=tau;
            vector<vector<double>> nLast4u(last4U.begin()+1,last4U.end());
            nLast4u.push_back(nVariables);
            last4U=nLast4u;

            //variables=nVariables;
        }
        return U;
    };
    vector<double> evaluateNextValue(vector<double> (*F)(vector<double>,double),double tau,vector<vector<double>> last4U, double t){
        vector<double> res(last4U[0].size());
        for (int i = 0; i < last4U[0].size(); ++i) {
            res[i]=last4U[3][i]+ (tau/24.0)*(55.0*F(last4U[3],t)[i]-59*F(last4U[2],t)[i]+37*F(last4U[1],t)[i]-9*F(last4U[0],t)[i]);
        }
        return res;
    }

};

#endif //LAB6_ADAMS4_H
