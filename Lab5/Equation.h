//
// Created by andrey on 11.12.17.
//

#ifndef LAB5_SOLVEEQUATION_H
#define LAB5_SOLVEEQUATION_H
#include<iostream>
#include<vector>
#include <queue>
#include "Grids/Grid.h"
#include "Grids/UniformGrid.h"
#include "Solve/SolveEq.h"
#include "Solve/SolveBisection.h"
#include "Solve/SolveNewton.h"

using namespace std;

class Equation {

private:
 //   SolveEq* solveEq= nullptr;
    vector<double> roots;
    double a{};
    double b{};
    int n{};
    queue<pair<double,double>> intervals;//интервалы локализации корня
    Equation(double a,double b):a(a),b(b){
         n = static_cast<int>(22*(b-a));//standart coef= 22(b-a)
    }

    void localization(){
        Grid* grid = new UniformGrid(a,b,n);
        auto values = grid->get();
        grid->print();
        for(int i=0;i<values.first.size()-1;i++){
            if(values.second[i]*values.second[i+1]<0){
                intervals.emplace(values.first[i],values.first[i+1]);
            }
        }
    }
public:
    Equation() = default;

    enum Method { Newton, Bisection};
    static vector<double> execute(double a, double b, Method method){
        auto * instance = new Equation(a,b);
        instance->localization();
        while(!instance->intervals.empty()) {
            double x1,x2;
            tie(x1,x2)= instance->intervals.front();
            instance->intervals.pop();
            if (method == Bisection){
                instance->roots.push_back((new SolveBisection(x1, x2))->execute());
                continue;
            }
            if (method == Newton){
                instance->roots.push_back((new SolveNewton(x1, x2))->execute());
                continue;
            }
            assert(false);
        }
        return instance->roots;
    }

};


#endif //LAB5_SOLVEEQUATION_H
