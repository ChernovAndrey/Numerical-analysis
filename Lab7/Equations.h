
// Created by andrey on 29.03.18.
//

#ifndef LAB7_EQUATIONS_H
#define LAB7_EQUATIONS_H

#include <cassert>
#include "Var.h"
#include "solveSystem/Sweep.h"
#include "helping/workWithConsole.h"
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <tuple>

using namespace std;

class Equations {
public:
    bool flagKv = false; // флаг квазилинейности.
    virtual int getKindLeft()=0;

    virtual int getKindRight()=0;

    virtual double getK(Var *var, int ix, int it)=0;

    double getExplicitValue(Var *var, int it, int ix) {  //ix - текущий индекс по x
        auto U = var->U;
        double aNext = calculateA(var, ix + 1,it);
        double a = calculateA(var, ix,it);
//        return (1-var->sigma)*(var->tau / (var->h  * var->c * var->p)) *
//               ((aNext) * (U[it-1][ix+1] - U[it-1][ix]) - (a) * (U[it-1][ix] - U[it-1][ix-1])) + U[it-1][ix];

        return (1 - var->sigma) * (var->tau / (var->h * var->c * var->p)) *
               (getOmega(var, it, ix, 0.5) - getOmega(var, it, ix, -0.5)) + U[it - 1][ix];
    }

    double getOmega(Var *var, int it, int ix, double flag) { // flag +0.5 или минус 0.5
        auto U = var->U;
        if (flag == 0.5) {
            auto a = calculateA(var, ix + 1,it);
            return (a / var->h) * (U[it - 1][ix + 1] - U[it - 1][ix]);
        }

        if (flag == -0.5) {
            auto a = calculateA(var, ix,it);
            return (a / var->h) * (U[it - 1][ix] - U[it - 1][ix - 1]);
        }
        assert(false);
    }


    virtual double getBoundValueLeft(Var *var, int it)=0;  // че то странное передал ересь какая-то=)


    virtual double getBoundValueRight(Var *var, int it)=0;

    virtual double getBeginningValue(Var *var, int ix)=0;


    vector<double> getImplicitValue(Var *var, int it,bool flagKv= false,vector<double> YPr= vector<double>()) {
        vector<vector<double>> matrix;
        vector<double> f;
        vector<double> Y;
        if (getKindLeft() == 1) {
            if (getKindRight() == 1) {
                tie(matrix, f) = FactoryDiagMatrixL1R1(var, it,flagKv, std::move(YPr));
                auto sweep=new Sweep(matrix, f);
                Y = (sweep)->solveSystem();
                delete sweep;
                Y.insert(Y.begin(), getBoundValueLeft(var, it));
          //      if (!this->flagKv) {
                    Y.push_back(getBoundValueRight(var, it));
           //     }
            }

            if (getKindRight() == 2) {
                tie(matrix, f) = FactoryDiagMatrixL1R2(var, it);
                auto sweep=new Sweep(matrix, f);
                Y = (sweep)->solveSystem();
                delete sweep;
                Y.insert(Y.begin(), getBoundValueLeft(var, it));
            }

        }else{
            if(getKindRight()==2){
                tie(matrix, f) = FactoryDiagMatrixL2R2(var, it);
                auto sweep=new Sweep(matrix, f);
                Y = (sweep)->solveSystem();
                delete sweep;
            }
        }

        return Y;

    }

