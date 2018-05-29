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
         n = static_cast<int>(2);//standart coef= 22(b-a)
    }

    void localization(double (*f)(double)){
        Grid* grid = new UniformGrid(a,b,n);
        auto values = grid->get(f);
        grid->print();
        for(int i=0;i<values.first.size()-1;i++){
            if(SolveEq::compareWithZero(f(values.first[i]))){
                this->roots.push_back(values.first[i]);
                continue;
            }

            if(SolveEq::compareWithZero(f(values.second[i]))){
                this->roots.push_back(values.second[i]);
                continue;
            }

            if(values.second[i]*values.second[i+1]<0){
                intervals.emplace(values.first[i],values.first[i+1]);
            }
        }
        delete grid;// возможно не тут надо удалять.
    }
public:
    Equation() = default;

    enum Method { Newton, Bisection};
    static vector<double> execute(double a, double b, Method method,double (*f)(double),bool flagLocalize=true){
        if (!flagLocalize){
            auto * instance = new Equation(a,b);
            instance->roots.push_back((new SolveBisection(a, b))->execute(f));
            auto res= instance->roots;
            delete instance;
            return res;
        }

        auto * instance = new Equation(a,b);
        instance->localization(f);
        while(!instance->intervals.empty()) {
            double x1,x2;
            tie(x1,x2)= instance->intervals.front();
            instance->intervals.pop();
            if (method == Bisection){
                auto solveBisection=new SolveBisection(x1,x2);
                instance->roots.push_back(solveBisection->execute(f));
                delete solveBisection;
                continue;
            }
            if (method == Newton){
                auto solveNewton = new SolveNewton(x1,x2);
                instance->roots.push_back(solveNewton->execute(f));
                delete solveNewton;
                continue;
            }
            assert(false);
        }
        auto res= instance->roots;
        delete instance;
        return res;
    }

};


#endif //LAB5_SOLVEEQUATION_H
