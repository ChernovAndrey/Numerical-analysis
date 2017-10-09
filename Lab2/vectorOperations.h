//
// Created by andrey on 21.09.17.
//

#ifndef LAB2_VECTOROPERATIONS_H
#define LAB2_VECTOROPERATIONS_H
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
vector<T> sumVector(vector<T> a, vector<T> b);

template <typename T>
vector<T> diffVectors(vector<T> a, vector<T> b);

template <typename T>
T normVector(vector<T> v);

template <typename T>
T getResidual(vector<T> a,vector<T> b);

#include "vectorOperations.cpp"
#endif //LAB2_VECTOROPERATIONS_H
