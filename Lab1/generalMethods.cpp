//
// Created by andrey on 10.09.17.
//

#include <iostream>
#include <vector>
using namespace std;

//обратный ход
template <typename T>
vector<T> Reverse(vector<vector<T>> matrix){
    const T E = 0.2 * 10e-5;
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
    const T E = 1e-7;
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
