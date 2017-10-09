//
// Created by andrey on 21.09.17.
//

#include <iostream>
#include <vector>
using namespace std;

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


//E-A
template<typename T>
vector<vector<T>> EMinusMatrix(vector<vector<T>> A){
    for(int i=0;i<A.size();i++){
        for (int j = 0; j < A[0].size(); ++j) {
            if(i==j) A[i][i]= 1.0 - A[i][i];
            else A[i][j] = -A[i][j];
        }
    }
    return A;
}

template <typename T>
static vector<T> multiMatrixVector(vector<vector<T>> m, vector<T> v){
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
static vector<vector <T>> matrixMultiplication(vector<vector<T>> a, vector<vector<T>> b){
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

template <typename T>
static vector<vector <T>> transposeMatrix(vector<vector <T>> matrix){
    vector<vector<T>> newMatrix(matrix[matrix.size()-1].size(),vector<T>(matrix.size(),0.0));
    for(int i=0;i<matrix.size(); i++) {
        vector<T> help(matrix.size());
        for (int j = 0; j < matrix[i].size(); ++j) {
            newMatrix[j][i]=matrix[i][j];
        }
    }
    return newMatrix;
}

//достаем последний столбец из матрицы
template <typename T>
static vector<T> getVectorB(vector<vector<T>> matrix){
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
