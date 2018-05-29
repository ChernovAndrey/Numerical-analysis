#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include "SolveMethod.h"
#include "Euler/ExplicitEuler.h"
#include "tests.h"
#include "Euler/ImplicitEuler.h"
#include "RK.h"
#include "Adams4.h"
#include "PredCor.h"
#include "SymScheme.h"

using namespace std;


void compareWithAnswerEx1(SolveMethod* method, vector<double>(*F)(vector<double>, double)){ //вычисление погрешности для шарика с пружинкой; норма C
    double t =T0;
    double tau = TAU;
    double tf = Tf;

    auto U = method->solve(F, initVariables(),T0,Tf);
    auto x = U[0];//x=u1
    vector<double> accurX(x.size()); //точное значение

    accurX[0]=getAnswerEx1(0);
    for(int i=1;t<=tf;i++){
        accurX[i]=getAnswerEx1(t);
        t+=tau;
    }
  //  printVector(accurX);
   // printVector(x);
    cout<< "Residual="<<normC(accurX,x);
}


void writingData(vector<vector<double>> U){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab6/files/U.txt";
    ofstream file(pathToFile, ios_base::out | ios_base::trunc);
    for(int i=0;i<U[0].size();i++){
        for (auto &var : U) {//local variables
            file<< var[i]<<" ";
        }
        file<<endl;
    }
    file.close();
}

void execute(SolveMethod* method, vector<double>(*F)(vector<double>, double)){
    auto U = method->solve(F, initVariables(),T0,Tf);
    writingData(U);
}


int main(){

    auto method = new RK(false,4);
    execute(method,Func);
    compareWithAnswerEx1(method,Func); // только для маятника с пружинкой; не работает для автомат шага
    delete method;
    return 0;
}
