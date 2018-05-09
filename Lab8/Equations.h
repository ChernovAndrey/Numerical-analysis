
// Created by andrey on 29.03.18.
//

#ifndef LAB7_EQUATIONS_H
#define LAB7_EQUATIONS_H

#include <cassert>
#include "Var.h"
#include "helping/workWithConsole.h"
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <tuple>
#include <math.h>

using namespace std;

class Equations {
public:

    double getExplicitValue(Var *var, int it, int ix) {  //ix - текущий индекс по x
        auto U = var->U;
        auto tau= var->tau;
        auto h= var->h;
        auto a = getA();
        return ( (tau*tau*a*a)/(h*h) ) * ( var->U[it-1][ix+1] - 2*var->U[it-1][ix] + var->U[it-1][ix-1] )
                + 2*var->U[it-1][ix] - var->U[it-2][ix];
    }


    virtual double getBoundValueLeft(Var *var, int it)=0;


    virtual double getBoundValueRight(Var *var, int it)=0;

    virtual double getBeginningValue(Var *var, int ix)=0;

    virtual double getFirstValue(Var *var, int ix) = 0;

    double getA(){ // коэффицент уравнения
        return 1.0;
    }


    virtual double getSecondDerivative(Var *var, int ix)=0;

    double getNumSecondDerivative(Var* var, int ix){
        return ( getBeginningValue(var,ix+1) - 2*getBeginningValue(var,ix) + getBeginningValue(var,ix-1) )/(var->h*var->h);
    }

    virtual double getEpsNumSecondDerivative(Var* var, int ix) =0;


    virtual double getAnSecondDerivative(Var *var, int ix) =0;//вторая аналитическая производная
};


class Equations1 : public Equations {
public:


    double getBoundValueLeft(Var *var, int it) override {
        return 0.0;
    }

    double getBoundValueRight(Var *var, int it) override {
        return 0.0;
    }

    double getBeginningValue(Var *var, int ix) override {
      //  cout<<"X[ix]"<<var->X[ix]<<endl;
        return sin(M_PI * var->X[ix]);
    }

    double getFirstValue(Var *var, int ix) override {
        return 0.0;
    }

    double getSecondDerivative(Var *var, int ix) override {
//        return getAnSecondDerivative(var,ix);
        return getNumSecondDerivative(var,ix);
//        return getEpsNumSecondDerivative(var,ix);
    }

    double getAnSecondDerivative(Var *var, int ix) override {
        return -M_PI*M_PI*sin(M_PI*var->X[ix]);
    }

    double getEpsNumSecondDerivative(Var *var, int ix) override {
        auto getF = [](double x){
            auto pi = M_PI;
            return sin(M_PI * x);
        };
        auto x = var->X[ix];
        double eps = 0.01;
        return (getF(x+eps) - 2*getF(x) + getF(x-eps))/(eps*eps);

    }

};

class Equations2 : public Equations {
public:


    double getBoundValueLeft(Var *var, int it) override {
        return 0.0;
    }

    double getBoundValueRight(Var *var, int it) override {
        return 0.0;
    }

    double getBeginningValue(Var *var, int ix) override {
        auto x = var->X[ix];
        return x*(1-x);
    }

    double getEpsNumSecondDerivative(Var *var, int ix) override {
        return 0;
    }

    double getFirstValue(Var *var, int ix) override {
        return 0.0;
    }

    double getSecondDerivative(Var *var, int ix) override {
        return getAnSecondDerivative(var,ix);
    }

    double getAnSecondDerivative(Var *var, int ix) override {
        return -2.0;
    }


};


#endif //LAB7_EQUATIONS_H
