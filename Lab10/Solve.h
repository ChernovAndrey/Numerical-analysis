//
// Created by andrey on 29.03.18.
//

#ifndef LAB9_SOLVE_H
#define LAB9_SOLVE_H

#include <iostream>
#include <vector>
#include <tuple>
#include "helping/workWithConsole.h"
#include "Params.h"
#include "helping/vectorOperations.h"
#include "Method.h"

using namespace std;


class Solve {
public:
double eps = 1e-7;
bool flagOut= true;//флаг выхода

    Solve(double h, double a, double b, double hs, double as, double bs) {
        int nx = static_cast<int>((b - a) / h) + 1;
        int ns = static_cast<int>((bs - as) / hs) + 1;
        init(h,a,nx,hs,as,ns);
    }

    Solve(double h, double a, int nx, double hs, double as, int ns) {
        init(h,a,nx,hs,as,ns);
    }


    void init(double h, double a, int nx, double hs, double as, int ns) {
        this->var = new Var(h,hs);
        setGridParam(h,a,nx,hs,as,ns);
    }

    ~Solve() {
        delete gp->X;
        delete gp->S;
        delete gp;
        delete var;
        delete equations;
    }

    //nx- кол-во точек по x;nt- кол-во точек по t
    GridParam setGridParam(double h,double a, int nx, double hs, double as, int ns) {
        auto *X = new Params(a, h, nx);
        auto *S = new Params(as, hs, ns);
        this->gp = new GridParam(X,S);
        this->var->setX(X);
        this->var->setS(S);
        cout<<"gp X and S n"<<endl;
        cout << gp->X->n << endl;
        cout << gp->S->n << endl;
    };
    vector<double> calculate() {
        return method->solve(equations,var);

    }


    Equations *equations = new Equations1();
    Method *method= new MethodReplaceKernel();
    GridParam *gp{};
    Var *var{};
};


#endif //LAB9_SOLVE_H
