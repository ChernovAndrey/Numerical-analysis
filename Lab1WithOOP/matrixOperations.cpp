//
// Created by andrey on 24.09.17.
//

#include <vector>
#include "Gauss.hpp"
#include "QR.hpp"
using namespace std;
template<typename T>
vector<vector<T>>getInvertibleMatrix(vector<vector<T>> matrix){
    vector<vector<T>> inverseMatrix(matrix.size());
    vector<T> help(matrix[0].size());
    for (int i = 0; i < matrix.size(); i++){
        vector<T> e(matrix.size(),0.0);
        e[i]=1.0;
        inverseMatrix[i] = QR<T>::solveSystem(matrix,e);
    }
    return BasicInterface<T>::transposeMatrix(inverseMatrix);
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

template<typename T>
T getConditionNumber(const vector<vector<T>> &matrix,int nNorm){//nNorm- номер нормы
    if(nNorm==1){
        return getNormMatrix1(matrix)*getNormMatrix1(getInvertibleMatrix(matrix));
    }
    if(nNorm==3){
        return getNormMatrix3(matrix)*getNormMatrix3(getInvertibleMatrix(matrix));
    }
    assert(false);
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
void printMatrix(vector<vector<T>> m) {
    for (auto &str : m) {
        for (T el : str) {
            cout << el << "    ";
        }
        cout << endl;
    }
    cout << endl;
}

