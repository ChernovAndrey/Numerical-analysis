
// Created by andrey on 12.12.17.
//

#ifndef LAB5_SYSTEMSOLVENEWTON_H
#define LAB5_SYSTEMSOLVENEWTON_H

#include <utility>

#include "iostream"
#include "vector"
#include "../vectorOperations.h"
#include "../matrixOperations.h"
using namespace std;
class SystemSolveNewton {
private:
    const double eps =1e-3;
    double a1;
    double b1;
    double a2;
    double b2;
    double countIter=0;
    vector<double>(*F)(vector<double>);
    bool flagX0 = false;//задано начальное прибл
    vector<double> X0;
public:
    double getCountIter(){
        return countIter;
    }
    SystemSolveNewton(double a1, double b1, double a2, double b2): a1(a1), b1(b1), a2(a2), b2(b2){}

    SystemSolveNewton(vector<double> X0,vector<double>(*Func)(vector<double>)):X0(std::move(X0)),flagX0(true),F(Func){}

    vector<double> execute() {
        vector<double> Xk;
        if (!flagX0) Xk = {(a1 + b1) / 2, (a2 + b2) / 2};
        else Xk=X0;
        cout<<"X0:"<<endl;
        printVector(X0);
        vector<double> prXk = Xk;//not used this value
        vector<double> pr2Xk = {0,0};//not used this value

        bool flagFirst = false;
        int countIter =0;
        while (((getResidual(prXk,Xk)>=eps) || !flagFirst)){
            if(countIter>0) pr2Xk = Xk;
            prXk=Xk;
            auto invJacobi = InverseJacobi(Xk[0],Xk[1]);
            if(invJacobi.empty()){
                countIter=10000;
                break;
            }
            Xk = diffVectors( Xk,multiMatrixVector(invJacobi, Fxy(Xk[0], Xk[1]) ) );

            flagFirst=true;
            countIter++;
            if(countIter>=30) {
                countIter=10000;
                break;
            }
        }
        this->countIter=countIter;
        cout<<"Count Iterations="<<countIter<<endl;
        printVector(Xk);
        return Xk;
    }

    const double eps0 =1e-6;

    vector<double> Fxy(vector<double> variables){
        return F(variables);
    }

    vector<double> Fxy(double x1, double x2){       //убрать
        return  F({x1,x2});
    }
//
//    vector<vector<double>> numericallyJacobi(const vector<double> &variables){
//        int n = static_cast<int>(variables.size());
//        for(int i=0;i<variables.size();i++){
//
//        }
//    }
    vector<vector<double>> numericallyJacobi(double x1, double x2){

        vector<double> dx1 = diffVectors(Fxy(x1+eps0,x2),Fxy(x1,x2));
        vector<double> dx2 = diffVectors(Fxy(x1,x2+eps0),Fxy(x1,x2));
        return{
                {dx1[0]/eps0,dx2[0]/eps0},
                {dx1[1]/eps0,dx2[1]/eps0}
        };
    }


    vector<vector<double>> Jacobi(double x1, double x2){
        return numericallyJacobi(x1,x2);
    }

    double Det(vector<vector<double>> m){
        return m[1][1]*m[0][0]- m[1][0]*m[0][1];
    }

    vector<vector<double>> InverseJacobi(double x1, double x2){
        auto jacobi = Jacobi(x1,x2);
        auto det = Det(jacobi);
        if(compareWithZero(det)){
            return {};
        }
        return {
                {jacobi[1][1]/det,-jacobi[0][1]/det},
                {-jacobi[1][0]/det, jacobi[0][0]/det}
        };
    }

    static bool compareWithZero(double x){
        return abs(x)<1e-6;
    }
};


#endif //LAB5_SYSTEMSOLVENEWTON_H
