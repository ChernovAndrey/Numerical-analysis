
// Created by andrey on 29.03.18.
//

#ifndef LAB9_EQUATIONS_H
#define LAB9_EQUATIONS_H

#include <cassert>
#include "Var.h"
#include "solveSystem/Sweep.h"
#include "helping/workWithConsole.h"
#include "helping/matrixOperations.h"
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <tuple>

using namespace std;

class Equations {
public:
    virtual int getKindLeft()=0;

    virtual int getKindUp()=0;

    virtual int getKindRight()=0;

    virtual int getKindDown()=0;

    virtual double getFi()=0;//неоднородная часть

    virtual double getBoundValueLeft(Var *var, int ix2)=0;

    virtual double getBoundValueUp(Var *var, int ix1)=0;

    virtual double getBoundValueDown(Var *var, int ix1)=0;

    virtual double getBoundValueRight(Var *var, int ix2)=0;

    virtual double getBeginningValue(Var *var, int ix1, int ix2 )=0;


    vector<vector<double>> getImplicitValue(Var *var, int it, GridParam* gp) {
        vector<vector<double>> matrix;
        vector<double> f;
        vector<double> Y;
        if((getKindRight()==1)&&(getKindLeft()==1)&&(getKindDown()==1)&&(getKindUp()==1)){
            vector<vector<double>> halfU(gp->X1->n);
            vector<double> halfU0(gp->X2->n);
            for (int j = 0; j < gp->X2->n; ++j) {
                halfU0[j] = getBoundValueUp(var,j);
            }
            halfU[0] = halfU0;
            for (int j = 1; j < gp->X1->n-1; ++j) {
                tie(matrix, f) = FactoryDiagMatrixL1R1(var, it,j);
                Y = (new Sweep(matrix, f))->solveSystem();
                Y.insert(Y.begin(), getBoundValueUp(var, j));
                Y.push_back( getBoundValueDown(var,j) );
                halfU[j] = Y;
            }
            vector<double> halfULast(gp->X2->n);
            for (int j = 0; j < gp->X2->n; ++j) {
                halfULast[j] = getBoundValueRight(var,j);
            }
            halfU[halfU.size()-1] = halfULast;

            halfU=transposeMatrix(halfU);

            //TODO: нормальную аппроксимацию фи(неоднородности)
            vector<vector<double>> UNext(gp->X2->n);
            vector<double> UNext0(gp->X1->n);
            for (int j = 0; j < gp->X1->n; ++j) {
                UNext0[j] = getBoundValueUp(var,j);
            }
            UNext[0] = UNext0;
            for (int j = 1; j < gp->X2->n-1; ++j) {
                tie(matrix, f) = FullFactoryDiagMatrixL1R1(var, it,j,halfU);
                Y = (new Sweep(matrix, f))->solveSystem();
                Y.insert(Y.begin(), getBoundValueLeft(var, j));
                Y.push_back( getBoundValueRight(var,j) );
                UNext[j] = Y;
            }

            vector<double> UNextLast(gp->X1->n);
            for (int j = 0; j < gp->X1->n; ++j) {
                UNextLast[j] = getBoundValueDown(var,j);
            }
            UNext[UNext.size()-1] = UNextLast;
            printMatrix(UNext);
            return UNext;

        }

//        if (getKindLeft() == 1) {
//            if (getKindUpDown() == 1) {
//                tie(matrix, f) = FactoryDiagMatrixL1R1(var, it,flagKv, std::move(YPr));
//                Y = (new Sweep(matrix, f))->solveSystem();
//                Y.insert(Y.begin(), getBoundValueLeft(var, it));
//          //      if (!this->flagKv) {
//                    Y.push_back(getBoundValueRight(var, it));
//           //     }
//            }
//
//            if (getKindUpDown() == 2) {
//                tie(matrix, f) = FactoryDiagMatrixL1R2(var, it);
//                Y = (new Sweep(matrix, f))->solveSystem();
//                Y.insert(Y.begin(), getBoundValueLeft(var, it));
//            }
//
//        }else{
//            if(getKindUpDown()==2){
//                tie(matrix, f) = FactoryDiagMatrixL2R2(var, it);
//                Y = (new Sweep(matrix, f))->solveSystem();
//            }
//        }
//
//        return Y;

    }

