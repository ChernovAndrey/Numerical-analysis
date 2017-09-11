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

#include "generalMethods.cpp"
#endif //LAB1_GENERALMEHODS_H
