//
// Created by andrey on 24.09.17.
//

#ifndef LAB1WITHOOP_MATRIXOPERATIONS_H
#define LAB1WITHOOP_MATRIXOPERATIONS_H
#include <vector>

using namespace std;

template<typename T>
T getNormMatrix1(const vector<vector<T>> &matrix);

template<typename T>
T getNormMatrix3(const vector<vector<T>> &matrix);

//достаем последний столбец из матрицы
template<typename T>
vector<T> getVectorB(vector<vector<T>> matrix);

//на вход подается расширенная матрица и просто отбрасывается последний столбец
template <typename T>
vector<vector<T>> getMatrixA(vector<vector<T>> matrix);


template <typename T>
void shiftMatrix(vector<vector<T>> &matrix,T c);
template <typename T>

void backShiftMatrix(vector<vector<T>> &matrix,T c);


template <typename T>
void printMatrix(vector<vector<T>> m);


#include "matrixOperations.cpp"
#endif //LAB1WITHOOP_MATRIXOPERATIONS_H
