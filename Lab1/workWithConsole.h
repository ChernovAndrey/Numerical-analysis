//
// Created by andrey on 06.09.17.
//
#ifndef LAB1_WORLWITHCONSOLE_H
#define LAB1_WORLWITHCONSOLE_H
#include<iostream>
#include <vector>
using namespace std;

template<typename T>
void printVector(std::vector<T> v);

template<typename T>
void printMatrix(std::vector<std::vector<T>> m);



//std::vector<std::vector<double>> InputMatrix();

#include "workWithConsole.cpp"

#endif //LAB1_WORLWITHCONSOLE_H

