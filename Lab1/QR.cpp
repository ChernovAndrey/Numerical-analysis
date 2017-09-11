//
// Created by andrey on 06.09.17.
//
#include<iostream>
#include "workWithConsole.h"
#include "generalMethods.h"
#include<cmath>
using namespace std;
template <typename T>
vector<vector <T>> matrixMultiplication(vector<vector<T>> a, vector<vector<T>> b){
    vector<vector<T>> multi(a.size(),vector<T>(a[a.size()-1].size(),0.0));

    for(int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            int f =b[i].size();
            for (int k = 0; k < a[i].size(); ++k) {
                multi[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return multi;
}
template<typename T>
vector<vector<T>> createTijMatrix(T c, T s, int ni, int nj,int strSize){ //содание Tij матрицы, strSize-кол-во строк
    vector<vector<T>> Tij(strSize);
    for(int i=0;  i < strSize; i++){
        vector<T> strT(strSize+1);//стобцов на 1 больше чем строк
        for(int j =0; j<strT.size(); j++){
            if((i==ni)&&(j==nj)){
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
    printMatrix(Tij);
    return Tij;
}

//замена i, j  строки матрицы на их линейную комбинацию с коэф
template <typename T>
vector<vector<T>> transformateMatrix(vector<vector<T>> matrix, T c, T s, int ni, int nj){
    vector<T> strI(matrix.size()+1); //cтолбцов на 1 больше чем строк
    vector<T> strJ(matrix.size()+1);
    cout<< matrix[0][0];
    for(int i=0; i< matrix.size()+1; i++){
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
    T Sqrt = sqrt(matrix[ni][ni]*matrix[ni][ni] + matrix[nj][ni]*matrix[nj][ni]);
    T c = matrix[ni][ni]/Sqrt;
    T s = matrix[nj][ni]/Sqrt;
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
 vector<vector<T>> getRMatrix(vector<vector<T>> matrix){
    vector<vector<T>> TMatrix(matrix.size());
    auto flagInitTMatrix = false;//инициализирована ли матрица или нет
    const T E =0.2*1e-5;
    for (int i =0; i<matrix.size()-1; i++) {
        for( int j=i+1; j<matrix.size(); j++){
            //auto T = createTMatrix(matrix[i], matrix[j],i,j);
           // auto A = matrixMultiplication(T, matrix);
            if(abs(matrix[i][i])< E){
                int nMaxStr =findMaxStr(i,i,matrix);
                if (abs(matrix[nMaxStr][i]) < E){
                    return {};
                }
                matrix = swapStrMatrix(nMaxStr,i,matrix);
            }
            matrix = rotation(matrix, i, j, TMatrix,flagInitTMatrix);
            flagInitTMatrix=true;
        }
    }
    cout<<"T"<<endl;
    cout<<"---------------------------";
    printMatrix(TMatrix);
    printMatrix(transposeMatrix(TMatrix));
    printMatrix(matrixMultiplication(TMatrix,matrix));
    return matrix;
}

template<typename T>
std::vector<T> methodQR(std::vector<std::vector<T>> matrix){
    auto R = getRMatrix(matrix);// std::move что это?
    printMatrix(R);
    return Reverse(R);
}
