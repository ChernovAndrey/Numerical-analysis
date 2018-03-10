#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include "SolveMethod.h"
#include "Euler/ExplicitEuler.h"
#include "tests.h"
#include "Euler/ImplicitEuler.h"
#include "RK4.h"
#include "Adams4.h"
#include "PredCor.h"

using namespace std;




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

void execute(SolveMethod* method, vector<double>(*F)(vector<double>)){
    auto U = method->solve(F, initVariables(),N);
    writingData(U);
    delete method;
}


int main(){
    //Euler(,{1,0});
    execute(new PredCor(),F);
    return 0;
}
