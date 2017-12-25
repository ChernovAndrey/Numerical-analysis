#ifndef LAB5_Fxy_H
#define LAB5_Fxy_H


#include "iostream"
#include "vector"
#include "../vectorOperations.h"

using namespace std;

const double eps0 =1e-6;
vector<double> Fxy1(double x1, double x2){
    return {
            x1*x1 - x2*x2  -15,
            x1*x2 + 4
    };
}

vector<vector<double>> Jacobi1(double x1, double x2){
    return {
            {2*x1,-2*x2},
            {x2,x1}
    };
}



vector<double> Fxy2(double x1, double x2){
    return {
            x1*x1 + x2*x2 +x1 +x2  -8,
            x1*x1+x2*x2 + x1*x2- 7
    };
}

vector<vector<double>> Jacobi2(double x1, double x2){
    return {
            {2*x1+1,2*x2+1},
            {2*x1+x2,2*x2+x1}
    };
}

vector<double> Fxy(double x1, double x2){
    return Fxy2(x1,x2);
}

vector<vector<double>> analyticallJacobi(double x1, double x2){
    return Jacobi2(x1,x2);
}


vector<vector<double>> numericallyJacobi(double x1, double x2){
    vector<double> dx1 = diffVectors(Fxy(x1+eps0,x2),Fxy(x1,x2));
    vector<double> dx2 = diffVectors(Fxy(x1,x2+eps0),Fxy(x1,x2));
    return{
            {dx1[0]/eps0,dx2[0]/eps0},
            {dx1[1]/eps0,dx2[1]/eps0}
    };
}


vector<vector<double>> Jacobi(double x1, double x2){
    return analyticallJacobi(x1,x2);
}

double Det(vector<vector<double>> m){
    return m[1][1]*m[0][0]- m[1][0]*m[0][1];
}

vector<vector<double>> InverseJacobi(double x1, double x2){
    auto jacobi = Jacobi(x1,x2);
    auto det = Det(jacobi);
    if(SolveBisection::compareWithZero(det)){
        return {};
    }
    return {
            {jacobi[1][1]/det,-jacobi[0][1]/det},
            {-jacobi[1][0]/det, jacobi[0][0]/det}
    };
}
#endif //LAB5_Fxy_H