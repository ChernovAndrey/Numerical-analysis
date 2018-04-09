#include <iostream>
#include "Solve.h"
#include <vector>
using namespace std;



void writingData(vector<double> v, string s){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab7/files/Ui"+s+".txt";
    ofstream file(pathToFile, ios_base::out | ios_base::trunc);
    for(int i=0;i<v.size();i++){
        file<< v[i]<<" ";
        file<<endl;
    }
    file.close();
}

int main() {

    double h=0.2;
    double tau=0.002;  //0.062e-1 -граница сх-ти явного метода  для Ex1
    double x0=0;
    double xf=1;
    double t0=0.0;
    double tf=1.5;

    Solve* solve = new Solve(h,tau,x0,xf,t0,tf);
    auto U = solve->calculateExplicit();
    printMatrix(U);
    cout<<"size="<<U.size()<<'\t'<<U[0].size()<<endl;
//    writingData(U[0],"1");
//    writingData(U[50],"2");
//    writingData(U[100],"3");
//    writingData(U[200],"4");
    printVector(U[0]);
    printVector(U[1]);
    delete solve;
    return 0;
}
