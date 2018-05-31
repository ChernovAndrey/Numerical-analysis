
// Created by andrey on 29.03.18.
//

#ifndef LAB9_EQUATIONS_H
#define LAB9_EQUATIONS_H

#include <cassert>
#include "Var.h"
#include "helping/workWithConsole.h"
#include "helping/matrixOperations.h"
#include "Params.h"
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <tuple>

using namespace std;

class Equations {
public:
    virtual double getF(double x)=0;

    virtual double getLambda()=0;

    virtual double getKernel(double x, double s)=0;

    virtual double getKi(int i,double s)=0;

    virtual double getGj(int j,double x)=0;

};

class Equations1: public Equations{
public:
    double getF(double x) override {
        return 0.5*(1+sin(x));
    }

    double getLambda() override {
        return 0.5;
    }

    double getKernel(double x, double s) override {
        return (1-x*cos(x*s));
    }

// для метода замены ядра на вырожденное.
//Gi - функции от x. Ki - функции от s. ( получаются при представлении ядра, как вырожденного.
// расскладываем по формуле Тейлора ядро и берем первые три ненулевых члена.

    double getGj(int j,double x) override { // i - номер функции (от 1 до 3)
        if (j==1){
            return 1.0-x;
        }
        if (j==2){
            return 0.5*pow(x,3);
        }
        if (j==3){
            return -pow(x,5)/24.0;
        }
        assert(false);
    }

    double getKi(int i,double s) override { // i - номер функции (от 1 до 3)
        if (i==1){
            return 1.0;
        }
        if (i==2){
            return pow(s,2);
        }
        if (i==3){
            return pow(s,4);
        }
        assert(false);
    }

};


class Equations2: public Equations{
public:
    double getF(double x) override {
        return x*x+sqrt(x);
    }

    double getLambda() override {
        return 0.5;
    }

    double getKernel(double x, double s) override {
        return (1-x*cos(x*s));
    }



    // для метода замены ядра на вырожденное.
//Gi - функции от x. Ki - функции от s. ( получаются при представлении ядра, как вырожденного.
// расскладываем по формуле Тейлора ядро и берем первые три ненулевых члена.

    double getGj(int j,double x) override { // j - номер функции (от 1 до 3)
        if (j==1){
            return 1.0-x;
        }
        if (j==2){
            return 0.5*pow(x,3);
        }
        if (j==3){
            return -pow(x,5)/24.0;
        }
        assert(false);
    }

    double getKi(int i,double s) override { // i - номер функции (от 1 до 3)
        if (i==1){
            return 1.0;
        }
        if (i==2){
            return pow(s,2);
        }
        if (i==3){
            return pow(s,4);
        }
        assert(false);
    }


};
#endif //LAB9_EQUATIONS_H
