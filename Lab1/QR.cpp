//
// Created by andrey on 06.09.17.
//
#include<iostream>
#include "workWithConsole.h"
#include "generalMethods.h"
#include "cmath"
#include<cmath>
#include <cassert>

using namespace std;

template<typename T>
vector<vector<T>> createTijMatrix(T c, T s, int ni, int nj,int strSize){ //содание Tij матрицы, strSize-кол-во строк
    vector<vector<T>> Tij(strSize);
    for(int i=0;  i < strSize; i++){
        vector<T> strT(strSize);//стобцов на 1 больше чем строк, но b исключаем
        for(int j =0; j<strT.size(); j++){
            if((i==ni)&&(j==ni)){
                strT[j] = c;
                continue;
            }
            if((i==nj)&&(j==nj)){
                strT[j] = c;
                continue;
            }
            if((i==ni)&&(j==nj)){
                strT[j] = s;
                continue;
            }
            if((i==nj)&&(j==ni)){
                strT[j] = -s;
                continue;
            }
            if(i==j){
                strT[j]=1;
                continue;
            }
            strT[j]=0;
        }
        Tij[i] = strT;
    }
    return Tij;
}

//замена i, j  строки матрицы на их линейную комбинацию с коэф
template <typename T>
vector<vector<T>> transformateMatrix(vector<vector<T>> matrix, T c, T s, int ni, int nj){
    vector<T> strI(matrix[0].size());
    vector<T> strJ(matrix[0].size());
    for(int i=0; i< matrix[0].size(); i++){
        strI[i] = c*matrix[ni][i] + s*matrix[nj][i];
        strJ[i] = -s*matrix[ni][i] + c*matrix[nj][i];
    }
    matrix[ni]= strI;
    matrix[nj]= strJ;
    return matrix;
}

template <typename T>
void upsertTMatrix(T c, T s, int ni, int nj,vector<vector<T>> &TMatrix, bool flag){//инициализация или обновление
    if(!flag){
      TMatrix=createTijMatrix(c, s, ni, nj, static_cast<int>(TMatrix.size()));
    }else{
        TMatrix=transformateMatrix(TMatrix,c,s,ni,nj);
    }
}

//прямой ход метода вращений
template <typename T>
vector<vector<T>> rotation(vector<vector<T>> matrix, int ni, int nj,vector<vector<T>> &TMatrix, bool flagInitTMatrix =false) {  //ni, nj -номер строк
    T sqrtA = sqrt(matrix[ni][ni]*matrix[ni][ni] + matrix[nj][ni]*matrix[nj][ni]);
    const T E =1e-6;
    if(abs(sqrtA)<E){
        throw INFINITY;
    }
    T c = matrix[ni][ni]/sqrtA;
    T s = matrix[nj][ni]/sqrtA;
    if(!TMatrix.empty()) {
        upsertTMatrix(c,s,ni,nj,TMatrix,flagInitTMatrix);
    }
    matrix = transformateMatrix(matrix,c,s,ni,nj);
    return matrix;
}

template<typename  T>
vector<vector <T>> transposeMatrix(vector<vector <T>> matrix){
    vector<vector<T>> newMatrix(matrix[matrix.size()-1].size(),vector<T>(matrix.size(),0.0));
    for(int i=0;i<matrix.size(); i++) {
        vector<T> help(matrix.size());
        for (int j = 0; j < matrix[i].size(); ++j) {
            newMatrix[j][i]=matrix[i][j];
        }
    }
    return newMatrix;
}
//треугольная матрица
template <typename T>
 vector<vector<T>> getTriangularMatrixQR(vector<vector<T>> matrix){
    vector<vector<T>> TMatrix(matrix.size());
    auto flagInitTMatrix = false;//инициализирована ли матрица или нет
    const T E =1e-14;
    for (int i =0; i<matrix.size()-1; i++) {
        for( int j=i+1; j<matrix.size(); j++){
            /*if(abs(matrix[i][i])< E){
                int nMaxStr =findMaxStr(i,i,matrix);
                if (abs(matrix[nMaxStr][i]) < E){
                    return {};
                }
                matrix = swapStrMatrix(nMaxStr,i,matrix);
            }*/
            try {
                matrix = rotation(matrix, i, j, TMatrix, flagInitTMatrix);
                flagInitTMatrix = true;
            }
            catch (...){}//ignore
        }
    }
    auto Q = transposeMatrix(TMatrix);
    auto R = excludeVectorB(matrix);
    cout <<"Q:"<<endl;
    printMatrix(Q);
    cout <<"R:"<<endl;
    printMatrix(R);
    cout <<"A:"<<endl;
    printMatrix(matrixMultiplication(Q,R));
    return matrix;
}

template<typename T>
std::vector<T> methodQR(std::vector<std::vector<T>> matrix) {
    auto A = excludeVectorB(matrix);
    auto b = getVectorB(matrix);
    auto triangularMatrix = getTriangularMatrixQR(matrix);
    printMatrix(triangularMatrix);
    auto result = Reverse(triangularMatrix);
    if (result.empty()) {
        // cout <<"matrix degenerate"<<endl;
        return {};
    }
    auto b1 = multiMatrixVector(A, result);
    printVector(b);
    cout << "residual=" << getResidual(b, b1) << endl;
    return result;
}
