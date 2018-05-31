
// Created by andrey on 29.03.18.
//

#ifndef LAB9_EQUATIONS_H
#define LAB9_EQUATIONS_H

#include <cassert>
#include "Var.h"
#include "solveSystem/Sweep.h"
#include "helping/workWithConsole.h"
#include "helping/matrixOperations.h"
#include "Params.h"
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

    virtual double getFi(Var *var, int ix1, int ix2)=0;//неоднородная часть

    virtual double getBoundValueLeft(Var *var, int ix1)=0;

    virtual double getBoundValueUp(Var *var, int ix2)=0;

    virtual double getBoundValueDown(Var *var, int ix2)=0;

    virtual double getBoundValueRight(Var *var, int ix1)=0;

    virtual double getBeginningValue(Var *var, int ix1, int ix2)=0;

    vector<vector<double>> getImplicitValue(Var *var, int it, GridParam *gp) {
        vector<vector<double>> matrix;
        vector<double> f;
        vector<double> Y;
        if ((getKindRight() == 1) && (getKindLeft() == 1) && (getKindDown() == 2) && (getKindUp() == 2)) {
            vector<vector<double>> Uhalf(gp->X1->n);
            Uhalf = getFirstSweepU2D2L1R1(var, it, gp);
            cout << "Uhalf" << endl;
            printMatrix(Uhalf);

            auto U = getSecondSweepU2D2L1R1(var, it, gp, Uhalf);
            cout << "U " << endl;
            printMatrix(U);
            return U;
        }

        if ((getKindRight() == 2) && (getKindLeft() == 2) && (getKindDown() == 1) && (getKindUp() == 1)) {
            vector<vector<double>> Uhalf(gp->X1->n);
            Uhalf = getFirstSweepU1D1L2R2(var, it, gp);
            cout << "Uhalf" << endl;
            printMatrix(Uhalf);

            auto U = getSecondSweepU1D1L2R2(var, it, gp, Uhalf);
            cout << "U " << endl;
            printMatrix(U);
            return U;
        }

        if ((getKindRight() == 1) && (getKindLeft() == 1) && (getKindDown() == 1) && (getKindUp() == 1)) {
            vector<vector<double>> Uhalf(gp->X1->n);
            Uhalf = getFirstSweepU1D1L1R1(var, it, gp);
            cout << "Uhalf" << endl;
            printMatrix(Uhalf);

            auto U = getSecondSweepU1D1L1R1(var, it, gp, Uhalf);
            cout << "U " << endl;
            printMatrix(U);
            return U;
        }
        assert(false);
    }

    vector<vector<double>> getFirstSweepU1D1L1R1(Var *var, int it, GridParam *gp) {
        vector<vector<double>> U(gp->X1->n);
        vector<vector<double>> matrix;
        vector<double> f;
        vector<double> Y;

        //первая прогонка
        vector<double> U0(gp->X2->n);
        for (int j = 0; j < gp->X2->n; ++j) {
            U0[j] = getBoundValueUp(var, j);
        }
        U[0] = U0;


        for (int j = 1; j < gp->X1->n - 1; ++j) {
            tie(matrix, f) = FactoryDiagMatrixU1D1L1R1First(var, it, j);
            auto sweep=new Sweep(matrix, f);
            Y = (sweep)->solveSystem();
            delete sweep;
            Y.insert(Y.begin(), getBoundValueLeft(var, j));
            Y.push_back(getBoundValueRight(var, j));
            U[j] = Y;
        }

        vector<double> UN(gp->X2->n);
        for (int j = 0; j < gp->X2->n; ++j) {
            UN[j] = getBoundValueDown(var, j);
        }
        U[U.size()-1] = UN;

        return U;

    }


    vector<vector<double>> getSecondSweepU1D1L1R1(Var *var, int it, GridParam *gp, const vector<vector<double>> &Uhalf) {
        vector<vector<double>> U(gp->X1->n);
        vector<vector<double>> matrix;
        vector<double> f;
        vector<double> Y;

        // вторая прогонка
        vector<double> U0(gp->X1->n);
        for (int j = 0; j < gp->X1->n; ++j) {
            U0[j] = getBoundValueLeft(var, j);
        }
        U[0] = U0;

        for (int j = 1; j < gp->X2->n - 1; ++j) {
            tie(matrix, f) = FactoryDiagMatrixU1D1L1R1Second(var, it, j, Uhalf);
            auto sweep=new Sweep(matrix, f);
            Y = (sweep)->solveSystem();
            delete sweep;
            Y.insert(Y.begin(), getBoundValueUp(var, j));
            Y.push_back(getBoundValueDown(var, j));
            U[j] = Y;
        }


        vector<double> UN(gp->X1->n);
        for (int j = 0; j < gp->X1->n; ++j) {
            UN[j] = getBoundValueRight(var, j);
        }
        U[U.size() - 1] = UN;

        return transposeMatrix(U);

    }

    vector<vector<double>> getFirstSweepU2D2L1R1(Var *var, int it, GridParam *gp) {
        vector<vector<double>> U(gp->X1->n);
        vector<vector<double>> matrix;
        vector<double> f;
        vector<double> Y;

        //первая прогонка

        for (int j = 0; j < gp->X1->n; ++j) {
            tie(matrix, f) = FactoryDiagMatrixU2D2L1R1First(var, it, j);
            auto sweep=new Sweep(matrix, f);
            Y = (sweep)->solveSystem();
            delete sweep;
            Y.insert(Y.begin(), getBoundValueLeft(var, j));
            Y.push_back(getBoundValueRight(var, j));
            U[j] = Y;
        }

        return U;

    }


    vector<vector<double>> getFirstSweepU1D1L2R2(Var *var, int it, GridParam *gp) {
        vector<vector<double>> U(gp->X1->n);
        vector<vector<double>> matrix;
        vector<double> f;
        vector<double> Y;

        //первая прогонка

        //для нулевой строки.
        vector<double> U0(gp->X2->n);
        for (int j = 0; j < gp->X2->n; ++j) {
            U0[j] = getBoundValueUp(var, j);
        }
        U[0] = U0;

        for (int j = 1; j < gp->X2->n - 1; ++j) {
            tie(matrix, f) = FactoryDiagMatrixU1D1L2R2First(var, it, j);
            auto sweep=new Sweep(matrix, f);
            Y = (sweep)->solveSystem();
            delete sweep;
            U[j] = Y;
        }

        vector<double> UN(gp->X2->n);
        for (int j = 0; j < gp->X2->n; ++j) {
            UN[j] = getBoundValueDown(var, j);
        }
        U[U.size() - 1] = UN;

        return U;

    }

    vector<vector<double>> getSecondSweepU2D2L1R1(Var *var, int it, GridParam *gp, const vector<vector<double>> &Uhalf) {
        vector<vector<double>> U(gp->X2->n);
        vector<vector<double>> matrix;
        vector<double> f;
        vector<double> Y;


        //вторая прогонка; будем класть столбцы, как строки, потом транспонируем.

        //для нулевой строки.
        vector<double> U0(gp->X1->n);
        for (int j = 0; j < gp->X1->n; ++j) {
            U0[j] = getBoundValueLeft(var, j);
        }
        U[0] = U0;

        //c 1 по n-1 строку
        for (int j = 1; j < gp->X2->n - 1; ++j) {
            tie(matrix, f) = FactoryDiagMatrixU2D2L1R1Second(var, it, j, Uhalf);
            auto sweep=new Sweep(matrix, f);
            Y = (sweep)->solveSystem();
            delete sweep;
            U[j] = Y;
        }

        //n-1 строка
        vector<double> ULast(gp->X2->n);
        for (int j = 0; j < gp->X1->n; ++j) {
            ULast[j] = getBoundValueRight(var, j);
        }
        U[U.size() - 1] = ULast;

        return transposeMatrix(U);

    }


    vector<vector<double>> getSecondSweepU1D1L2R2(Var *var, int it, GridParam *gp, const vector<vector<double>> &Uhalf) {
        vector<vector<double>> U(gp->X1->n);
        vector<vector<double>> matrix;
        vector<double> f;
        vector<double> Y;

        //вторая прогонка

        for (int j = 0; j < gp->X1->n; ++j) {
            tie(matrix, f) = FactoryDiagMatrixU1D1L2R2Second(var, it, j, Uhalf);
            auto sweep=new Sweep(matrix, f);
            Y = (sweep)->solveSystem();
            delete sweep;
            Y.insert(Y.begin(), getBoundValueUp(var, j));
            Y.push_back(getBoundValueDown(var, j));
            U[j] = Y;
        }

        return transposeMatrix(U);

    }


    pair<vector<vector<double>>, vector<double>>
    FactoryDiagMatrixU1D1L1R1Second(Var *var, int it, int ix1, const vector<vector<double>> &halfU) {
        unsigned countDiag = 3;
        auto UPrev = halfU;
        auto n = var->X1.size() - 2;// так как y0 и yN я знаю
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h1 = var->h1;
        auto h2 = var->h2;
        auto tau = var->tau;
        auto y0 = getBoundValueUp(var, ix1);
        auto yN = getBoundValueDown(var, ix1);
        for (int i = 0; i < n; i++) { //знаем y0 и yN; считаем только для y1...yN-1
            int j = i + 1;// индекс для X
            vector<double> strMatrix(countDiag);//строка матрицы
            strMatrix[1] = 2 * (1 / (h2 * h2) + 1 / tau);
            if (i == 0) { // для y1
                strMatrix[0] = 0.0;
                strMatrix[2] = -1 / (h2 * h2);
                b[i] = (2 / tau) * UPrev[j][ix1] +
                       (1 / (h1 * h1)) * (UPrev[j][ix1+1] - 2 * UPrev[j][ix1] + UPrev[j][ix1 - 1])
                       + getFi(var, ix1, j) + y0 / (h2 * h2);
                matrix[i] = strMatrix;
                continue;
            }


            if (i == n - 1) { // для yN-1
                strMatrix[2] = 0.0;
                strMatrix[0] = -1 / (h2 * h2);
                matrix[i] = strMatrix;
                b[i] = (2 / tau) * UPrev[j][ix1] +
                       (1 / (h1 * h1)) * (UPrev[j][ix1 + 1] - 2 * UPrev[j][ix1] + UPrev[j][ix1 - 1])
                       + getFi(var, ix1, j) + yN / (h2 * h2);
                continue;
            }
            strMatrix[0] = -1 / (h2 * h2);
            strMatrix[2] = -1 / (h2 * h2);
            b[i] = (2 / tau) * UPrev[j][ix1] +
                   (1 / (h1 * h1)) * (UPrev[j][ix1 + 1] - 2 * UPrev[j][ix1] + UPrev[j][ix1 - 1])
                   + getFi(var, ix1, j);
            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }


    pair<vector<vector<double>>, vector<double>>
    FactoryDiagMatrixU2D2L1R1Second(Var *var, int it, int ix1,
                               const vector<vector<double>> &halfU) {  // на левой и правой границе условия первого рода.
        unsigned countDiag = 3;
        auto UPrev = halfU;
        auto n = var->X2.size();
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h1 = var->h1;
        auto h2 = var->h2;
        auto tau = var->tau;
        for (int i = 0; i < n; i++) {
            vector<double> strMatrix(countDiag);//строка матрицы
            strMatrix[1] = 2 * (1 / (h2 * h2) + 1 / tau);
            if (i == 0) { // для y0
                strMatrix[0] = 0.0;
                strMatrix[2] = -2 / (h2 * h2); // 2 - из-за y_{-1}
                b[i] = (2 / tau) * UPrev[i][ix1] +
                       (1 / (h1 * h1)) * (UPrev[i][ix1 + 1] - 2 * UPrev[i][ix1] + UPrev[i][ix1 - 1])
                       + getFi(var, ix1, i) + 2 * getBoundValueUp(var, i) / (h2);
                matrix[i] = strMatrix;
                continue;

            }


            if (i == n - 1) { // для yN
                strMatrix[2] = 0.0;
                strMatrix[0] = -2 / (h2 * h2);
                matrix[i] = strMatrix;
                b[i] = (2 / tau) * UPrev[i][ix1] +
                       (1 / (h1 * h1)) * (UPrev[i][ix1 + 1] - 2 * UPrev[i][ix1] + UPrev[i][ix1 - 1])
                       + getFi(var, ix1, i) + 2 * getBoundValueDown(var, i) / (h2);
                continue;

            }
            strMatrix[0] = -1 / (h2 * h2);
            strMatrix[2] = -1 / (h2 * h2);
            b[i] = (2 / tau) * UPrev[i][ix1] +
                   (1 / (h1 * h1)) * (UPrev[i][ix1 + 1] - 2 * UPrev[i][ix1] + UPrev[i][ix1 - 1])
                   + getFi(var, ix1, i);
            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }


    pair<vector<vector<double>>, vector<double>>
    FactoryDiagMatrixU1D1L2R2Second(Var *var, int it, int ix1,
                               const vector<vector<double>> &halfU) {  // на левой и правой границе условия первого рода.
        unsigned countDiag = 3;
        auto UPrev = halfU;
        auto n = var->X2.size() - 2;
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h1 = var->h1;
        auto h2 = var->h2;
        auto tau = var->tau;
        auto y0 = getBoundValueUp(var, ix1);
        auto yN = getBoundValueDown(var, ix1);
        for (int i = 0; i < n; i++) {
            int j = i + 1;
            vector<double> strMatrix(countDiag);//строка матрицы
            strMatrix[1] = 2 * (1 / (h2 * h2) + 1 / tau);
            double lambdaX2 = 0;

            if (ix1 == var->X1.size() - 1) {
//                cout<<"ix1=n"
                lambdaX2 = (2 * UPrev[j][ix1 - 1] - 2 * UPrev[j][ix1] + 2 * h2 * getBoundValueRight(var, j));
            } else {
                if (ix1 == 0) {
                    lambdaX2 = (2 * UPrev[j][ix1 + 1] - 2 * UPrev[j][ix1] + 2 * h2 * getBoundValueLeft(var, j));
                } else {
                    lambdaX2 = (UPrev[j][ix1 + 1] - 2 * UPrev[j][ix1] + UPrev[j][ix1 - 1]);
                }
            }

            b[i] = (2 / tau) * UPrev[j][ix1] +
                   (1 / (h2 * h2)) * lambdaX2
                   + getFi(var, ix1, j);

            if (i == 0) { // для y1
                strMatrix[0] = 0.0;
                strMatrix[2] = -1 / (h2 * h2);
                matrix[i] = strMatrix;
                b[i] += y0 / (h2 * h2);
                continue;
            }

            if (i == n - 1) { // для yN
                strMatrix[2] = 0.0;
                strMatrix[0] = -1 / (h2 * h2);
                matrix[i] = strMatrix;
                b[i] += yN / (h2 * h2);
                continue;

            }
            strMatrix[0] = -1 / (h2 * h2);
            strMatrix[2] = -1 / (h2 * h2);
            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }


    pair<vector<vector<double>>, vector<double>>
    FactoryDiagMatrixU1D1L1R1First(Var *var, int it, int ix2) {  // на левой и правой границе условия первого рода.
        unsigned countDiag = 3;
        auto UPrev = var->U[it - 1];
        auto n = var->X1.size() - 2;// так как y0 и yN я знаю
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h1 = var->h1;
        auto h2 = var->h2;
        auto tau = var->tau;
//        cout<<"ix2 "<<ix2<<endl;
        auto y0 = getBoundValueLeft(var, ix2);
        auto yN = getBoundValueRight(var, ix2);
        for (int i = 0; i < n; i++) { //знаем y0 и yN; считаем только для y1...yN-1
            int j = i + 1;// индекс для X
            vector<double> strMatrix(countDiag);//строка матрицы
            strMatrix[1] = 2 * (1 / (h1 * h1) + 1 / tau);
            if (i == 0) { // для y1
                strMatrix[0] = 0.0;
                strMatrix[2] = -1 / (h1 * h1);

                b[i] = (2 / tau) * UPrev[ix2][j] +
                       (1 / (h2 * h2)) * (UPrev[ix2 + 1][j] - 2 * UPrev[ix2][j] + UPrev[ix2 - 1][j])
                       + getFi(var, j, ix2) + y0 / (h1 * h1);
                matrix[i] = strMatrix;
                continue;
            }


            if (i == n - 1) { // для yN-1
                strMatrix[2] = 0.0;
                strMatrix[0] = -1 / (h1 * h1);
                b[i] = (2 / tau) * UPrev[ix2][j] +
                       (1 / (h2 * h2)) * (UPrev[ix2 + 1][j] - 2 * UPrev[ix2][j] + UPrev[ix2 - 1][j])
                       + getFi(var, j, ix2) + yN / (h1 * h1);
                matrix[i] = strMatrix;
                continue;
            }
            strMatrix[0] = -1 / (h1 * h1);
            strMatrix[2] = -1 / (h1 * h1);



            b[i] = (2 / tau) * UPrev[ix2][j] +
                   (1 / (h2 * h2)) * (UPrev[ix2 + 1][j] - 2 * UPrev[ix2][j] + UPrev[ix2 - 1][j])
                   + getFi(var, j, ix2);
            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }


    pair<vector<vector<double>>, vector<double>>
    FactoryDiagMatrixU2D2L1R1First(Var *var, int it, int ix2) {  // на левой и правой границе условия первого рода.
        //x1 - это второй индекс;x2-первыйю
        unsigned countDiag = 3;
        auto UPrev = var->U[it - 1];
        auto n = var->X1.size() - 2;// так как y0 и yN я знаю
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h1 = var->h1;
        auto h2 = var->h2;
        auto tau = var->tau;
//        cout<<"ix2 "<<ix2<<endl;
        auto y0 = getBoundValueLeft(var, ix2);
        auto yN = getBoundValueRight(var, ix2);
        for (int i = 0; i < n; i++) { //знаем y0 и yN; считаем только для y1...yN-1
            int j = i + 1;// индекс для X
            vector<double> strMatrix(countDiag);//строка матрицы
            strMatrix[1] = 2 * (1 / (h1 * h1) + 1 / tau);
            double lambdaX2 = 0;

            if (ix2 == var->X2.size() - 1) {
                lambdaX2 = (2 * UPrev[ix2 - 1][j] - 2 * UPrev[ix2][j] + 2 * h2 * getBoundValueDown(var, ix2));
            } else {
                if (ix2 == 0) {
                    lambdaX2 = (2 * UPrev[ix2 + 1][j] - 2 * UPrev[ix2][j] + 2 * h2 * getBoundValueUp(var, ix2));
                } else {
                    lambdaX2 = (UPrev[ix2 + 1][j] - 2 * UPrev[ix2][j] + UPrev[ix2 - 1][j]);
                }
            }
            b[i] = (2 / tau) * UPrev[ix2][j] +
                   (1 / (h2 * h2)) * lambdaX2
                   + getFi(var, j, ix2);

            if (i == 0) { // для y1
                strMatrix[0] = 0.0;
                strMatrix[2] = -1 / (h1 * h1);
                matrix[i] = strMatrix;
                b[i] += y0 / (h1 * h1);
                continue;
            }

            if (i == n - 1) { // для yN-1
                strMatrix[2] = 0.0;
                strMatrix[0] = -1 / (h1 * h1);
                b[i] += yN / (h1 * h1);
                matrix[i] = strMatrix;
                continue;


            }
            strMatrix[0] = -1 / (h1 * h1);
            strMatrix[2] = -1 / (h1 * h1);

            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }

    pair<vector<vector<double>>, vector<double>>
    FactoryDiagMatrixU1D1L2R2First(Var *var, int it, int ix2) {  // на левой и правой границе условия первого рода.
        //x1 - это второй индекс;x2-первыйю
        unsigned countDiag = 3;
        auto UPrev = var->U[it - 1];
        auto n = var->X1.size();
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        auto h1 = var->h1;
        auto h2 = var->h2;
        auto tau = var->tau;
//        cout<<"ix2 "<<ix2<<endl;
        for (int i = 0; i < n; i++) { //знаем y0 и yN; считаем только для y1...yN-1
            int j = i;// индекс для X
            vector<double> strMatrix(countDiag);//строка матрицы
            strMatrix[1] = 2 * (1 / (h1 * h1) + 1 / tau);


            if (i == 0) { // для y0
                strMatrix[0] = 0.0;
                strMatrix[2] = -2 / (h1 * h1); // 2 - из-за y_{-1}
                b[i] = (2 / tau) * UPrev[ix2][j] +
                       (1 / (h2 * h2)) * (UPrev[ix2 + 1][j] - 2 * UPrev[ix2][j] + UPrev[ix2 - 1][j])
                       + getFi(var, j, ix2) + 2 * getBoundValueLeft(var, i) / (h1);

                matrix[i] = strMatrix;
                continue;

            }

            if (i == n - 1) { // для yN
                strMatrix[2] = 0.0;
                strMatrix[0] = -2 / (h1 * h1); // 2 - из-за y_{n+1}
                b[i] = (2 / tau) * UPrev[ix2][j] +
                       (1 / (h2 * h2)) * (UPrev[ix2 + 1][j] - 2 * UPrev[ix2][j] + UPrev[ix2 - 1][j])
                       + getFi(var, j, ix2) + 2 * getBoundValueRight(var, i) / (h1);
                matrix[i] = strMatrix;
                continue;
            }
            strMatrix[0] = -1 / (h1 * h1);
            strMatrix[2] = -1 / (h1 * h1);
            b[i] = (2 / tau) * UPrev[ix2][j] +
                   (1 / (h2 * h2)) * (UPrev[ix2 + 1][j] - 2 * UPrev[ix2][j] + UPrev[ix2 - 1][j])
                   + getFi(var, j, ix2);
            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);

    }


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

    double getBoundValueLeft(Var *var, int ix1) override {
        return 1.0;
    }


    double getBoundValueRight(Var *var, int ix1) override {
        return 1.0;
    }

    double getBoundValueUp(Var *var, int ix2) override {
        return 1.0;
    }


    double getBoundValueDown(Var *var, int ix2) override {
        return 1.0;
    }

    double getBeginningValue(Var *var, int ix1, int ix2) override {
        return 0.0;
    }

    double getFi(Var *var, int ix1, int ix2) override {
        return 0;
    }
};


class Equations2 : public Equations {
public:
    int getKindLeft() override {
        return 1;
    }

    int getKindUp() override {
        return 2;
    }

    int getKindRight() override {
        return 1;
    }

    int getKindDown() override {
        return 2;
    } // вид граничных условий

private:

    double getBoundValueDown(Var *var, int ix1) override {
        return 1.0;
    }


    double getBoundValueUp(Var *var, int ix1) override {
        return -1.0;
    }

    double getBoundValueRight(Var *var, int ix2) override {
        return 1.0 + var->X2[ix2];

    }


    double getBoundValueLeft(Var *var, int ix2) override {
        return 1.0 + var->X2[ix2];
    }

    double getBeginningValue(Var *var, int ix1, int ix2) override {
        return 0.0;
    }

    double getFi(Var *var, int ix1, int ix2) override {
        return 0;
    }
};


class Equations3 : public Equations {
public:
    int getKindLeft() override {
        return 2;
    }

    int getKindUp() override {
        return 1;
    }

    int getKindRight() override {
        return 2;
    }

    int getKindDown() override {
        return 1;
    } // вид граничных условий

private:

    double getBoundValueDown(Var *var, int ix1) override {
        return 1.0 + var->X1[ix1] * var->X1[ix1];
    }


    double getBoundValueUp(Var *var, int ix1) override {
        return var->X1[ix1] * var->X1[ix1];
    }

    double getBoundValueRight(Var *var, int ix2) override {
        return 2.0;

    }


    double getBoundValueLeft(Var *var, int ix2) override {
        return 0.0;
    }

    double getBeginningValue(Var *var, int ix1, int ix2) override {
        return 0.0;
    }

    double getFi(Var *var, int ix1, int ix2) override {
        return -4.0;
    }
};


class Equations4 : public Equations {
public:
    int getKindLeft() override {
        return 1;
    }

    int getKindUp() override {
        return 2;
    }

    int getKindRight() override {
        return 1;
    }

    int getKindDown() override {
        return 2;
    } // вид граничных условий

private:

    double getBoundValueDown(Var *var, int ix1) override {
        return 2.0;
    }


    double getBoundValueUp(Var *var, int ix1) override {
        return 0.0;
    }

    double getBoundValueRight(Var *var, int ix2) override {
        return 1 + var->X2[ix2] * var->X2[ix2];

    }


    double getBoundValueLeft(Var *var, int ix2) override {
        return var->X2[ix2] * var->X2[ix2];
    }

    double getBeginningValue(Var *var, int ix1, int ix2) override {
        return 0.0;
    }

    double getFi(Var *var, int ix1, int ix2) override {
        return -4.0;
    }
};

class EquationsVar6 : public Equations {
public:
    int getKindLeft() override {
        return 1;
    }

    int getKindUp() override {
        return 2;
    }

    int getKindRight() override {
        return 1;
    }

    int getKindDown() override {
        return 2;
    } // вид граничных условий

private:

    double getBoundValueDown(Var *var, int ix1) override {
        return sqrt(var->X1[ix1] + 2);
    }


    double getBoundValueUp(Var *var, int ix1) override {
        return -sqrt(var->X1[ix1] + 1);
    }

    double getBoundValueRight(Var *var, int ix2) override {
        return 2.0 * pow(var->X2[ix2] + 2, 1.5) / 3.0;
    }


    double getBoundValueLeft(Var *var, int ix2) override {
        return 2.0 * pow(var->X2[ix2] + 1, 1.5) / 3.0;
    }

    double getBeginningValue(Var *var, int ix1, int ix2) override {
        return 1+var->X1[ix1]+var->X2[ix2];
    }

    double getFi(Var *var, int ix1, int ix2) override {
        return -1 / sqrt(var->X1[ix1] + var->X2[ix2] + 1);
    }
};


#endif //LAB9_EQUATIONS_H
