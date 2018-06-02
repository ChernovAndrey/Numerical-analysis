#include <iostream>
#include "Solve.h"
#include "MethodSingular.h"
#include "helping/vectorOperations.h"
#include "SolveSingular.h"
#include <vector>
using namespace std;



void writingFile(vector<double> U, vector<double> X){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab10/files/U2.txt";
    ofstream file(pathToFile, ios_base::out | ios_base::trunc);

        for (int i = 0; i < X.size(); ++i) {
            file<< X[i] <<" " << U[i] <<" ";
        }

    file.close();

}

vector<double> getAccuracy1(vector<double> X){
    vector<double> U(X.size());
    for (int i = 0; i < X.size(); ++i) {
        U[i] = 1.0;
    }
    return U;
}

void solveSingularEq(){
    int n = 40; // кол-во точек
    auto *solve = new SolveSingular(n);
    auto U = solve->calculate();
    double R = U.back(); // невязка.
    U.pop_back();
    printVector(U);
    cout<<"R="<<R<<endl;
    vector<double> X(n);
    for (int i = 0; i < X.size(); ++i) {
        X[i] = 2*M_PI*i/n;
    }
    writingFile(U,X);
    delete solve;
}


int main() {
    solveSingularEq();
    return 0;
//    double h=0.11;
//    double h=0.075;

    double a = 0.0;
    double b = 1.0;

    int nx = 7;
    double h = (b-a)/(nx-1);
    double as=a;
    double bs=b;
    double hs=h;
    int ns = nx;

//    auto *solve = new Solve(h,a,b,hs,as,bs);
    auto *solve = new Solve(h,a,nx,hs,as,ns);
    auto U = solve->calculate();
    printVector(U);
    cout<<"error="<<normVectorC( diffVectors( U,getAccuracy1(solve->var->X) ) );
    writingFile(U,solve->var->X);
    delete solve;
    return 0;
}
