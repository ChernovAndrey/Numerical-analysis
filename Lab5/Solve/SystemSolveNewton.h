
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
    const double eps =1e-6;
    double a1;
    double b1;
    double a2;
    double b2;;

public:
    SystemSolveNewton(double a1, double b1, double a2, double b2): a1(a1), b1(b1), a2(a2), b2(b2){}

    vector<double> execute() {

        vector<double> X1 = {a1, b1};
        vector<double> X2 = {a2, b2};

        vector<double> Xk = {(a1 + b1) / 2, (a2 + b2) / 2};
        vector<double> prXk =Xk;//not used this value
        vector<double> pr2Xk = X2;//not used this value

        bool flagFirst = false;
        int countIter =0;
        while (((getResidual(prXk,Xk)>=eps) || !flagFirst)){
            if(countIter>0) pr2Xk = Xk;
            prXk=Xk;
            Xk = diffVectors( Xk,multiMatrixVector( InverseJacobi(Xk[0],Xk[1]), Fxy(Xk[0], Xk[1]) ) );

            if(!((Xk[0]>=a1)&&(Xk[0]<=b1))){
                Xk={(prXk[0]+pr2Xk[0])/2,Xk[1]};
            }

            if(!((Xk[1]>=a2)&&(Xk[1]<=b2))){
                Xk={Xk[0],(prXk[1]+pr2Xk[1])/2};
            }

            flagFirst=true;
            printVector(Xk);
            countIter++;
        }
        cout<<"Count Iterations="<<countIter<<endl;
        return Xk;
    }
};


#endif //LAB5_SYSTEMSOLVENEWTON_H
