//
// Created by andrey on 11.12.17.
//

#ifndef LAB5_SOLVEBISECTION_H
#define LAB5_SOLVEBISECTION_H


#include "../Equation.h"
#include "cassert"
class SolveBisection: public SolveEq {
public:
    pair<double,double> interval;
    explicit SolveBisection(double a,double b):SolveEq(a,b){};
    double execute() override {
        double x1= a;
        double x2= b;
        assert(func(x1)*func(x2)<0);
        int countIter=0;
        bool flag = false;
        double c=0;//not uses this value
        double prC=0;//not uses this value

        while(!SolveEq::compareWithZero(2*abs((x2-x1)))){
        //while(!SolveEq::compareWithZero(2*abs(c-prC) ) || !flag){
            prC = c;
            c = (x1+x2)/2;
        //    if(SolveEq::compareWithZero(func(c))) return c;
            if(func(c)*func(x1)<=0){
                x2 = c;
            }else{
                x1 = c;
            }
            countIter++;
            if(countIter>1) flag = true;
        }
        std::cout<<"count Iterations(a="<<a<<",b="<<b<<")="<<countIter<<std::endl;
        return (x1+x2)/2;
    }
};


#endif //LAB5_SOLVEBISECTION_H
