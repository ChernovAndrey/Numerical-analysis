//
// Created by andrey on 21.09.17.
//

#ifndef LAB2_MATRIXOPERATIONS_H
#define LAB2_MATRIXOPERATIONS_H

#include <iostream>
#include <vector>
using namespace std;

template<typename T>
T getNormMatrix3(const vector<vector<T>> &matrix);

template<typename T>
vector<vector<T>> EMinusMatrix(vector<vector<T>> A);

template <typename T>
static vector<T> multiMatrixVector(vector<vector<T>> m, vector<T> v);

template <typename T>
static vector<vector <T>> matrixMultiplication(vector<vector<T>> a, vector<vector<T>> b);

template <typename T>
static vector<vector <T>> transposeMatrix(vector<vector <T>> matrix);

//достаем последний столбец из матрицы
template <typename T>
static vector<T> getVectorB(vector<vector<T>> matrix);

//на вход подается расширенная матрица и просто отбрасывается последний столбец
template <typename T>
vector<vector<T>> getMatrixA(vector<vector<T>> matrix);

template<typename T>
T getNormMatrix1(const vector<vector<T>> &matrix);

#include "matrixOperations.cpp"

#endif //LAB2_MATRIXOPERATIONS_H