    pair<vector<vector<double>>, vector<double>>
    FactoryDiagMatrixL1R1(Var *var, int it,bool flagKv=false, vector<double> YPr= vector<double>()) {  // на левой и правой границе условия первого рода.
        unsigned countDiag = 3;

        auto c = var->c;
        auto p = var->p;
        auto sigma = var->sigma;
        auto n = var->X.size() - 2;// так как y0 и yN я знаю
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h = var->h;
        auto tau = var->tau;
        auto y0 = getBoundValueLeft(var, it);
        auto yN = getBoundValueRight(var, it);
        auto yPrevLayer = var->U[it - 1];
        for (int i = 0; i < n; i++) { //знаем y0 и yN; считаем только для y1...yN-1
            int j = i + 1;// индекс для X
            vector<double> strMatrix(countDiag);//строка матрицы
            double a = calculateA(var, j,it);
            double aNext = calculateA(var, j + 1,it);

            if (i == 0) { // для y1
                strMatrix[0] = 0.0;
                strMatrix[1] = (sigma / h) * (a + aNext) + (c * p * h) / tau;
                strMatrix[2] = -(sigma / h) * aNext;
                if (flagKv){
                    b[i] = (c * p * h / tau) * YPr[j] +
                           (1 - sigma) * (getOmega(var, it, j, 0.5) - getOmega(var, it, j, -0.5)) + (sigma / h) * a * y0;
                }else{
                    b[i] = (c * p * h / tau) * yPrevLayer[j] +
                        (1 - sigma) * (getOmega(var, it, j, 0.5) - getOmega(var, it, j, -0.5)) + (sigma / h) * a * y0;
                }
                matrix[i] = strMatrix;
                continue;
            }


            if (i == n - 1) { // для yN-1
                strMatrix[2] = 0.0;
                strMatrix[1] = (sigma / h) * (a + aNext) + (c * p * h) / tau;
                strMatrix[0] = -(sigma / h) * a;
                if (flagKv){
                    b[i] = (c * p * h / tau) *YPr[j] +
                           (1 - sigma) * (getOmega(var, it, j, 0.5) - getOmega(var, it, j, -0.5)) +
                           (sigma / h) * aNext * yN;
                }else {
                    b[i] = (c * p * h / tau) * yPrevLayer[j] +
                           (1 - sigma) * (getOmega(var, it, j, 0.5) - getOmega(var, it, j, -0.5)) +
                           (sigma / h) * aNext * yN;
                }
                matrix[i] = strMatrix;
                continue;
            }
            if (flagKv){
                b[i] = (c * p * h / tau) * YPr[j] +
                       (1 - sigma) * (getOmega(var, it, j, 0.5) - getOmega(var, it, j, -0.5));
            }else {
                b[i] = (c * p * h / tau) * yPrevLayer[j] +
                       (1 - sigma) * (getOmega(var, it, j, 0.5) - getOmega(var, it, j, -0.5));
            }
            strMatrix[0] = -(sigma / h) * a;
            strMatrix[1] = (sigma / h) * (a + aNext) + (c * p * h) / tau;
            strMatrix[2] = -(sigma / h) * aNext;
            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }


    pair<vector<vector<double>>, vector<double>>
    FactoryDiagMatrixL1R2(Var *var, int it) {  // на левой условие первого рода, на правой второго.
        unsigned countDiag = 3;

        auto c = var->c;
        auto p = var->p;
        auto sigma = var->sigma;
        auto n = var->X.size() - 1;// так как y0  я знаю
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h = var->h;
        auto tau = var->tau;
        auto y0 = getBoundValueLeft(var, it);
        auto yPrevLayer = var->U[it - 1];
        for (int i = 0; i < n; i++) { //знаем y0 ; считаем только для y1...yN
            int j = i + 1;// индекс для X
            vector<double> strMatrix(countDiag);//строка матрицы
            double a = calculateA(var, j,it);
            double aNext = calculateA(var, j + 1,it);


            if (i == 0) { // для y1
                strMatrix[0] = 0.0;
                strMatrix[1] = (sigma / h) * (a + aNext) + (c * p * h) / tau;
                strMatrix[2] = -(sigma / h) * aNext;
                b[i] = (c * p * h / tau) * yPrevLayer[j] +
                       (1 - sigma) * (getOmega(var, it, j, 0.5) - getOmega(var, it, j, -0.5)) + (sigma / h) * a * y0;
                matrix[i] = strMatrix;
                continue;
            }


            if (i == n - 1) { // для yN
                strMatrix[2] = 0.0;
                strMatrix[1] = 1.0;
                strMatrix[0] =-( sigma*a/h )/(c*p*h/(2*tau) + sigma*a/h);
                b[i] = (c*p*yPrevLayer[j]*h/(2*tau) + sigma * getP2(var,it) +
                        (1-sigma)*( getP2(var,it-1) - getOmega(var,it,j,-0.5) )
                       )/
                        ( c*p*h/(2*tau) + sigma*a/h );
                matrix[i] = strMatrix;
                continue;
            }

            b[i] = (c * p * h / tau) * yPrevLayer[j] +
                   (1 - sigma) * (getOmega(var, it, j, 0.5) - getOmega(var, it, j, -0.5));
            strMatrix[0] = -(sigma / h) * a;
            strMatrix[1] = (sigma / h) * (a + aNext) + (c * p * h) / tau;
            strMatrix[2] = -(sigma / h) * aNext;
            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }


    pair<vector<vector<double>>, vector<double>>
    FactoryDiagMatrixL2R2(Var *var, int it) {  // на левой условие первого рода, на правой второго.
        unsigned countDiag = 3;

        auto c = var->c;
        auto p = var->p;
        auto sigma = var->sigma;
        auto n = var->X.size();
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h = var->h;
        auto tau = var->tau;
       // auto y0 = getBoundValueLeft(var, it);
        auto yPrevLayer = var->U[it - 1];
        for (int i = 0; i < n; i++) { // считаем  для y0...yN
//            int j = i + 1;// индекс для X
            vector<double> strMatrix(countDiag);//строка матрицы



            if (i == 0) { // для y0
                double aNext = calculateA(var, i + 1,it);

                strMatrix[0] = 0.0;
                strMatrix[1] = ( (1/tau) + (2*aNext*sigma)/(h*h) );
                strMatrix[2] = -2*aNext*sigma/(h*h);
                b[i] = (c * p / tau) * yPrevLayer[0] +
                        (2/h)*(1 - sigma) * (getOmega(var, it, i, 0.5) - getP3(var,it) ) - (2*sigma / h) *getP3(var,it+1);
                matrix[i] = strMatrix;
                continue;
            }


            if (i == n - 1) { // для yN
                double a = calculateA(var, i, it);

                strMatrix[2] = 0.0;
                strMatrix[1] = 1.0;
                strMatrix[0] =-( sigma*a/h )/(c*p*h/(2*tau) + sigma*a/h);
                b[i] = (c*p*yPrevLayer[i]*h/(2*tau) + sigma * getP3(var,it) +
                        (1-sigma)*( getP3(var,it-1) - getOmega(var,it,i,-0.5) )
                       )/
                       ( c*p*h/(2*tau) + sigma*a/h );
                matrix[i] = strMatrix;
                continue;
            }

            double a = calculateA(var, i, it);
            double aNext = calculateA(var, i + 1,it);

            b[i] = (c * p * h / tau) * yPrevLayer[i] +
                   (1 - sigma) * (getOmega(var, it, i, 0.5) - getOmega(var, it, i, -0.5));
            strMatrix[0] = -(sigma / h) * a;
            strMatrix[1] = (sigma / h) * (a + aNext) + (c * p * h) / tau;
            strMatrix[2] = -(sigma / h) * aNext;
            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }

    double getP3(Var *var,int it){
        return 0.0;
    }

    double getP2(Var *var, int it) {
        auto t0 = var->t0;
        auto Q = var->Q;
        auto t = var->T[it];
        if (t < t0) {
            return 2 * Q * t;
        }
        return 0;

    }

    double calculateA(Var *var, int ix,int it) {
    //трапеции
        assert(ix>0);
        return (getK(var,ix,it-1)+getK(var,ix-1,it-1))/2.0;
        return var->h *
               1/( (var->X[ix] - var->X[ix - 1])*(1/getK(var,ix,it)+1/getK(var,ix-1,it))/2.0 );

        //5 cлучаев так как считаем аналитически
        return 1 / ((var->X[ix] - var->X[ix - 1])) * var->h;
        // уравнение для среднего отрезка-9x+6.5(c учетом параметров);
        auto middleIntegral = [](double z) { return (-1.0 / 9) * log(-9 * z + 6.5); };
        auto x = var->X[ix];
        auto xPrev = var->X[ix - 1];
        auto h = var->h;
        if (x <= var->x1) { // от нуля до x1
            auto a = (x - xPrev) / (var->k1 * h);
//            std::cout<<1.0/a<<std::endl;
            return 1.0 / a;
        }
        if ((xPrev <= var->x1) && (x > var->x1) && (x < var->x2)) {
            auto a1 = (var->x1 - xPrev) / (var->k1 * h);
            auto a2 = (middleIntegral(x) - middleIntegral(var->x1)) / h;
//            std::cout<<1.0/(a1+a2)<<std::endl;
            return 1.0 / (a1 + a2);
        }

        if ((xPrev > var->x1) && (x < var->x2)) {
            auto a = (middleIntegral(x) - middleIntegral(xPrev)) / h;
//            std::cout<<1.0/(a)<<std::endl;
            return 1.0 / a;
        }

        if ((xPrev < var->x2) && (x >= var->x2) && (x < var->l)) {
            auto a1 = (middleIntegral(var->x2) - middleIntegral(xPrev)) / h;
            auto a2 = (x - var->x2) / (var->k2 * h);
//            std::cout<<1.0/(a1+a2)<<std::endl;
            return 1.0 / (a1 + a2);
        }

        if (xPrev >= var->x2) {
            auto a = (x - xPrev) / (var->k2 * h);
//            std::cout<<1.0/(a)<<std::endl;
            return 1.0 / a;
        }
        assert(false);
    }
};

class Equations2 : public Equations {
public:

    int getKindLeft() override {
        return 1;
    }

    double getK(Var *var, int ix, int it) override {
        double x = var->X[ix];
        if (x<var->x1){ // аккуратно! сложная логика, это не для девушек
            return var->k1;
        }
        if (x<var->x2){
           return  var->k1*(x-var->x2)/(var->x1-var->x2) + var->k2*(x-var->x1)*(var->x2-var->x1);
        }
        return var->k2;
    }

private:
    int getKindRight() override {
        return 2;
    } // вид граничных условий

//    double getExplicitValue(double h, double tau, double yPrev, double y, double yNext) override {
//        double aNext = 1.0;
//        double a = 1.0;
//        return (tau / (h * h * c * p)) *
//               ((aNext) * (yNext - y) - (a) * (y - yPrev)) + y;
//    }

    double getBoundValueLeft(Var *var, int it) override {
        return var->u0;
    }

    double getBoundValueRight(Var *var, int it) override {
        auto sigma = var->sigma;
        auto tau = var->tau;
        auto h = var->h;
        auto c = var->c;
        auto p = var->p;
        auto a = calculateA(var, static_cast<int>(var->X.size() - 1),it);// второай аргумент ix

        if (sigma == 0) {
//            return ((c * p * h * var->U[it - 1][var->X.size() - 1]) / (2 * tau) +
//                    (getP2(var, it - 1) - a * var->U[it - 1][var->X.size() - 1])) / (c * p * h / (2 * tau));
            return ( 2*tau/(c*p*h) *
                    ( getP2(var,it-1) - getOmega(var, it, static_cast<int>(var->X.size() - 1), -0.5) )
            ) + var->U[it-1][var->X.size()-1];
        }
        assert(false);
    }

    double getBeginningValue(Var *var, int ix) override {
//            return var->u0 + x*(var->l-x);
        return var->u0;
    }

};


class EquationZeroFlow : public Equations {
public:
    int getKindLeft() override {
        return 2;
    }

    double getK(Var *var, int ix,int it) override {
        return 1.0;
    }

    int getKindRight() override {
        return 2;
    } // вид граничных условий

private:
//    double getExplicitValue(double h, double tau, double yPrev, double y, double yNext) override {
//        double aNext = 1.0;
//        double a = 1.0;
//        return (tau / (h * h * c * p)) *
//               ((aNext) * (yNext - y) - (a) * (y - yPrev)) + y;
//    }

    double getBoundValueLeft(Var *var, int it) override {
        assert(false);
        return var->u0;
    }

    double getBoundValueRight(Var *var, int it) override {
        assert(false);
        return var->u0;
    }

    double getBeginningValue(Var *var, int ix) override {
        auto x = var->X[ix];
        return var->u0 + x * (var->l - x);
    }

};


class Equations1 : public Equations {
public:
    int getKindLeft() override {
        return 1;
    }

    double getK(Var *var, int ix,int it) override {
        return 1;
    }

    int getKindRight() override {
        return 1;
    } // вид граничных условий

private:
//    double getExplicitValue(double h, double tau, double yPrev, double y, double yNext) override {
//        double aNext = 1.0;
//        double a = 1.0;
//        return (tau / (h * h * c * p)) *
//               ((aNext) * (yNext - y) - (a) * (y - yPrev)) + y;
//    }

    double getBoundValueLeft(Var *var, int it) override {
        return var->u0;
    }

    double getBoundValueRight(Var *var, int it) override {
        return var->u0;
    }

    double getBeginningValue(Var *var, int ix) override {
        auto x = var->X[ix];
        return var->u0 + x * (var->l - x);
    }

};

// unused
//class EquationsTest : public Equations { //deprecated
//public:
//    int getKindLeft() override {
//        return 1;
//    }
//
//    int getKindRight() override {
//        return 1;
//    } // вид граничных условий
//
//private:
////    double getExplicitValue(double h, double tau, double yPrev, double y, double yNext) override {
////        double aNext = 1.0;
////        double a = 1.0;
////        return (tau / (h * h * c * p)) *
////               ((aNext) * (yNext - y) - (a) * (y - yPrev)) + y;
////    }
//
//    double getBoundValueLeft(Var *var, int it) override {
//        return 0.0;
//    }
//
//    double getBoundValueRight(Var *var, int it) override {
//        return 0.0;
//    }
//
//    double getBeginningValue(Var *var, int ix) override {
//        auto x = var->X[ix];
//        return var->u0 + x * (var->l - x);
//    }
//
//};


class EquationsTest2 : public Equations {
public:
    int getKindLeft() override {
        return 1;
    }

    int getKindRight() override {
        return 1;
    } // вид граничных условий

//    double getExplicitValue(double h, double tau, double yPrev, double y, double yNext) override {
//        double aNext = 1.0;
//        double a = 1.0;
//        return (tau / (h * h * c * p)) *
//               ((aNext) * (yNext - y) - (a) * (y - yPrev)) + y;
//    }

    double getBoundValueLeft(Var *var, int it) override {//длина начальная ноль
        return 1/sqrt(var->T[it]);
    }

    double getBoundValueRight(Var *var, int it) override {// длина конечная один
        double t= var->T[it];
        return (1/sqrt(t))*exp( -1/(4*t) ) ;
    }

    double getBeginningValue(Var *var, int ix) override { // процесс от 0.1 до 1.1
        double t =0.1;
        auto x = var->X[ix];
        return (1/sqrt(t))* exp( -x*x/(4*t) );
    }

    double getK(Var *var, int ix, int it) override {
        return 1;
    }

};



class Equations3 : public Equations {
private:
    double kappa0=0.5;
    double c=5.0;
    double delta=2.0;

public:
    Equations3(){
        flagKv=true;
    }
    int getKindLeft() override {
        return 1;
    }

    int getKindRight() override {
        return 1;
    } // вид граничных условий



    double getBoundValueLeft(Var *var, int it) override {
        double u = pow((delta*c*c/kappa0),1.0/delta);
        return u*pow(var->T[it],1.0/delta);

    }

    double getBoundValueRight(Var *var, int it) override {
        //assert(false);
      //  return 0;
        double xf= 10.0;
        auto t = var->T[it];
        if (xf<c*t) {
            return pow((delta*c/kappa0) *(c*t-xf),1.0/delta);;
        }else return 0;
    }

    double getBeginningValue(Var *var, int ix) override {
        return 0;
    }

    double getK(Var *var, int ix,int it) override {
//        assert(ix>0);
        assert(it>=0);
        return  kappa0*pow((var->U[it][ix]),delta);
    }

};
#endif //LAB7_EQUATIONS_H
