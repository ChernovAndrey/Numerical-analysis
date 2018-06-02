
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


// для метода замены ядра на вырожденное.
//Gi - функции от x. Ki - функции от s. ( получаются при представлении ядра, как вырожденного.
// расскладываем по формуле Тейлора ядро и берем первые три ненулевых члена.

    virtual double getKi(int i,double s)=0; // i - номер функции (от 1 до 3)

    virtual double getGj(int j,double x)=0; // j - номер функции (от 1 до 3)

    virtual int getCountTermsSeries()=0;// количество ненулевых слагаемых разложения в ряд ядра.
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

    double getGj(int j,double x) override { // j - номер функции (от 1 до 3)
        if (j==0){
            return 1.0-x;
        }
        if (j==1){
            return 0.5*pow(x,3);
        }
        if (j==2){
            return -pow(x,5)/24.0;
        }
        assert(false);
    }

    double getKi(int i,double s) override { // i - номер функции (от 1 до 3)
        if (i==0){
            return 1.0;
        }
        if (i==1){
            return pow(s,2);
        }
        if (i==2){
            return pow(s,4);
        }
        assert(false);
    }

    int getCountTermsSeries() override {
        return 3;
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
        if (j==0){
            return 1.0-x;
        }
        if (j==1){
            return 0.5*pow(x,3);
        }
        if (j==2){
            return -pow(x,5)/24.0;
        }
        assert(false);
    }

    double getKi(int i,double s) override { // i - номер функции (от 1 до 3)
        if (i==0){
            return 1.0;
        }
        if (i==1){
            return pow(s,2);
        }
        if (i==2){
            return pow(s,4);
        }
        assert(false);
    }
    
    int getCountTermsSeries() override {
        return 3;
    }

};


class Equations3: public Equations{
public:
    double getF(double x) override {
        return 1.0;
        return x*x+sqrt(x);
    }

    double getLambda() override {
        return 2.0;
    }

    double getKernel(double x, double s) override {
        if ((x >= 0.5)&&(s <=0.5)){
            return (x - 0.5)*(0.5-s);
        }
        return 0.0;
    }

    // для метода замены ядра на вырожденное.
//Gi - функции от x. Ki - функции от s. ( получаются при представлении ядра, как вырожденного.
// расскладываем по формуле Тейлора ядро и берем первые три ненулевых члена.

    double getGj(int j,double x) override { // j - номер функции (от 1 до 3)
        if (j==0){
            if(x<=0.5){
                return 0.0;
            }
            return x-0.5;
        }
        assert(false);
    }

    double getKi(int i,double s) override { // i - номер функции (от 1 до 3)
        if (i==0){
            if (s>=0.5){
                return 0.0;
            }
            return 0.5-s;
        }
        assert(false);
    }

    int getCountTermsSeries() override {
        return 1;
    }

};


class EquationsSingular{
public:
    int n;//кол-во точек
    double arcLen;
    explicit EquationsSingular(int n) : n(n),arcLen(2*M_PI/n){};
    // на единичной окружности с центром в точке (0,0)
    double getF(int i){ // номер точки на круге от 1 до N
        return cos(3 * 2*M_PI*(i-1.0)/n);
    }

    pair<double,double> getKernel(pair<double,double> r, pair<double,double> p){
        double distance2 =(r.first-p.first)*(r.first-p.first) + (r.second-p.second)*(r.second-p.second);    //расстояние между точками в квадрате.
        return make_pair( -(r.second-p.second) / (2*M_PI*distance2)
                ,
                           (r.first-p.first)/(2*M_PI*distance2)
        );
    }

    pair<double,double> getNormal(pair<double,double> r){ //единичная нормаль к окружности.
        double a = sqrt(r.first*r.first + r.second*r.second);
        return make_pair(r.first/a,r.second/a);
    };

    pair<double,double> getCheckPoint(int i){ // контрольная точка
        return make_pair(
                cos( 2*M_PI*(i-0.5)/n ),
                sin( 2*M_PI*(i-0.5)/n )
        );
    };

    pair<double,double> getCalcPoint(int j){ // расчетная точка
        return make_pair(
                cos( 2*M_PI*(j-1.0)/n ),
                sin( 2*M_PI*(j-1.0)/n )
        );
    };

};

#endif //LAB9_EQUATIONS_H
