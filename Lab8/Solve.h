//
// Created by andrey on 29.03.18.
//

#ifndef LAB7_SOLVE_H
#define LAB7_SOLVE_H

#include <iostream>
#include <vector>
#include <tuple>
#include "Equations.h"
#include "helping/workWithConsole.h"
#include "Params.h"
#include "helping/vectorOperations.h"
#include "Var.h"

using namespace std;


class Solve {
public:


    Solve(double h, double tau, double x0, double xf, double t0, double tf) {
        int nx = static_cast<int>((xf - x0) / h) + 1;
        int nt = static_cast<int>((tf - t0) / tau) + 1;
        init(h, tau, x0, nx, t0, nt);
    }


    Solve(double h, double tau, double x0, int nx, double t0, int nt) {
        init(h, tau, x0, nx, t0, nt);
    }

    void init(double h, double tau, double x0, int nx, double t0, int nt) {
        this->var = new Var(h, tau);
        setGridParam(h, tau, x0, nx, t0, nt);
    }

    ~Solve() {
        delete gp->X;
        delete gp->T;
        delete gp;
        delete equations;
        delete var;
    }

    //nx- кол-во точек по x;nt- кол-во точек по t
    GridParam setGridParam(double h, double tau, double x0, int nx, double t0, int nt) {
        auto *X = new Params(x0, h, nx);
        auto *T = new Params(t0, tau, nt);
        this->gp = new GridParam(X, T);
        this->var->setX(X);
        this->var->setT(T);
        cout << gp->X->n << endl;
    };


    vector<vector<double>> calculate() {

        vector<double> U0(gp->X->n);//при t равном нулю
        for (int i = 0; i < U0.size(); i++) {
            U0[i] = equations->getBeginningValue(var, i);
        }
        var->U.push_back(U0);

        double h = gp->X->step;
        double tau = gp->T->step;

        vector<double> U1(gp->X->n);//при t равном единице

        double a = equations->getA();
        for (int i = 0; i < U0.size(); i++) {
            U1[i] = equations->getBeginningValue(var, i) + tau * equations->getFirstValue(var, i) +
                    (a * a * tau * tau / 2) *
                    equations->getSecondDerivative(var, i);
        }

        var->U.push_back(U1);

        for (int i = 2; i < gp->T->n; i++) {
            vector<double> UiEx(gp->X->n);
            UiEx[0] = equations->getBoundValueLeft(var, i);
            UiEx[UiEx.size() - 1] = equations->getBoundValueRight(var, i);
            for (int j = 1; j < gp->X->n - 1; j++) {
                UiEx[j] = equations->getExplicitValue(var, i, j);
            }
            var->U.push_back(UiEx);
        }
        return var->U;

    }


    Equations *equations = new Equations1();
    GridParam *gp;
    Var *var;
};


#endif //LAB7_SOLVE_H
