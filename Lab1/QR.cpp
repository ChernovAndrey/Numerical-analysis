//
// Created by andrey on 06.09.17.
//
#include<iostream>
#include "workWithConsole.h"
#include<cmath>
using namespace std;

//посление столбцы не трогаем
/* std::vector<std::vector<double>> matrixMultiplication(std::vector<std::vector<double>> T,std::vector<std::vector<double>> matrix) {
    //умножаем T на A(посление столбцы в matrix не трогаем)
    vector<vector<double >> C(T.size());
    for (int i = 0; i < T.size(); i++) {
        vector<double> help(T[i].size());
        for (int j = 0; j < T[i].size() - 1; j++) {
            help[j] = 0;
            for (int k = 0; k < matrix[i].size() - 1; k++)
                help[j] += T[i][k] * matrix[k][j];
        }
        C[i] = help;
    }

    //умножаем T на b(посление столбцы в matrix)
    vector<double> b(matrix.size());
    for(int i = 0; i<matrix.size();i++){
        b[i]=matrix[i][matrix[i].size()-1];
    }
    cout <<"b:"<<endl;
    printVector(b);
    vector<double> bNew(matrix.size());
    for(int i=0; i<T.size(); i++)
    {
        bNew[i]=0;
        for(int j=0; j<T[i].size(); j++)
        {
            bNew[i]+=T[i][j]*b[j];
        }
    }
    cout <<"bNew:"<<endl;
    printVector(bNew);
    for(int i = 0; i<matrix.size();i++){
        matrix[i][matrix[i].size()-1]=bNew[i];
    }
    return C;
}*/

//матрица на которую умножаем исходную на каждом шаге, k - номер строки strk
// (и номер элемента, который искл.), m- номер строки strm
/*vector<vector<double>> createTMatrix(vector<double> strk,vector<double> strm, int k, int m){
    double Sqrt =sqrt(strk[k]*strk[k] + strm[k]*strm[k]);
    double c = strk[k]/Sqrt;
    double s = strm[k]/Sqrt;
    cout <<"size="<< strk.size()<<endl;
    vector<vector<double >> T(strk.size()-1); //вообще костыль, но столбцов гарантировано больше на 1 чем стр.
    for(int i=0;  i < T.size(); i++){
        vector<double> strT(strk.size()-1);
        for(int j =0; j<strT.size(); j++){
            if((i==k)&&(j==k)){
                strT[j] = c;
                continue;
            }
            if((i==m)&&(j==m)){
                strT[j] = c;
                continue;
            }
            if((i==k)&&(j==m)){
                strT[j] = s;
                continue;
            }
            if((i==m)&&(j==k)){
                strT[j] = -s;
                continue;
            }
            if(i==j){
                strT[j]=1;
                continue;
            }
            strT[j]=0;
        }
        T[i]=strT;
    }
    cout <<"T"<<endl;
    printMatrix(T);
    return T;
}*/

//прямой ход метода вращений
template <typename T>
 vector<vector<T>> rotation(vector<vector<T>> matrix, int ni, int nj) {  //ni, nj -номер строк
    cout << matrix.size() <<endl;
    T Sqrt = sqrt(matrix[ni][ni]*matrix[ni][ni] + matrix[nj][ni]*matrix[nj][ni]);
    T c = matrix[ni][ni]/Sqrt;
    T s = matrix[nj][ni]/Sqrt;
    vector<T> strI(matrix.size()+1); //cтолбцов на 1 больше чем строк
    vector<T> strJ(matrix.size()+1);
    for(int i=0; i< matrix.size()+1; i++){
        strI[i] = c*matrix[ni][i] + s*matrix[nj][i];
        strJ[i] = -s*matrix[ni][i] + c*matrix[nj][i];
    }
    matrix[ni]= strI;
    matrix[nj]= strJ;
    return matrix;
}
//треугольная матрица
template <typename T>
 vector<vector<T>> getRMatrix(vector<vector<T>> matrix){
    for (int i =0; i<matrix.size()-1; i++) {
        //vector<double> str(matrix[i]);
        for( int j=i+1; j<matrix.size(); j++){
            //auto T = createTMatrix(matrix[i], matrix[j],i,j);
           // auto A = matrixMultiplication(T, matrix);
            matrix = rotation(matrix, i, j);
        }
    }
    return matrix;
}
template <typename T>
vector<T> calculateResultVectorQR(vector<vector<T>> matrix){
    vector<T> result(matrix.size());
    for(auto i= static_cast<int>(matrix.size() - 1); i >= 0; i--){
        double s =0.0;
        for(auto j=i+1;j<matrix.size();j++){
            s= s - matrix[i][j]*result[j];
        }
        result[i] =(s + matrix[i][matrix[i].size()-1])/matrix[i][i]; // прибавляем: поледний столбец, i-ая строка
    }
    return result;
}
template<typename T>
std::vector<T> methodQR(std::vector<std::vector<T>> matrix){
    auto R = getRMatrix(matrix);// std::move что это?
    printMatrix(R);
    return calculateResultVectorQR(R);
}
