#include "iostream"
#include "vector"
using namespace std;

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

vector<vector<double>> Jacobi(double x1, double x2){
    return Jacobi2(x1,x2);
}

double Det(vector<vector<double>> m){
    return m[1][1]*m[0][0]- m[1][0]*m[0][1];
}

vector<vector<double>> InverseJacobi(double x1, double x2){
    auto jacobi = Jacobi(x1,x2);
    auto det = Det(jacobi);
    return {
            {jacobi[1][1]/det,-jacobi[0][1]/det},
            {-jacobi[1][0]/det, jacobi[0][0]/det}
    };
}