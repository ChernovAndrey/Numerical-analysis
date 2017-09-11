//
// Created by andrey on 10.09.17.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "cassert"
using namespace std;

//обратный ход
template <typename T>
vector<T> Reverse(vector<vector<T>> matrix){
    const T E = 1e-14;
    vector<T> result(matrix.size());
    for(int i = static_cast<int>(matrix.size() - 1); i >= 0; i--){
        double s =0.0;
        for(auto j=i+1;j<matrix.size();j++){
            s= s - matrix[i][j]*result[j];
        }
        if(abs(matrix[i][i])< E) return {};
        result[i] =(s + matrix[i][matrix[i].size()-1])/matrix[i][i]; // прибавляем: поледний столбец, i-ая строка
    }
    return result;
}

//поиск максимального элемента в столбце nColumn, начиная со строки nBeginStr
template <typename T>
int findMaxStr(int nColumn,int nBeginStr, vector<vector<T>> matrix){
    const T E = 1e-14;
    if (nBeginStr+1 >= matrix.size()){  //проверка на выход за пределы
        return nBeginStr;
    }
    int nMax=nBeginStr;
    T max = matrix[nBeginStr][nColumn];
    for(int i = nBeginStr+1; i< matrix.size(); i++){
        if (matrix[i][nColumn] - max > E){
            max = matrix[i][nColumn];
            nMax = i;
        }
    }
    return nMax;
}

template <typename T>
vector<vector<T>> swapStrMatrix(int nStr1,int nStr2,vector<vector<T>> matrix) {
    if (nStr1 == nStr2) return matrix;
    vector<T> swapHelp(matrix[nStr1]);
    matrix[nStr1] = matrix[nStr2];
    matrix[nStr2] = swapHelp;
    return matrix;
}


template <typename T>
T getResidual(vector<T> a, vector<T> b){
    T norm;
    if (a.size()!=b.size()) assert(false);
    for(int i=0;i<a.size();i++){
        norm+=(a[i]-b[i])*(a[i]-b[i]);
    }
    return sqrt(norm);
}

template <typename  T>
vector<T> multiMatrixVector(vector<vector<T>> m, vector<T> v){
    vector<T> result(v.size());
    for(int i=0;i < m.size(); i++){
        result[i]=0;
        for (int j = 0; j < v.size(); j++) {
            result[i] += m[i][j]*v[j];
        }
    }
    return result;
}
template <typename T>
vector<vector <T>> matrixMultiplication(vector<vector<T>> a, vector<vector<T>> b){
    vector<vector<T>> multi(a.size(),vector<T>(a[a.size()-1].size(),0.0));
    auto f = b[0].size();
    for(int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b[i].size(); ++j) {
            for (int k = 0; k < a[i].size(); ++k) {
                multi[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return multi;
}


//из матрицы вытаскивается последний столбец
template <typename T>
vector<T> getVectorB(vector<vector<T>> matrix){
    vector<T> result;
    for(int i=0;i< matrix.size();i++){
        result.push_back(matrix[i][matrix[i].size()-1]);
    }
    return result;
}

//на вход подается расширенная матрица и просто отбрасывается последний столбец
template <typename T>
vector<vector<T>> excludeVectorB(vector<vector<T>> matrix){
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
