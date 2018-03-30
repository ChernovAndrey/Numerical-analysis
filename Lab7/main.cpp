#include <iostream>
#include "Solve.h"
#include <vector>
using namespace std;

void writeInFile(vector<double> x){

}


void writingData(vector<double> v){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab7/files/Ui.txt";
    ofstream file(pathToFile, ios_base::out | ios_base::trunc);
    for(int i=0;i<v.size();i++){
        file<< v[i]<<" ";
        file<<endl;
    }
    file.close();
}

int main() {

    double h=0.2;
    double tau=0.2e-4;
    double x0=0;
    double xf=1;
    double t0=0.0;
    double tf=0.7;

    auto solve = new Solve(h,tau,x0,xf,t0,tf);
    auto U = solve->calculateExplicit();
    printMatrix(U);
    cout<<"size="<<U.size()<<'\t'<<U[0].size()<<endl;
    writingData(U[10000]);
    printVector(U[100]);
    delete solve;
    return 0;
}
