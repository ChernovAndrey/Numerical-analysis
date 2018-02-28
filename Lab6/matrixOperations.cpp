//
// Created by andrey on 24.09.17.
//
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;

template<typename T>
T getNormMatrix1(const vector<vector<T>> &matrix){ //по столбцам
    T norm;
    bool flagInit = false;
    for(int j=0; j<matrix[0].size();j++){
        T max = 0.0;
        for (auto &el : matrix) {
            max+=abs(el[j]);
        }
        if(!flagInit) {
            norm = max;
            flagInit =true;
        }else {
            if (norm < max) norm = max;
        }
    }
    return norm;
}

template<typename T>
T getNormMatrix3(const vector<vector<T>> &matrix){ // по строкам
    T norm ;
    bool flagInit = false;
    for (auto str : matrix) {
        T max = 0.0;
        for (auto el : str) {
            max+=abs(el);
        }
        if(!flagInit) {
            norm = max;
            flagInit =true;
        }else {
            if (norm < max) norm = max;
        }
    }
    return norm;
}


template <typename T>
void printMatrix(vector<vector<T>> m) {
    for (auto &str : m) {
        for (T el : str) {
            cout << el << "    ";
        }
        cout << endl;
    }
    cout << endl;
}


//достаем последний столбец из матрицы
template<typename T>
vector<T> getVectorB(vector<vector<T>> matrix){
    vector<T> result;
    for(int i=0;i< matrix.size();i++){
        result.push_back(matrix[i][matrix[i].size()-1]);
    }
    return result;
}

//на вход подается расширенная матрица и просто отбрасывается последний столбец
template <typename T>
vector<vector<T>> getMatrixA(vector<vector<T>> matrix){
    vector<vector<T>> newMatrix(matrix.size());
    for(int i=0;i<matrix.size();i++){
        vector<T> help(matrix[i].size()-1);
        for (int j = 0; j < matrix[i].size()-1; j++){
            help[j]=matrix[i][j];
        }
        newMatrix[i]=help;
    }
    return newMatrix;
}


template <typename T>
void shiftMatrix(vector<vector<T>> &matrix,T c) {//Matix- c*E
    for(int i=0;i<matrix.size();i++){
        matrix[i][i]-=c;
    }
}

template <typename T>
void backShiftMatrix(vector<vector<T>> &matrix,T c) {//Matix+ c*E
    for(int i=0;i<matrix.size();i++){
        matrix[i][i]+=c;
    }
}




