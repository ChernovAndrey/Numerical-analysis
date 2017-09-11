//
// Created by andrey on 10.09.17.
//

#ifndef LAB1_GENERALMEHODS_H
#define LAB1_GENERALMEHODS_H

#include "vector"

template <typename T>
vector<T> Reverse(vector<vector<T>> matrix);

template <typename T>
int findMaxStr(int nColumn,int nBeginStr, vector<vector<T>> matrix);

template <typename T>
vector<vector<T>> swapStrMatrix(int nStr1,int nStr2,vector<vector<T>> matrix);

template <typename T>
T getResidual(vector<T> a, vector<T> b);

template <typename  T>
vector<T> multiMatrixVector(vector<vector<T>> m, vector<T> v);

template <typename T>
vector<vector <T>> matrixMultiplication(vector<vector<T>> a, vector<vector<T>> b);

//из матрицы вытаскивается последний столбец
template <typename T>
vector<T> getVectorB(vector<vector<T>> matrix);

//на вход подается расширенная матрица и просто отбрасывается последний столбец
template <typename T>
vector<vector<T>> excludeVectorB(vector<vector<T>> matrix);
#include "generalMethods.cpp"
#endif //LAB1_GENERALMEHODS_H
