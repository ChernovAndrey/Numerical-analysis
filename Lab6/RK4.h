//
// Created by andrey on 28.02.18.
//

#ifndef LAB6_RK4_H
#define LAB6_RK4_H

#include <vector>
#include "SolveMethod.h"

using namespace std;
class RK4: public SolveMethod{
private:
    const int P =4;
    bool autoStepFlag = false;
public:
    explicit RK4(bool flag) : SolveMethod(){
        this->autoStepFlag=flag;
    }
    RK4() = default;

    void setAutoStepFlag(bool flag){this->autoStepFlag=flag;}

    bool getAutoStepFlag(){return this->autoStepFlag;}

    vector<vector<double>> solve(vector<double>(*F)(vector<double>), const vector<double> &initVariables, int n) override{
      if (autoStepFlag){
        return calculateWithChangeTau(F,initVariables,n);
      }
        return calculateWithConstTau(F,initVariables,n);

    }

    vector<vector<double>> calculateWithConstTau(vector<double>(*F)(vector<double>), const vector<double> &initVariables, int n){
        auto variables = initVariables;
        vector<vector<double>> U(variables.size());
        double t = T0;
        double tau = TAU;
        double eps = EPS;
        for(int i=0;i<variables.size();i++) U[i].push_back(variables[i]); // заполнение вектора начальным данными


        for(int i=1;i<n;i++) {
            vector<double> nVariables(variables.size(),1);
            nVariables = calculateNextValue(tau, variables);
            for (int j = 0; j < U.size(); j++){
                U[j].push_back(nVariables[j]); // сейчас кол-во элементов равно i
                //nVariables[j]=U[j][i];
            }
            t+=tau;
            variables=nVariables;
        }
        cout<<"tau="<<tau<<endl;
        return U;
    }


    vector<vector<double>> calculateWithChangeTau(vector<double>(*F)(vector<double>), const vector<double> &initVariables, int n){
        auto variables = initVariables;
        vector<vector<double>> U(variables.size());
        double t = T0;
        double tau = TAU;
        double eps = EPS;
        for(int i=0;i<variables.size();i++) U[i].push_back(variables[i]); // заполнение вектора начальным данными


        for(int i=1;i<n;i++) {
            vector<double> nVariables(variables.size(),1);
            vector<double> nVariables2(variables.size(),20);
            while (normC(nVariables, nVariables2)/(pow(2,P)-1) >= eps) {
                nVariables = calculateNextValue(tau, variables);
                tau=tau/2;
                nVariables2 = calculateNextValue(tau, variables);
            }
            for (int j = 0; j < U.size(); j++){
                U[j].push_back(nVariables2[j]); // сейчас кол-во элементов равно i
                //nVariables[j]=U[j][i];
            }
            if (normC(nVariables, nVariables2)/(pow(2,P)-1) <= 10*eps){
                tau=10*tau;
            }
            t+=tau;
            variables=nVariables2;
        }
        cout<<"tau="<<tau<<endl;
        return U;
    }

    vector<double> calculateNextValue(double tau,vector<double> variables){
        vector<double> nVariables(variables.size());
        auto k1=F(variables); //добваить t  в variables

        vector<double> variablesK2(variables.size());
        for(int k =0;k<variables.size();k++){
            variablesK2[k]=variables[k]+tau/2 * k1[k];
        }
        auto k2=F(variablesK2);

        vector<double> variablesK3(variables.size());
        for(int k =0;k<variables.size();k++){
            variablesK3[k]=variables[k]+tau/2 * k2[k];
        }
        auto k3=F(variablesK3);

        vector<double> variablesK4(variables.size());
        for(int k =0;k<variables.size();k++){
            variablesK4[k]=variables[k]+tau * k3[k];
        }
        auto k4=F(variablesK4);

        vector<double> K(k4.size());
        for (int l = 0; l < K.size(); ++l) {
            K[l]=1.0/6.0 * (k1[l]+2*k2[l]+2*k3[l]+k4[l]);
        }

        for (int j = 0; j < variables.size(); j++){
            nVariables[j] =variables[j]+tau*K[j]; // сейчас кол-во элементов равно i
        }
        return nVariables;

    }

};


#endif //LAB6_EXPLICITEULER_H
