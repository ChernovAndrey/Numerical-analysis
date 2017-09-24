//
// Created by andrey on 21.09.17.
//

#ifndef LAB2_SIMPLEITERATION_H
#define LAB2_SIMPLEITERATION_H

#include <iostream>
#include "IterativeMethods.hpp"

using namespace std;

template <typename T>
class SimpleIteration : public IterativeMethods<T>{
public:
    SimpleIteration(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b) :
            IterativeMethods<T>(eps,x,A,b){};

private:
    void convertToIterativeMatrix(){ //C в уравнении x=C*x + b
        printMatrix(this->A);
        this->A=EMinusMatrix(this->A);
        printMatrix(this->A);
    }

public:
    /*static vector<T> solveSystem(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b){
        IterativeMethods<T>* instance = new SimpleIteration(eps,x,A,b);
        auto result = IterativeMethods<T>::solveSystem(instance);

        delete instance;
        return result;
    }*/


};


#endif //LAB2_SIMPLEITERATION_H
