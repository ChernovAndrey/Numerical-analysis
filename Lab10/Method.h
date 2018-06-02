//
// Created by andrey on 29.05.18.
//

#ifndef LAB10_METHOD_H
#define LAB10_METHOD_H

#include <iostream>
#include <vector>
#include "Equations.h"
#include "Var.h"
#include "solveSystem/Gauss.hpp"

using namespace std;

class Method {
public:
    virtual vector<double> solve(Equations *eq, Var *var)=0;

protected:
    //возвращаем коэффициенты при членах ряда
    vector<double> formula3_8(Equations *eq, Var *var, double x) { // замена интеграла сумой по формуле трех восьмых.
        //  double a = var->S[0];
        //   double b = var->S[var->S.size()-1];
        double h = var->hs;
        vector<double> result(var->S.size(), 0);
        for (int is = 0; is < var->S.size() - 1; is += 3) {
            if (is + 3 >= var->S.size()) {
                assert(false); //кол-во узлов в сетке не подходит для метода квадратур
            }
            // 0,3,6-ой коэффиценты учитываются два раза.

            result[is] += (3 * h / 8.0) * eq->getKernel(x, var->S[is]);
            result[is + 1] += (9 * h / 8.0) * eq->getKernel(x, var->S[is + 1]);
            result[is + 2] += (9 * h / 8.0) * eq->getKernel(x, var->S[is + 2]);
            result[is + 3] += (3 * h / 8.0) * eq->getKernel(x, var->S[is + 3]);
        }
        return result;
//        return (3*h/8.0)*(F(x,a)+3*F(x,a+h)+3*F(x,a+2*h) + F(x,b) );
    }


};

class MethodQuadr : public Method { // метод квадратур
    vector<double> solve(Equations *eq, Var *var) override {
        vector<vector<double>> A(var->X.size());
        vector<double> f(var->X.size());
        for (int ix = 0; ix < var->X.size(); ++ix) {
//            vector<double> strMatrix(var->X.size(),0);
            vector<double> coef = formula3_8(eq, var, var->X[ix]);
//            vector<double> coef = formula3(var,var->X[ix]);
            for (int j = 0; j < coef.size(); ++j) {
                coef[j] = -eq->getLambda() * coef[j];
            }
            coef[ix] += 1.0;
            f[ix] = eq->getF(var->X[ix]);
            A[ix] = coef;
        }
        auto result = Gauss::solveSystem(A, f);
        return result;
    }


};

class MethodSequence : public Method { // метод последовательных приближений.

private:
    double eps = 1e-2;
    vector<double> getBeginningValue(Equations *eq, Var *var) {
        vector<double> U0(var->X.size());
        for (int i = 0; i < var->X.size(); ++i) {
            U0[i] = eq->getF(var->X[i]);
        }
        return U0;
    }


public:
    vector<double> solve(Equations *eq, Var *var) override {
        auto U = getBeginningValue(eq,var);
        vector<double> UNext(var->X.size());
        bool flagFirst = true;//первый заход.
        int countIter = 0;
        while((normVectorC( diffVectors(UNext,U) ) > eps) || flagFirst){

            flagFirst = false;
            countIter++;
            for (int ix = 0; ix < var->X.size(); ++ix) {
                vector<double> coef = formula3_8(eq, var, var->X[ix]);
                double valueIntegral = 0.0;
                for (int j = 0; j < coef.size(); ++j) {
                    coef[j] = eq->getLambda() * coef[j]*U[j];
                    valueIntegral+=coef[j];
                }
                U=UNext;
                UNext[ix] = eq->getF(var->X[ix])+valueIntegral;
            }

        }

        cout<<"countIter="<<countIter<<endl;
        return UNext;
    }

};

class MethodReplaceKernel : public Method { // метод замены ядра на вырожденное.
    vector<double> solve(Equations *eq, Var *var) override {
       // сначала находим константы в разложении ядра.
        int countTermsSeries = eq->getCountTermsSeries();
        vector<vector<double>> A(countTermsSeries);
        vector<double> f(countTermsSeries);
        for (int i = 0; i < countTermsSeries; ++i) {
            vector<double> coef(countTermsSeries);
            for (int j = 0; j < countTermsSeries; ++j) {
                coef[j] = -eq->getLambda() * getAlpha(i,j,eq,var);
            }
            coef[i] += 1.0;
            f[i] = getBeta(i,eq,var);
            A[i] = coef;
        }
        auto C = Gauss::solveSystem(A, f);
        vector<double> U(var->X.size());
        for (int ix = 0; ix < var->X.size(); ++ix) {
            double sumSeries=0.0;
            for (int j = 0; j < C.size(); ++j) {
                sumSeries+=C[j]*eq->getGj(j,var->X[ix]);
            }
            U[ix]=eq->getF(var->X[ix]) + eq->getLambda()*sumSeries;
        }
        return U;
    }

private:
    double getAlpha(int i, int j, Equations* eq, Var* var){ // коэффиценты в формуле для слау. j - индекс по Gj,i - Ki
        //вычисляем значения интегралов по формуле трех восьмых.
        double h = var->hs;
        double valueIntegral = 0.0;
        for (int is = 0; is < var->S.size() - 1; is += 3) {
            if (is + 3 >= var->S.size()) {
                assert(false); //кол-во узлов в сетке не подходит для метода квадратур
            }
            auto f1 = eq->getGj(j,var->S[is]) * eq->getKi(i,var->S[is]);
            auto f2 = eq->getGj(j,var->S[is+1]) * eq->getKi(i,var->S[is+1]);
            auto f3 = eq->getGj(j,var->S[is+2]) * eq->getKi(i,var->S[is+2]);
            auto f4 = eq->getGj(j,var->S[is+3]) * eq->getKi(i,var->S[is+3]);
            valueIntegral+=(3.0*h/8.0)*(f1 + 3*f2 + 3*f3 + f4);
        }
        return valueIntegral;
    }

    double getBeta(int i, Equations* eq, Var* var){ // коэффиценты в формуле для слау. i - Ki
        //вычисляем значения интегралов по формуле трех восьмых.
        double h = var->hs;
        double valueIntegral = 0.0;
        for (int is = 0; is < var->S.size() - 1; is += 3) {
            if (is + 3 >= var->S.size()) {
                assert(false); //кол-во узлов в сетке не подходит для метода квадратур
            }
            auto f1 = eq->getF(var->S[is]) * eq->getKi(i,var->S[is]);
            auto f2 = eq->getF(var->S[is+1]) * eq->getKi(i,var->S[is+1]);
            auto f3 = eq->getF(var->S[is+2]) * eq->getKi(i,var->S[is+2]);
            auto f4 = eq->getF(var->S[is+3]) * eq->getKi(i,var->S[is+3]);
            valueIntegral+=(3.0*h/8.0)*(f1 + 3*f2 + 3*f3 + f4);
        }
        return valueIntegral;
    }

};






#endif //LAB10_METHOD_H
