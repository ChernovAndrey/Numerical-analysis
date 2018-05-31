#include <iostream>
#include "Solve.h"
#include "helping/vectorOperations.h"
#include <vector>
using namespace std;



void writingFile(vector<double> U, vector<double> X){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab10/files/U2.txt";
    ofstream file(pathToFile, ios_base::out | ios_base::app);

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

int main() {

//    double h=0.11;
//    double h=0.075;
    double a = 0.0;
    double b = 1.0;

    int nx = 22;
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
