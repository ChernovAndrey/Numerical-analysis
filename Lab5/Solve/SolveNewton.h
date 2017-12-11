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
    double execute() override {
        cout<<"------------------------------------------------------"<<endl;
        cout<<"a="<<a<<endl;
        cout<<"b="<<b<<endl;
        cout<<endl;
        assert(func(a)*func(b)<0);
        double xk= (func(a)*b-func(b)*a)/(func(a)-func(b));
        //double xk= 8;
        assert((xk>=a)&&(xk<=b));
        cout<<"x0="<<xk<<endl;
        int countIter=0;
        double pr2Xk=b;
        double prXk=xk;
        while(!SolveEq::compareWithZero(func(xk))){
            if(countIter>0) pr2Xk = prXk;
            prXk = xk;
            xk= xk - func(xk)/derivative(xk);
            if(( !((xk>=a)&&(xk<=b)) ) || (SolveEq::compareWithZero( abs(xk-prXk)-abs(prXk-pr2Xk) )) ) {
                xk = (func(prXk)*pr2Xk-func(pr2Xk)*prXk)/(func(prXk)-func(pr2Xk));//при countiter=0 pr2xk = b
                if(!((xk>=a)&&(xk<=b))) xk = (prXk+pr2Xk)/2;
            }

            countIter++;
            cout<<"x"<<countIter<<"="<<xk<<endl;
            assert((xk>=a)&&(xk<=b));
        }
        cout<<"count Iterations(a="<<a<<",b="<<b<<")="<<countIter<<endl;
        cout<<"------------------------------------------------------"<<endl;
        return xk;
    }

};


#endif //LAB5_NEWTON_H
