//
// Created by andrey on 01.10.17.
//

#ifndef LAB2_DIAGMETHODSEIDEL_H
#define LAB2_DIAGMETHODSEIDEL_H


#include <iostream>
#include "DiagMethodRelaxation.hpp"
using namespace std;

template <typename T>
class DiagMethodSeidel : public DiagMethodRelaxation<T> {

public:
    DiagMethodSeidel(T eps, const vector<T> &x, const vector<vector<T>> &A, const vector<T> &b) :
            DiagMethodRelaxation<T>(eps, x, A, b,1.0){};//w=1.0
};
#endif //LAB2_DIAGMETHODSEIDEL_H
