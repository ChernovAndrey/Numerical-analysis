//
// Created by andrey on 06.09.17.
//
#include<vector>
#ifndef LAB1_GAUSS_H_H
#define LAB1_GAUSS_H_H

template <typename T>
std::vector<T> methodGauss(std::vector<std::vector<T>> matrix);

template<typename T>
std::vector<std::vector<T>> getInvertibleMatrix(std::vector<std::vector<T>> matrix);

#include "gauss.cpp"
#include "invertibleMatrixGauss.cpp"
#endif //LAB1_GAUSS_H_H
