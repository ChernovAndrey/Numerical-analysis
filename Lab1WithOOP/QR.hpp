// Created by andrey on 17.09.17.
//
#include<iostream>
#include<vector>
#include"cmath"
using namespace std;
#ifndef LAB1WITHOOP_QR_H
#define LAB1WITHOOP_QR_H


template<typename T>
class BasicInterface;

template <typename T>
class QR : public BasicInterface<T>{
public:

private:
    QR(vector<vector<T>> A, vector<T> b){
        this->A=A;
        this->b=b;
    }

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
//когда меняем матрицу A то меняем и вектор b, если меняем T, то естественно без вектора
    void transformateMatrix(T c, T s, int ni, int nj,vector<vector<T>> &matrix, bool changeB=false){
        vector<T> strI(matrix[0].size());
        vector<T> strJ(matrix[0].size());
        for(int i=0; i< matrix[0].size(); i++){
            strI[i] = c*matrix[ni][i] + s*matrix[nj][i];
            strJ[i] = -s*matrix[ni][i] + c*matrix[nj][i];
        }
        matrix[ni]= strI;
        matrix[nj]= strJ;
        if (!changeB) return;
        T bi = c*this->b[ni] + s*this->b[nj];
        T bj = -s*this->b[ni] + c*this->b[nj];
        this->b[ni]=bi;
        this->b[nj]=bj;
    }

    void upsertTMatrix(T c, T s, int ni, int nj,vector<vector<T>> &TMatrix, bool flag){//инициализация или обновление
        if(!flag){
            TMatrix=createTijMatrix(c, s, ni, nj, static_cast<int>(TMatrix.size()));
        }else{
            transformateMatrix(c,s,ni,nj,TMatrix);
        }
    }

//прямой ход метода вращений
    void rotation(int ni, int nj,vector<vector<T>> &TMatrix, bool flagInitTMatrix =false) {  //ni, nj -номер строк
        T sqrtA = sqrt(this->A[ni][ni]*this->A[ni][ni] + this->A[nj][ni]*this->A[nj][ni]);
        if(BasicInterface<T>::compareWithZero(sqrtA)){
            throw INFINITY;
        }
        T c = this->A[ni][ni]/sqrtA;
        T s = this->A[nj][ni]/sqrtA;
        if(!TMatrix.empty()) {
            upsertTMatrix(c,s,ni,nj,TMatrix,flagInitTMatrix);
        }
        transformateMatrix(c,s,ni,nj,this->A,true);
    }

//треугольная матрица
    void convertToTriangleMatrix(){
        vector<vector<T>> TMatrix(this->A.size());
        auto flagInitTMatrix = false;//инициализирована ли матрица или нет
        for (int i =0; i<this->A.size()-1; i++) {
            for( int j=i+1; j<this->A.size(); j++){
                try {
                    rotation(i, j, TMatrix, flagInitTMatrix);
                    flagInitTMatrix = true;
                }
                catch (...){}//ignore
            }
        }
        auto Q = transposeMatrix(TMatrix);
        auto R = this->A;
        cout <<"Q:"<<endl;
        BasicInterface<T>::printMatrix(Q);
        cout <<"R:"<<endl;
        BasicInterface<T>::printMatrix(R);
        cout <<"A:"<<endl;
        BasicInterface<T>::printMatrix(BasicInterface<T>::matrixMultiplication(Q,R));
    }
public:
    static vector<T> solveSystem(vector<vector<T>> A, vector<T> b){
        auto* instance = new QR(A,b);
        try {
            instance->convertToTriangleMatrix();
        }
        catch (...){
            return {};
        }
        BasicInterface<T>::printVector(instance->b);
        return BasicInterface<T>::solveSystem(instance);
    }


};



#endif //LAB1WITHOOP_QR_H
