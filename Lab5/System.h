//
// Created by andrey on 12.12.17.
//

#ifndef LAB5_SYSTEM_H
#define LAB5_SYSTEM_H

#include <queue>
#include "iostream"
#include "vector"
#include "Solve/SystemSolveNewton.h"

using namespace std;
class System {
public:

    static vector<double> execute(double a1, double b1, double a2, double b2){
     //auto* instance = new System(a1,b1,a2,b2);
       return (new SystemSolveNewton(a1,b1,a2,b2))->execute();
    }

private:
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
