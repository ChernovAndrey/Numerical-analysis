
// Created by andrey on 12.12.17.
//

#ifndef LAB5_SYSTEMSOLVENEWTON_H
#define LAB5_SYSTEMSOLVENEWTON_H

#include "iostream"
#include "vector"
#include "../vectorOperations.h"
#include "../matrixOperations.h"
#include "../tests/Fxy.h"
using namespace std;
class SystemSolveNewton {
    const double eps =1e-3;
    double a1;
    double b1;
    double a2;
    double b2;
    double countIter=0;
    bool flagX0 = false;//задано начальное прибл
    vector<double> X0;
public:
    double getCountIter(){
        return countIter;
    }
    SystemSolveNewton(double a1, double b1, double a2, double b2): a1(a1), b1(b1), a2(a2), b2(b2){}

    SystemSolveNewton(vector<double> X0):X0(X0),flagX0(true){}

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

//            if(!((Xk[0]>=a1)&&(Xk[0]<=b1))){
//                Xk={(prXk[0]+pr2Xk[0])/2,Xk[1]};
//            }
//
//            if(!((Xk[1]>=a2)&&(Xk[1]<=b2))){
//                Xk={Xk[0],(prXk[1]+pr2Xk[1])/2};
//            }

            flagFirst=true;
          //  printVector(Xk);
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
};


#endif //LAB5_SYSTEMSOLVENEWTON_H
