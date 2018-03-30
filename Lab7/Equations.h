
// Created by andrey on 29.03.18.
//

#ifndef LAB7_EQUATIONS_H
#define LAB7_EQUATIONS_H

#include <cassert>
#include "Params.h"
#include "math.h"

class Equations {
public:
    Params* par = new Params();
    double getExplicitValue(double h, double tau, double yPrev, double y, double yNext, double xPrev, double x, double xNext) {
            double aNext = calculateA(x,xNext,h);
            double a= calculateA(xPrev,x,h);
            return (tau / (h * h * par->c * par->p)) *
                   ((aNext) * (yNext - y) - (a) * (y - yPrev)) + y;
    }

    ~Equations(){delete par;}

    virtual double getBoundValueLeft(int j)=0;  // че то странное передал

    virtual double getBoundValueRight(int j)=0; // че то странное передал

    virtual double getBeginningValue(double x)=0;

    double calculateA(double xPrev, double x,double h) {   //для подсчета explicit
        //5 cлучаев так как считаем аналитически

        // уравнение для среднего отрезка-9x+6.5(c учетом параметров);
        auto middleIntegral =[](double z){return (-1.0/9)*log(-9*z + 6.5);};

        if (x<=par->x1){ // от нуля до x1
            auto a=(x-xPrev)/(par->k1*h);
//            std::cout<<1.0/a<<std::endl;
            return 1.0/a;
        }
        if ( (xPrev<=par->x1) && (x>par->x1) && (x<par->x2) ){
            auto a1= (par->x1-xPrev)/(par->k1 *h);
            auto a2= ( middleIntegral(x) - middleIntegral(par->x1) )/h;
//            std::cout<<1.0/(a1+a2)<<std::endl;
            return 1.0/(a1+a2);
        }

        if ( (xPrev>par->x1) && (x<par->x2) ){
            auto a = ( middleIntegral(x) - middleIntegral(xPrev) )/h;
//            std::cout<<1.0/(a)<<std::endl;
            return 1.0/a;
        }

        if ( (xPrev<par->x2) && (x>=par->x2) && (x<par->l) ){
            auto a1= ( middleIntegral(par->x2) - middleIntegral(xPrev) )/h;
            auto a2= (x-par->x2)/(par->k2 *h);
//            std::cout<<1.0/(a1+a2)<<std::endl;
            return 1.0/(a1+a2);
        }

        if (xPrev>=par->x2){
            auto a=(x-xPrev)/(par->k2*h);
//            std::cout<<1.0/(a)<<std::endl;
            return 1.0/a;
        }
        assert(false);
    }
};

class Equations1 : public Equations {

//    double getExplicitValue(double h, double tau, double yPrev, double y, double yNext) override {
//        double aNext = 1.0;
//        double a = 1.0;
//        return (tau / (h * h * c * p)) *
//               ((aNext) * (yNext - y) - (a) * (y - yPrev)) + y;
//    }

    double getBoundValueLeft(int j) override {
            return par->u0;
    }

    double getBoundValueRight(int j) override {
            return par->u0;
    }

    double getBeginningValue(double x) override {
            return par->u0 + x*(par->l-x);
    }

};


#endif //LAB7_EQUATIONS_H
