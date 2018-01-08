//
// Created by andrey on 11.12.17.
//

#ifndef LAB5_NEWTON_H
#define LAB5_NEWTON_H


#include <cassert>
#include <iostream>
#include "SolveEq.h"
#include "../tests/functions.h"
using namespace std;
class SolveNewton: public SolveEq {
public:
    explicit SolveNewton(double a, double b):SolveEq(a,b){};
    double execute(double (*f)(double)) override {
        cout<<"------------------------------------------------------"<<endl;
        cout<<"a="<<a<<endl;
        cout<<"b="<<b<<endl;
        cout<<endl;
        assert(f(a)*f(b)<0);
        double xk= (f(a)*b-f(b)*a)/(f(a)-f(b));
        if(!((xk>=a)&&(xk<=b))) xk= (a+b)/2;
         xk=0;
        //assert((xk>=a)&&(xk<=b));
        cout<<"x0="<<xk<<endl;
        int countIter=0;
        double pr2Xk=a;
        double prXk=b;
        if(prXk==xk){
            prXk=(a+b)/2;
        }
       bool flagFirst=false;
       // while(!SolveEq::compareWithZero(f(xk))){
        while((!SolveEq::compareWithZero(xk-prXk)) || !flagFirst){
            if(countIter>0) pr2Xk = prXk;
            double  k = (f(xk)-f(prXk))/(xk-prXk);
            xk= xk - f(xk)/derivative(xk);
       //     xk= xk - f(xk)/secondDerivative(xk);
            if(!((xk>=a)&&(xk<=b)) ){
                cout<<derivative(prXk)<<" "<<prXk;
                xk= prXk - k*f(prXk)/derivative(prXk);
            }
            if(( !((xk>=a)&&(xk<=b)) ) || (SolveEq::compareWithZero( abs(xk-prXk)-abs(prXk-pr2Xk) )) ) {
                xk = (f(prXk)*pr2Xk-f(pr2Xk)*prXk)/(f(prXk)-f(pr2Xk));//при countiter=0 pr2xk = b
                if(!((xk>=a)&&(xk<=b))) {
                    xk = (f(prXk)*a-f(a)*prXk)/(f(prXk)-f(a));
                };
                if(!((xk>=a)&&(xk<=b))){
                    xk=(prXk+pr2Xk)/2;
                }
//                if(!((xk>=a)&&(xk<=b))){
//                    xk=(prXk+a)/2;
//                }

            }
            if(SolveEq::compareWithZero(abs(xk-prXk)-abs(prXk-pr2Xk))){
                cout<<"зацикливание";
                xk= (pr2Xk+prXk)/2;
            }
            countIter++;
            cout<<"x"<<countIter<<"="<<xk<<endl;
            assert((xk>=a)&&(xk<=b));
            flagFirst=true;
            prXk = xk;
        }
        cout<<"count Iterations(a="<<a<<",b="<<b<<")="<<countIter<<endl;
        cout<<"------------------------------------------------------"<<endl;
        return xk;
    }

};


#endif //LAB5_NEWTON_H
