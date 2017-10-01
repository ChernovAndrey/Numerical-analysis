//
// Created by andrey on 06.09.17.
//
#include <iostream>
#include <cmath>
#include<vector>
#include "workWithConsole.h"
#include "generalMethods.h"

using namespace std;



//поиск по стобцу, принимает номер столбца, номер начала строки, с которой надо искать, и матрицу,
//возвращается номер строки, с максимальным элементом

template <typename T>
vector<vector<T>> getTriangleMatrixGauss(vector<vector<T>> matrix){
    int i=0;
    const T E = 1e-7;
    for (; i < matrix.size()-1; i++){ //сколько проходов глобально итерации прямого обхода
        int nMaxStr =findMaxStr(i,i,matrix);
        if (abs(matrix[nMaxStr][i]) < E){
            return {};
        }
        matrix = swapStrMatrix(nMaxStr,i,matrix);
        vector<T> strMatrix(matrix[i]);
        for(int j=i+1; j< matrix.size(); j++){ // итерации по срокам матрицы, которые ниже текущего положения
            T c = matrix[j][i]/strMatrix[i]; //коэфф вычитания
            for(int k=0; k< strMatrix.size(); k++){ //вычитание строк, итерация по cтолбцам
                matrix[j][k] = matrix[j][k] - c * strMatrix[k];
            }
        }
    }
    if (abs(matrix[i][i]) < E){
        matrix.clear();
        return matrix;
    }
    return matrix;
}



template <typename T>
vector<T> methodGauss(vector<vector<T>> matrix){
    auto A=excludeVectorB(matrix);
    auto b=getVectorB(matrix);
    matrix = getTriangleMatrixGauss(matrix);
    printMatrix(matrix);
    if (matrix.empty()) {
        return {};
    }
    auto result = Reverse(matrix);
    if (result.empty()){
       // cout <<"matrix degenerate"<<endl;
        return {};
    }
    auto b1 = multiMatrixVector(A,result);
    cout<<"Residual="<< getResidual(b1,b)<<endl;
    return result;
}