    pair<vector<vector<double>>, vector<double>>
    FullFactoryDiagMatrixL1R1(Var *var, int it, int ix1, const vector<vector<double>> &halfU) {  // на левой и правой границе условия первого рода.
        unsigned countDiag = 3;
        auto UPrev = halfU;
        auto n = var->X1.size() - 2;// так как y0 и yN я знаю
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h1 = var->h1;
        auto h2 = var->h2;
        auto tau = var->tau;
        auto y0 = getBoundValueLeft(var, ix1);
        auto yN = getBoundValueRight(var, ix1);
        for (int i = 0; i < n; i++) { //знаем y0 и yN; считаем только для y1...yN-1
            int j = i + 1;// индекс для X
            vector<double> strMatrix(countDiag);//строка матрицы
            strMatrix[1] = 2*(1/(h2*h2) +1/tau);
            if (i == 0) { // для y1
                strMatrix[0] = 0.0;
                strMatrix[2] = -1/(h2*h2);
                b[i] = (2/tau)*UPrev[ix1][j]+(1/(h1*h1))*( UPrev[ix1+1][j] - 2*UPrev[ix1][j] + UPrev[ix1-1][j] ) + getFi()+y0/(h2*h2);
                matrix[i] = strMatrix;
                continue;
            }


            if (i == n - 1) { // для yN-1
                strMatrix[2] = 0.0;
                strMatrix[0] = -1/(h2*h2);
                matrix[i] = strMatrix;
                b[i] = (2/tau)*UPrev[ix1][j]+(1/(h1*h1))*( UPrev[ix1+1][j] - 2*UPrev[ix1][j] + UPrev[ix1-1][j] ) + getFi()+yN/(h2*h2);
                continue;
            }
            strMatrix[0] = -1/(h2*h2);
            strMatrix[2] = -1/(h2*h2);
            b[i] = (2/tau)*UPrev[ix1][j]+(1/(h1*h1))*( UPrev[ix1+1][j] - 2*UPrev[ix1][j] + UPrev[ix1-1][j] ) + getFi();
            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }

    pair<vector<vector<double>>, vector<double>>
    FactoryDiagMatrixL1R1(Var *var, int it, int ix2) {  // на левой и правой границе условия первого рода.
        unsigned countDiag = 3;
        auto UPrev = var->U[it-1];
        auto n = var->X1.size() - 2;// так как y0 и yN я знаю
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h1 = var->h1;
        auto h2 = var->h2;
        auto tau = var->tau;
        auto y0 = getBoundValueUp(var, ix2);
        auto yN = getBoundValueDown(var, ix2);
        for (int i = 0; i < n; i++) { //знаем y0 и yN; считаем только для y1...yN-1
            int j = i + 1;// индекс для X
            vector<double> strMatrix(countDiag);//строка матрицы
            strMatrix[1] = 2*(1/(h1*h1) +1/tau);
            if (i == 0) { // для y1
                strMatrix[0] = 0.0;
                strMatrix[2] = -1/(h1*h1);
                b[i] = (2/tau)*UPrev[j][ix2]+(1/(h2*h2))*( UPrev[j][ix2+1] - 2*UPrev[j][ix2] + UPrev[j][ix2-1] ) + getFi()+y0/(h1*h1);
                matrix[i] = strMatrix;
                continue;
            }


            if (i == n - 1) { // для yN-1
                strMatrix[2] = 0.0;
                strMatrix[0] = -1/(h1*h1);
                b[i] = (2/tau)*UPrev[j][ix2]+(1/(h2*h2))*( UPrev[j][ix2+1] - 2*UPrev[j][ix2] + UPrev[j][ix2-1] ) + getFi()+yN/(h1*h1);
                matrix[i] = strMatrix;
                continue;
            }
            strMatrix[0] = -1/(h1*h1);
            strMatrix[2] = -1/(h1*h1);
            b[i] = (2/tau)*UPrev[j][ix2]+(1/(h2*h2))*( UPrev[j][ix2+1] - 2*UPrev[j][ix2] + UPrev[j][ix2-1] ) + getFi();
            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }


//    pair<vector<vector<double>>, vector<double>>
//    FactoryDiagMatrixL1R2(Var *var, int it) {  // на левой условие первого рода, на правой второго.
//        unsigned countDiag = 3;
//
//        auto c = var->c;
//        auto p = var->p;
//        auto sigma = var->sigma;
//        auto n = var->X.size() - 1;// так как y0  я знаю
//        vector<vector<double>> matrix(n);
//        vector<double> b(n);
//        auto h = var->h;
//        auto tau = var->tau;
//        auto y0 = getBoundValueLeft(var, it);
//        auto yPrevLayer = var->U[it - 1];
//        for (int i = 0; i < n; i++) { //знаем y0 ; считаем только для y1...yN
//            int j = i + 1;// индекс для X
//            vector<double> strMatrix(countDiag);//строка матрицы
//            double a = calculateA(var, j,it);
//            double aNext = calculateA(var, j + 1,it);
//
//
//            if (i == 0) { // для y1
//                strMatrix[0] = 0.0;
//                strMatrix[1] = (sigma / h) * (a + aNext) + (c * p * h) / tau;
//                strMatrix[2] = -(sigma / h) * aNext;
//                b[i] = (c * p * h / tau) * yPrevLayer[j] +
//                       (1 - sigma) * (getOmega(var, it, j, 0.5) - getOmega(var, it, j, -0.5)) + (sigma / h) * a * y0;
//                matrix[i] = strMatrix;
//                continue;
//            }
//
//
//            if (i == n - 1) { // для yN
//                strMatrix[2] = 0.0;
//                strMatrix[1] = 1.0;
//                strMatrix[0] =-( sigma*a/h )/(c*p*h/(2*tau) + sigma*a/h);
//                b[i] = (c*p*yPrevLayer[j]*h/(2*tau) + sigma * getP2(var,it) +
//                        (1-sigma)*( getP2(var,it-1) - getOmega(var,it,j,-0.5) )
//                       )/
//                        ( c*p*h/(2*tau) + sigma*a/h );
//                matrix[i] = strMatrix;
//                continue;
//            }
//
//            b[i] = (c * p * h / tau) * yPrevLayer[j] +
//                   (1 - sigma) * (getOmega(var, it, j, 0.5) - getOmega(var, it, j, -0.5));
//            strMatrix[0] = -(sigma / h) * a;
//            strMatrix[1] = (sigma / h) * (a + aNext) + (c * p * h) / tau;
//            strMatrix[2] = -(sigma / h) * aNext;
//            matrix[i] = strMatrix;
//        }
//        return make_pair(matrix, b);
//
//    }
//
//
//    pair<vector<vector<double>>, vector<double>>
//    FactoryDiagMatrixL2R2(Var *var, int it) {  // на левой условие первого рода, на правой второго.
//        unsigned countDiag = 3;
//
//        auto c = var->c;
//        auto p = var->p;
//        auto sigma = var->sigma;
//        auto n = var->X.size();
//        vector<vector<double>> matrix(n);
//        vector<double> b(n);
//        auto h = var->h;
//        auto tau = var->tau;
//       // auto y0 = getBoundValueLeft(var, it);
//        auto yPrevLayer = var->U[it - 1];
//        for (int i = 0; i < n; i++) { // считаем  для y0...yN
////            int j = i + 1;// индекс для X
//            vector<double> strMatrix(countDiag);//строка матрицы
//
//
//
//            if (i == 0) { // для y0
//                double aNext = calculateA(var, i + 1,it);
//
//                strMatrix[0] = 0.0;
//                strMatrix[1] = ( (1/tau) + (2*aNext*sigma)/(h*h) );
//                strMatrix[2] = -2*aNext*sigma/(h*h);
//                b[i] = (c * p / tau) * yPrevLayer[0] +
//                        (2/h)*(1 - sigma) * (getOmega(var, it, i, 0.5) - getP3(var,it) ) - (2*sigma / h) *getP3(var,it+1);
//                matrix[i] = strMatrix;
//                continue;
//            }
//
//
//            if (i == n - 1) { // для yN
//                double a = calculateA(var, i, it);
//
//                strMatrix[2] = 0.0;
//                strMatrix[1] = 1.0;
//                strMatrix[0] =-( sigma*a/h )/(c*p*h/(2*tau) + sigma*a/h);
//                b[i] = (c*p*yPrevLayer[i]*h/(2*tau) + sigma * getP3(var,it) +
//                        (1-sigma)*( getP3(var,it-1) - getOmega(var,it,i,-0.5) )
//                       )/
//                       ( c*p*h/(2*tau) + sigma*a/h );
//                matrix[i] = strMatrix;
//                continue;
//            }
//
//            double a = calculateA(var, i, it);
//            double aNext = calculateA(var, i + 1,it);
//
//            b[i] = (c * p * h / tau) * yPrevLayer[i] +
//                   (1 - sigma) * (getOmega(var, it, i, 0.5) - getOmega(var, it, i, -0.5));
//            strMatrix[0] = -(sigma / h) * a;
//            strMatrix[1] = (sigma / h) * (a + aNext) + (c * p * h) / tau;
//            strMatrix[2] = -(sigma / h) * aNext;
//            matrix[i] = strMatrix;
//        }
//        return make_pair(matrix, b);
//
//    }
//
//    double getP3(Var *var,int it){
//        return 0.0;
//    }
//
//    double getP2(Var *var, int it) {
//        auto t0 = var->t0;
//        auto Q = var->Q;
//        auto t = var->T[it];
//        if (t < t0) {
//            return 2 * Q * t;
//        }
//        return 0;
//
//    }

//
//class Equations2 : public Equations {
//public:
//
//    int getKindLeft() override {
//        return 1;
//    }
//
//    double getK(Var *var, int ix, int it) override {
//        double x = var->X[ix];
//        if (x<var->x1){ // аккуратно! сложная логика, это не для девушек
//            return var->k1;
//        }
//        if (x<var->x2){
//           return  var->k1*(x-var->x2)/(var->x1-var->x2) + var->k2*(x-var->x1)*(var->x2-var->x1);
//        }
//        return var->k2;
//    }
//
//private:
//    int getKindUpDown() override {
//        return 2;
//    } // вид граничных условий
//
////    double getExplicitValue(double h, double tau, double yPrev, double y, double yNext) override {
////        double aNext = 1.0;
////        double a = 1.0;
////        return (tau / (h * h * c * p)) *
////               ((aNext) * (yNext - y) - (a) * (y - yPrev)) + y;
////    }
//
//    double getBoundValueLeft(Var *var, int it) override {
//        return var->u0;
//    }
//
//    double getBoundValueRight(Var *var, int it) override {
//        auto sigma = var->sigma;
//        auto tau = var->tau;
//        auto h = var->h;
//        auto c = var->c;
//        auto p = var->p;
//        auto a = calculateA(var, static_cast<int>(var->X.size() - 1),it);// второай аргумент ix
//
//        if (sigma == 0) {
////            return ((c * p * h * var->U[it - 1][var->X.size() - 1]) / (2 * tau) +
////                    (getP2(var, it - 1) - a * var->U[it - 1][var->X.size() - 1])) / (c * p * h / (2 * tau));
//            return ( 2*tau/(c*p*h) *
//                    ( getP2(var,it-1) - getOmega(var, it, static_cast<int>(var->X.size() - 1), -0.5) )
//            ) + var->U[it-1][var->X.size()-1];
//        }
//        assert(false);
//    }
//
//    double getBeginningValue(Var *var, int ix) override {
////            return var->u0 + x*(var->l-x);
//        return var->u0;
//    }
//
};



class Equations1 : public Equations {
public:
    int getKindLeft() override {
        return 1;
    }

    int getKindUp() override {
        return 1;
    }

    int getKindRight() override {
        return 1;
    }

    int getKindDown() override {
        return 1;
    } // вид граничных условий

private:

    double getBoundValueLeft(Var *var, int ix2) override {
        return 1.0;
    }


    double getBoundValueRight(Var *var, int ix2) override {
        return 1.0;
    }

    double getBoundValueUp(Var *var, int ix1) override {
        return 1.0;
    }


    double getBoundValueDown(Var *var, int ix1) override {
        return 1.0;
    }

    double getBeginningValue(Var *var, int ix1, int ix2) override {
        return 0.0;
    }

    double getFi() override {
        return 0;
    }
};

#endif //LAB9_EQUATIONS_H
