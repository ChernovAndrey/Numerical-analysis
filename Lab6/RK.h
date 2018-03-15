//
// Created by andrey on 28.02.18.
//

#ifndef LAB6_RK4_H
#define LAB6_RK4_H

#include <vector>
#include "SolveMethod.h"
#include "cassert"
using namespace std;
class RK: public SolveMethod{
private:
    int P =4;//порядок точности
    bool autoStepFlag = false;
public:
    explicit RK(bool flag,int P=4) : SolveMethod(){
        this->autoStepFlag=flag;
        this->P=P;
    }
    RK() = default;

    void setAutoStepFlag(bool flag){this->autoStepFlag=flag;}

    bool getAutoStepFlag(){return this->autoStepFlag;}

    void setP(int P){
        assert((P==2)||(P==4));
        this->P=P;
    }

    int getP(){return P;}

    vector<vector<double>> solve(vector<double>(*F)(vector<double>,double), const vector<double> &initVariables,
                                    double t0, double tf) override{
        assert((P==2)||(P==4));
        if (autoStepFlag){
        return calculateWithChangeTau(F,initVariables,t0,tf);
        }
        return calculateWithConstTau(F,initVariables,t0,tf);

    }

    vector<vector<double>> calculateWithConstTau(vector<double>(*F)(vector<double>,double), const vector<double> &initVariables,
                                                 double t0,double tf){
        auto variables = initVariables;
        vector<vector<double>> U(variables.size());
        double t = t0;
        double tau = TAU;
        double eps = EPS;
        for(int i=0;i<variables.size();i++) U[i].push_back(variables[i]); // заполнение вектора начальным данными


        for(int i=1;t<=tf;i++) {
            vector<double> nVariables(variables.size(),1);
            nVariables = calculateNextValue(F,tau, variables,t);
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


    vector<vector<double>> calculateWithChangeTau(vector<double>(*F)(vector<double>,double), const vector<double> &initVariables,
                                                  double t0, double tf){
        auto variables = initVariables;
        vector<vector<double>> U(variables.size());
        double t = t0;
        double tau = TAU;
        double eps = EPS;
        for(int i=0;i<variables.size();i++) U[i].push_back(variables[i]); // заполнение вектора начальным данными

        auto minTau = tau;
        auto maxTau = tau;

        for(int i=1;t<=tf;i++) {
            vector<double> nVariables(variables.size(),1); //произвольный init
            vector<double> nVariables2(variables.size(),20); //произвольный init
            bool flagFirst = true;
            double multiplier = 1.0/(pow(2,P)-1); // на что умножаем
            double norm = normC( multiVectorByNumber( diffVectors(nVariables,nVariables2), multiplier ) ) ;
            while ( (norm >= eps) || (flagFirst) ){ //или flagFirst==true
                if (!flagFirst){
                    tau=tau/2;
                    cout<<"уменьшили tau"<<endl;
                }
                flagFirst = false;
                nVariables = calculateNextValue(F,tau, variables,t);
                double tau2=tau/2;
                nVariables2 = calculateNextValue(F,tau2, variables,t); //делаем два шага так как шаг уменьшился вдвое
                nVariables2 = calculateNextValue(F,tau2, nVariables2,t);
                norm = normC( multiVectorByNumber( diffVectors(nVariables,nVariables2), multiplier ) );
            }
            for (int j = 0; j < U.size(); j++){
                U[j].push_back(nVariables2[j]); // сейчас кол-во элементов равно i
                //nVariables[j]=U[j][i];
            }

            if(minTau > tau){ minTau = tau;}

            if(maxTau < tau){ maxTau = tau;}

            if (norm <= eps*eps){
                tau=1.5*tau;
                cout<<"увеличили tau"<<endl;
            }
            t+=tau;
            variables=nVariables2;
        }
        cout<<"finish tau="<<tau<<endl;
        cout<<"min tau="<<minTau<<endl;
        cout<<"max tau="<<maxTau<<endl;
        return U;
    }

    vector<double> calculateNextValue(vector<double>(*F)(vector<double>,double),double tau,vector<double> variables,double t){
        vector<double> nVariables(variables.size());
        auto k1=F(variables,t); //добваить t  в variables

        vector<double> variablesK2(variables.size());
        for(int k =0;k<variables.size();k++){
            variablesK2[k]=variables[k]+tau/2 * k1[k];
        }
        auto k2=F(variablesK2,t+tau/2);

        //если PK2
        if(P==2){
            for (int j = 0; j < variables.size(); j++){
                nVariables[j] =variables[j]+tau*k2[j]; // сейчас кол-во элементов равно i
            }
            return nVariables;
        }
        // конец если PK2

        vector<double> variablesK3(variables.size());
        for(int k =0;k<variables.size();k++){
            variablesK3[k]=variables[k]+tau/2 * k2[k];
        }
        auto k3=F(variablesK3,t+tau/2);

        vector<double> variablesK4(variables.size());
        for(int k =0;k<variables.size();k++){
            variablesK4[k]=variables[k]+tau * k3[k];
        }
        auto k4=F(variablesK4,t+tau);

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
