//
// Created by andrey on 29.03.18.
//

#ifndef LAB9_SOLVE_H
#define LAB9_SOLVE_H

#include <iostream>
#include <vector>
#include <tuple>
#include "Equations.h"
#include "helping/workWithConsole.h"
#include "Params.h"
#include "helping/vectorOperations.h"

using namespace std;


class Solve {
public:


    Solve(double h1, double h2,double tau, double x1b, double x1f, double x2b, double x2f, double t0, double tf) {
        int nx1 = static_cast<int>((x1f - x1b) / h1) + 1;
        int nx2 = static_cast<int>((x2f - x2b) / h2) + 1;
        int nt = static_cast<int>((tf - t0) / tau) + 1;
        init(h1,h2, tau, x1b, nx1,x2b,nx2, t0, nt);
    }


//    Solve(double h, double tau, double x0, int nx, double t0, int nt, double sigma = 0) {
//        init(h, tau, x0, nx, t0, nt, sigma);
//    }

    void init(double h1, double h2, double tau, double x1b, int nx1, double x2b, double nx2, double t0, int nt) {
        this->sigma = sigma;
        this->var = new Var(h1, h2, tau);
        setGridParam(h1, h2, tau, x1b, nx1,x2b, nx2, t0, nt);
    }

    ~Solve() {
        delete gp->X1;
        delete gp->X2;
        delete gp->T;
        delete gp;
        delete equations;
        delete var;
    }

    //nx- кол-во точек по x;nt- кол-во точек по t
    GridParam setGridParam(double h1, double h2, double tau, double x1b, int nx1, double x2b, int nx2, double t0, int nt) {
        auto *X1 = new Params(x1b, h1, nx1);
        auto *X2 = new Params(x2b, h2, nx2);
        auto *T = new Params(t0, tau, nt);
        this->gp = new GridParam(X1, X2, T);
        this->var->setX(X1,X2);
        this->var->setT(T);
        cout<<"gp X n"<<endl;
        cout << gp->X1->n << endl;
        cout << gp->X2->n << endl;
    };
    vector<vector<vector<double>>> calculate() {

//        cout<<gp->X->step;
        vector<vector<double>> U0(gp->X1->n);//при t равном нулю

        vector<double> Uup(gp->X2->n); // верхние гран усл
        for (int i = 0; i < gp->X2->n; ++i) {
            Uup[i] = equations->getBoundValueUp(var,i);
        }
        U0[0]=Uup;
        for (int i = 1; i < U0.size()-1; i++) {
            vector<double> Ustr(gp->X2->n);
            Ustr[0] = equations->getBoundValueLeft(var,i);
            for (int j = 1; j < gp->X2->n-1; ++j) {
                Ustr[j] = equations->getBeginningValue(var, j, i);
            }
            Ustr[Ustr.size()-1] = equations->getBoundValueRight(var,i);

            U0[i]=(Ustr);
        }

        vector<double> Udown(gp->X2->n); // нижние гран усл
        for (int i = 0; i < gp->X2->n; ++i) {
            Udown[i] = equations->getBoundValueUp(var,i);
        }
        U0[U0.size()-1]=Udown;

//        printVector("U0")
        var->U.push_back(U0);
        printMatrix(U0);
        double h1 = gp->X1->step;
        double h2 = gp->X2->step;
        double tau = gp->T->step;
        for (int i = 1; i < gp->T->n; i++) {
              auto Ui = equations->getImplicitValue(var, i,gp);
              var->U.push_back(Ui);
        }
        return var->U;

    }


    Equations *equations = new Equations1();
    double sigma = 0;
    GridParam *gp;
    Var *var;
};


#endif //LAB9_SOLVE_H
