//
// Created by andrey on 12.12.17.
//

#ifndef LAB5_SYSTEM_H
#define LAB5_SYSTEM_H

#include <queue>
#include "iostream"
#include "vector"
#include "Solve/SystemSolveNewton.h"
#include <iomanip>
#include <fstream>


using namespace std;
class System {
public:

    static vector<double> execute(double a1, double b1, double a2, double b2){
     //auto* instance = new System(a1,b1,a2,b2);
        plots(a1,b1,a2,b2);
      //  return (new SystemSolveNewton(a1,b1,a2,b2))->execute();
    }

private:

    static void plots(double a1, double b1, double a2, double b2) {
        const string fileNameX = "/home/andrey/CLionProjects/NumericalMethods/Lab5/files/X.txt";
        const string  fileNameY = "/home/andrey/CLionProjects/NumericalMethods/Lab5/files/Y.txt";
        const  string fileNameVal = "/home/andrey/CLionProjects/NumericalMethods/Lab5/files/Val.txt";
        double h =0.5;
        ofstream fileX(fileNameX, ios_base::out | ios_base::trunc);
        ofstream fileY(fileNameY, ios_base::out | ios_base::trunc);
        ofstream fileVal(fileNameVal, ios_base::out | ios_base::trunc);
        if (fileX.is_open()) {
            for(double i=a1;i<=b1;i=i+h){
                for(double j=a2;j<=b2;j=j+h){
                    fileVal<<i<<endl;
                    fileVal<< j<<endl;

                    vector<double> X0(2);
                    X0[0]=i;
                    X0[1]=j;
                    auto *instance = new SystemSolveNewton(X0);
                    instance->execute();
                    fileVal<<instance->getCountIter()<<endl;

                }
            }
        }
    }
    vector<double> roots;
    double a1{};
    double a2{};
    double b1{};
    double b2{};
    //int n{};
    queue<pair<double,double>> intervals;//интервалы локализации корня
    System(double a1,double b1,double a2, double b2):a1(a1),b1(b1),a2(a2),b2(b2){
      //  n = static_cast<int>(22*(b1-a1));//standart coef= 22(b-a)
    }


};


#endif //LAB5_SYSTEM_H
