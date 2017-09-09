//
// Created by andrey on 06.09.17.
//
#include <iostream>
#include <cmath>
#include<vector>
#include "workWithConsole.h"

using namespace std;


const double E = 1e-7;

//поиск по стобцу, принимает номер столбца, номер начала строки, с которой надо искать, и матрицу,
//возвращается номер строки, с максимальным элементом
int findMaxStr(int nColumn,int nBeginStr, vector<vector<double>> matrix){
    if (nBeginStr+1 >= matrix.size()){  //проверка на выход за пределы
        return nBeginStr;
    }
    int nMax=nBeginStr;
    double max = matrix[nBeginStr][nColumn];
    for(int i = nBeginStr+1; i< matrix.size(); i++){
        if (matrix[i][nColumn] - max > E){
            max = matrix[i][nColumn];
            nMax = i;
        }
    }
    return nMax;
}

vector<vector<double>> swapStrMatrix(int nStr1,int nStr2,vector<vector<double>> matrix) {
    if (nStr1 == nStr2) return matrix;
    vector<double> swapHelp(matrix[nStr1]);
    matrix[nStr1] = matrix[nStr2];
    matrix[nStr2] = swapHelp;
    return matrix;
}

vector<vector<double>> getTriangleMatrix(vector<vector<double>> matrix){
    int i=0;
    for (; i < matrix.size()-1; i++){ //сколько проходов глобально итерации прямого обхода
        int nMaxStr =findMaxStr(i,i,matrix);
        if (abs(matrix[nMaxStr][i]) < E){
            return {};
        }
        matrix = swapStrMatrix(nMaxStr,i,matrix);
        vector<double> strMatrix(matrix[i]);
        for(int j=i+1; j< matrix.size(); j++){ // итерации по срокам матрицы, которые ниже текущего положения
            double c = matrix[j][i]/strMatrix[i]; //коэфф вычитания
            for(int k=0; k< strMatrix.size(); k++){ //вычитание стоблцов
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

vector<double> calculateResultVector(vector<vector<double>> matrix){
    vector<double> result(matrix.size());
    for(auto i= static_cast<int>(matrix.size() - 1); i >= 0; i--){
        double s =0.0;
        for(auto j=i+1;j<matrix.size();j++){
            s= s - matrix[i][j]*result[j];
        }
        result[i] =(s + matrix[i][matrix[i].size()-1])/matrix[i][i]; // прибавляем: поледний столбец, i-ая строка
    }
    return result;
}

vector<double> methodGauss(vector<vector<double>> matrix){
    matrix = getTriangleMatrix(matrix);
    printMatrix(matrix);
    if (matrix.empty()) {
        return {};
    }
    return calculateResultVector(matrix);
}