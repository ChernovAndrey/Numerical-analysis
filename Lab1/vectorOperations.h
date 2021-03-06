//
// Created by andrey on 24.09.17.
//

#ifndef LAB1WITHOOP_VECTOROPERATIONS_H
#define LAB1WITHOOP_VECTOROPERATIONS_H
template <typename T>
T getResidual(vector<T> a,vector<T> b);

template <typename T>
vector<T> multiMatrixVector(vector<vector<T>> m, vector<T> v);

template <typename T>
T normVector(vector<T> v);

template <typename T>
void printVector(vector<T> v);
#include "vectorOperations.cpp"
#endif //LAB1WITHOOP_VECTOROPERATIONS_H
