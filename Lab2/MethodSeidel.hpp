//
// Created by andrey on 01.10.17.
//

#ifndef LAB2_METHODSEIDEL_H
#define LAB2_METHODSEIDEL_H


#include <iostream>
#include "MethodRelaxation.hpp"
using namespace std;

template <typename T>
class MethodSeidel : public MethodRelaxation<T> {

public:
    MethodSeidel(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b) :
            MethodRelaxation<T>(eps, x, A, b,1.0){};//w=1.0
};
#endif //LAB2_METHODSEIDEL_H
