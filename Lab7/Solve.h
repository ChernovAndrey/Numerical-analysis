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

using namespace std;


class Solve {
public:


    Solve(double h, double tau, double x0, double xf, double t0, double tf, double sigma = 0) {
        int nx = static_cast<int>((xf - x0) / h) + 1;
        int nt = static_cast<int>((tf - t0) / tau) + 1;
        init(h, tau, x0, nx, t0, nt, sigma);
    }


    Solve(double h, double tau, double x0, int nx, double t0, int nt, double sigma = 0) {
        init(h, tau, x0, nx, t0, nt, sigma);
    }

    void init(double h, double tau, double x0, int nx, double t0, int nt, double sigma = 0) {
        this->sigma = sigma;
        this->var = new Var(h, tau, sigma);
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


    vector<double> merge(const vector<double> &UiEx, const vector<double> &UiIm, double sigma) {
        vector<double> Ui(UiEx.size());
        for (int i = 0; i < UiEx.size(); ++i) {
            cout << "Im:" << UiIm[i] << endl;
            cout << "Ex:" << UiEx[i] << endl;
            Ui[i] = UiIm[i] + UiEx[i];
        }
        return Ui;

    }

    vector<vector<double>> calculate() {

//        cout<<gp->X->step;
        vector<double> U0(gp->X->n);//при t равном нулю

        for (int i = 0; i < U0.size(); i++) {
            U0[i] = equations->getBeginningValue(var, i);
        }
//        printVector("U0")
        var->U.push_back(U0);
//        printMatrix(U);
        double h = gp->X->step;
        double tau = gp->T->step;
        for (int i = 1; i < gp->T->n; i++) {
            vector<double> UiEx(gp->X->n);
            if (var->sigma == 0.0) {
                UiEx[0] = (1 - var->sigma) * equations->getBoundValueLeft(var, i);
                for (int j = 1; j < gp->X->n; j++) {
                    UiEx[j] = equations->getExplicitValue(var, i, j);
                }
                //   UiEx[UiEx.size()-1]= (1-var->sigma)*equations->getBoundValueRight(var,i);
                var->U.push_back(UiEx);
            } else {
                auto Ui = equations->getImplicitValue(var, i);
//                var->U.push_back(Ui);
//                cout<<equations->flagKv<<endl;
                if (equations->flagKv) {
                    double eps = 1e-2;
                    int countIter = 0;
                    auto sizeU = var->U.size();
                    //  cout<<"sizeU"<<sizeU<<endl;
                    auto UiPrev = var->U[sizeU - 1];
                    //     printVector(UiPrev);
                    var->U[sizeU - 1] = Ui;
                    double residual = 100.0;
                    while (residual >= eps) {
                        //   for (int s = 0; s < countIter; s++) {
                        //cout<<"Ui"<<endl;
                        //printVector(Ui);
                        Ui = equations->getImplicitValue(var, i, equations->flagKv, UiPrev);
                        residual=normVectorC( diffVectors(Ui,var->U[sizeU-1]));
                        //cout<<"resid:"<<residual<<endl;
                        var->U[sizeU - 1] = Ui;
                        countIter++;
                        //  }
                    }
                    if (i % 100 == 0) {
                        cout << "finish" << Ui[0] << endl;
                    }
                    cout<<"countIter"<<countIter<<endl;
                    var->U[sizeU - 1] = UiPrev;
                }
                var->U.push_back(Ui);
            }
        }
        return var->U;

    }


    Equations *equations = new Equations3();
    double sigma = 0;
    GridParam *gp;
    Var *var;
};


#endif //LAB7_SOLVE_H
