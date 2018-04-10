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

using namespace std;


class Solve {
public:


    Solve(double h, double tau, double x0, double xf, double t0, double tf, double sigma=0){
        int nx= static_cast<int>((xf - x0) / h) +1;
        int nt= static_cast<int>((tf - t0) / tau) +1;
        init(h,tau,x0,nx,t0,nt,sigma);
    }


    Solve(double h, double tau, double x0, int nx, double t0, int nt,double sigma=0){
        init(h,tau,x0,nx,t0,nt,sigma);
    }

    void init(double h, double tau, double x0, int nx, double t0, int nt,double sigma=0){
        this->sigma=sigma;
        this->var= new Var(h,tau,sigma);
        setGridParam(h, tau, x0, nx, t0, nt);
    }

    ~Solve(){
        delete gp->X;
        delete gp->T;
        delete gp;
        delete equations;
        delete var;
    }
    //tf- t конечная; xf- x конечная
//    void setGridParam(double h, double tau, double x0, double xf, double t0, double tf){
//        setGridParam(h,tau,x0,nx,t0,nt);
//    };

    //nx- кол-во точек по x;nt- кол-во точек по t
    GridParam setGridParam(double h, double tau, double x0, int nx, double t0, int nt){
        auto *X = new Params(x0,h,nx);
        auto *T = new Params(t0,tau,nt);
        this->gp  = new GridParam(X,T);
        this->var->setX(X);
        this->var->setT(T);
        cout<<gp->X->n<<endl;
    };


    vector<double> merge(const vector<double> &UiEx, const vector<double> &UiIm, double sigma){
        vector<double> Ui(UiEx.size());
        for (int i = 0; i < UiEx.size(); ++i) {
            Ui[i]= sigma*UiIm[i] + (1-sigma)*UiEx[i];
        }
        return Ui;

    }

    vector<vector<double>> calculate(){
//        auto UExp = calculateExplicit();
//        auto UImp = calculateImplicit();

        cout<<gp->X->step;
        vector<double> U0(gp->X->n);//при t равном нулю

        for(int i=0;i<U0.size();i++){
            U0[i]=equations->getBeginningValue(var,i);
        }

        var->U.push_back(U0);
//        printMatrix(U);
        double h = gp->X->step;
        double tau = gp->T->step;
        for(int i=1;i<gp->T->n;i++){
            vector<double> UiEx(gp->X->n);
            UiEx[0]=equations->getBoundValueLeft(var,i);
            for (int j = 1; j < gp->X->n-1; j++) {
                UiEx[j] =equations->getExplicitValue(var,i,j);
            }
            UiEx[UiEx.size()-1]= equations->getBoundValueRight(var,i);

            vector<double> Ui(gp->X->n);
            auto UiIm = equations->getFullImplicitValue(var,i);
            var->U.push_back(merge(UiEx,UiIm,var->sigma) );
        }
        return var->U;

    }




    vector<vector<double>> calculateExplicit(){
     //   vector<vector<double>> U;// то есть сначала время.
        cout<<gp->X->step;
        vector<double> U0(gp->X->n);//при t равном нулю

        for(int i=0;i<U0.size();i++){
            U0[i]=equations->getBeginningValue(var,i);
        }

        var->U.push_back(U0);
//        printMatrix(U);
        double h = gp->X->step;
        double tau = gp->T->step;
        for(int i=1;i<gp->T->n;i++){
            vector<double> Ui(gp->X->n);
            Ui[0]=equations->getBoundValueLeft(var,i);
            for (int j = 1; j < gp->X->n-1; j++) {
                Ui[j] = equations->getExplicitValue(var,i,j);
            }
            Ui[Ui.size()-1]= equations->getBoundValueRight(var,i);
            var->U.push_back(Ui);
        }
        return var->U;
    }



    vector<vector<double>> calculateImplicit(){

        vector<double> U0(gp->X->n);//при t равном нулю

        U0[0] = equations->getBoundValueLeft(var,0);
        U0[U0.size()-1] = equations->getBoundValueLeft(var,gp->T->n-1);
        for(int i=0;i<U0.size()-1;i++){
            U0[i]=equations->getBeginningValue(var,i);
        }
        var->U.push_back(U0);
//        printMatrix(U);
        vector<double> X(U0.size());
        for(int i=1;i<gp->T->n;i++){
            vector<double> Ui(gp->X->n);
            var->U.push_back( equations->getFullImplicitValue(var,i) );
        }
        return var->U;
    }


//
//    vector<vector<double>> calculate(){
//
//    }


//private:
    Equations* equations= new Equations1();
    double sigma = 0;
    GridParam *gp;
    Var *var;
};


#endif //LAB7_SOLVE_H
