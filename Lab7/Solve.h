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

using namespace std;

struct Variable {  //объект, который содержит начало, шаг и кол-во шагов какой-либо переменной
public:
    Variable(double start,double step, int n):start(start),step(step),n(n){}
    double start;
    double step;
    int n; //кол-во шагов
};

struct GridParam{
public:
    Variable* X;
    Variable* T;
    GridParam(Variable* X, Variable* T):X(X), T(T){}
};

class Solve {
public:


    Solve(double h, double tau, double x0, double xf, double t0, double tf, double sigma=0){
        this->sigma=sigma;
        setGridParam(h, tau, x0, xf, t0, tf);
    }


    Solve(double h, double tau, double x0, int nx, double t0, int nt,double sigma=0){ 
        this->sigma=sigma;
        setGridParam(h, tau, x0, nx, t0, nt);
    
    }
    ~Solve(){
        delete gp->X;
        delete gp->T;
        delete gp;
        delete equations;
    }
    //tf- t конечная; xf- x конечная
    void setGridParam(double h, double tau, double x0, double xf, double t0, double tf){
        int nx= static_cast<int>((xf - x0) / h) +1;
        int nt= static_cast<int>((tf - t0) / tau) +1;
        setGridParam(h,tau,x0,nx,t0,nt);
    };

    //nx- кол-во точек по x;nt- кол-во точек по t
    GridParam setGridParam(double h, double tau, double x0, int nx, double t0, int nt){
        auto *X = new Variable(x0,h,nx);
        auto *T = new Variable(t0,tau,nt);
        this->gp  = new GridParam(X,T);
    };

    vector<vector<double>> calculateExplicit(){
        vector<vector<double>> U;// то есть сначала время.
        vector<double> U0(gp->X->n);//при t равном нулю

        U0[0] = equations->getBoundValueLeft(0);
        U0[U0.size()-1] = equations->getBoundValueLeft(0);
        for(int i=0;i<U0.size()-1;i++){
            U0[i]=equations->getBeginningValue(gp->X->start + i * gp->X->step);
        }
        U.push_back(U0);
//        printMatrix(U);
        double h = gp->X->step;
        double tau = gp->T->step;
        for(int i=1;i<gp->T->n;i++){
            vector<double> Ui(gp->X->n);
            Ui[0]=equations->getBoundValueLeft(i);
            Ui[Ui.size()-1]= equations->getBoundValueRight(i);
            for (int j = 1; j < gp->X->n-1; j++) {
                auto x = gp->X->start + gp->X->step*j;
                auto xPrev = x - gp->X->step;
                auto xNext = x + gp->X->step;
                Ui[j] = equations->getExplicitValue(h,tau,U[i-1][j-1],U[i-1][j],U[i-1][j+1], xPrev, x, xNext);
            }
            U.push_back(Ui);
  //          cout<<"size: "<<U.size()<<"  "<<U[0].size()<<endl;
       //     printMatrix(U);
        }
        return U;
    }

private:
    Equations* equations= new Equations1();
    double sigma = 0;
    GridParam *gp;
};


#endif //LAB7_SOLVE_H
