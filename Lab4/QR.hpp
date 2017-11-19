// Created by andrey on 17.09.17.
//
using namespace std;
#ifndef LAB1WITHOOP_QR_H
#define LAB1WITHOOP_QR_H
#include<iostream>
#include<vector>
#include"cmath"
#include "matrixOperations.h"
#include "vectorOperations.h"
template<typename T>
class BasicInterface;

template <typename T>
class QR : public BasicInterface<T>{
public:

private:

    explicit QR(vector<vector<T>> A){
        this->A=A;
    }

    QR(vector<vector<T>> A,vector<T> b){
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

  /*  //замена i, j  строки матрицы на их линейную комбинацию с коэф //equal T*A
    void transformateStrMatrix(T c, T s, int ni, int nj){
        vector<T> strI(this->A[0].size());
        vector<T> strJ(this->A[0].size());
        for(int i=0; i< this->A[0].size(); i++){
            strI[i] = c*this->A[ni][i] + s*this->A[nj][i];
            strJ[i] = -s*this->A[ni][i] + c*this->A[nj][i];
        }
        this->A[ni]= strI;
        this->A[nj]= strJ;
    }*/


    //замена i, j  столбца матрицы на их линейную комбинацию с коэф //equal A*transpose(T)
    void transformateColMatrix(T c, T s, int ni, int nj){
        vector<T> colI(this->A.size());
        vector<T> colJ(this->A.size());
        for(int i=0; i< this->A.size(); i++){
            colI[i] = c*this->A[i][ni] + s*this->A[i][nj];
            colJ[i] = -s*this->A[i][ni] + c*this->A[i][nj];
        }

        for(int i=0;i<2;i++){
            int nCurCol;
            vector<T> curCol;
            if(i==0) {
                nCurCol=ni;
                curCol=colI;
            }
            else {
                nCurCol=nj;
                curCol=colJ;
               }
            for(int j=0;j<this->A.size();j++){
                this->A[j][nCurCol]=curCol[j];
            }
        }
    }


//замена i, j  строки матрицы на их линейную комбинацию с коэф
//когда меняем матрицу A то меняем и вектор b, если меняем T, то естественно без вектора
    void transformateStrMatrix(T c, T s, int ni, int nj,vector<vector<T>> &matrix, bool changeB=false){
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
            transformateStrMatrix(c,s,ni,nj,TMatrix);
        }
    }

//прямой ход метода вращений; //flagB-есть ли вектор b
    void rotation(int ni, int nj,vector<vector<T>> &TMatrix, bool flagInitTMatrix, bool flagB=false) {  //ni, nj -номер строк
        T sqrtA = sqrt(this->A[ni][ni]*this->A[ni][ni] + this->A[nj][ni]*this->A[nj][ni]);
        if(BasicInterface<T>::compareWithZero(sqrtA)){
            throw INFINITY;
        }
        T c = this->A[ni][ni]/sqrtA;
        T s = this->A[nj][ni]/sqrtA;
        if(!TMatrix.empty()) {
            upsertTMatrix(c,s,ni,nj,TMatrix,flagInitTMatrix);
        }
        transformateStrMatrix(c,s,ni,nj,this->A,flagB);
    }




//треугольная матрица
    void iteration(){
        T norm=1.0;//норма элементов последней строки, левее главного элемента
        vector<vector<T>> TMatrix(this->A.size());
        T sigma=this->A[this->A.size()-1][this->A.size()-1];//величина сдвига

        while(!BasicInterface<T>::compareWithZero(norm)) {
            shiftMatrix(this->A, sigma);
            auto flagInitTMatrix = false;//инициализирована ли матрица или нет
            for (int i = 0; i < this->A.size() - 1; i++) {
                for (int j = i + 1; j < this->A.size(); j++) {
                    try {
                        rotation(i, j, TMatrix, flagInitTMatrix);
                        flagInitTMatrix = true;
                    }
                    catch (...) {}//ignore
                }
            }
            auto Q = BasicInterface<T>::transposeMatrix(TMatrix);
            this->A= BasicInterface<T>::matrixMultiplication(this->A,Q);

            backShiftMatrix(this->A, sigma);


            norm = 0.0;
            for(int i=0;i<this->A[0].size()-1;i++){
                T el =this->A[this->A.size()-1][i];
                norm+=sqrt(abs(el));
            }
          //  cout<<"norm="<<norm<<endl;
            //auto R = this->A;
            /*     cout <<"Q:"<<endl;
                 printMatrix(Q);
                 cout <<"R:"<<endl;
                 printMatrix(R);
                 cout <<"A:"<<endl;
                 printMatrix(BasicInterface<T>::matrixMultiplication(Q,R));*/
        }
    }


//треугольная матрица
    void convertToTriangleMatrix(){
        vector<vector<T>> TMatrix(this->A.size());
        auto flagInitTMatrix = false;//инициализирована ли матрица или нет
        for (int i =0; i<this->A.size()-1; i++) {
            for( int j=i+1; j<this->A.size(); j++){
                try {
                    rotation(i, j, TMatrix, flagInitTMatrix, true);
                    flagInitTMatrix = true;
                }
                catch (...){}//ignore
            }
        }
        auto Q = BasicInterface<T>::transposeMatrix(TMatrix);
        auto R = this->A;
          cout <<"Q:"<<endl;
          BasicInterface<T>::printMatrix(Q);
          cout <<"R:"<<endl;
          BasicInterface<T>::printMatrix(R);
          cout <<"A:"<<endl;
          BasicInterface<T>::printMatrix(BasicInterface<T>::matrixMultiplication(Q,R));
    }

    void convertToHessenbergMatrix(){
        for(int i=0;i<this->A[0].size()-2;i++){//по столбцам
            for(int j=i+2;j<this->A.size();j++){//по строкам
                T sqrtA = sqrt(this->A[i+1][i]*this->A[i+1][i] + this->A[j][i]*this->A[j][i]);
                if(BasicInterface<T>::compareWithZero(sqrtA)){
                    cout<<"деление на ноль!"<<endl;
                    throw INFINITY;
                }
                T c = this->A[i+1][i]/sqrtA;
                T s = this->A[j][i]/sqrtA;
                transformateStrMatrix(c,s,i+1,j,this->A);
                transformateColMatrix(c,s,i+1,j);
            }
        }
    }

void reductionDimensionMatrix() {    //уменьшение кол-во столбцов и строк на 1(отбрасыванием)
   // cout<<"size:"<<endl;
    this->A.pop_back();
    for(int i=0;i<this->A.size();i++){
        vector<T> strMatrix= this->A[i];
        strMatrix.pop_back();
        this->A[i]=strMatrix;
    //    cout<<this->A[i].size()<<endl;
    }
  //  cout<<"D"<<this->A.size()<<endl;
}
public:
    static vector<T> findEigenValues(const vector<vector<T>> &A){
        vector<T> result(A.size());
        auto* instance = new QR(A);
        vector<vector<T>> eigenMatrix(A.size());
        instance->convertToHessenbergMatrix();
        cout<<"Hessenberg Matrix:"<<endl;
        printMatrix(instance->A);
        try {
            while(instance->A.size()>1) {
                instance->iteration();
                printMatrix(instance->A);
                result[instance->A.size()-1]=instance->A[instance->A.size()-1][instance->A.size()-1];
                if(instance->A.size()==2) result[0]=instance->A[0][0];
                instance->reductionDimensionMatrix();
            }
        }
        catch (...){
            return {};
        }
        delete instance;
        return result;
    }

    static vector<T> solveSystem(vector<vector<T>> A, vector<T> b){
        auto* instance = new QR(A,b);
        try {
            instance->convertToTriangleMatrix();
        }
        catch (...){
            return {};
        }
        //  BasicInterface<T>::printVector(instance->b);
        auto result = BasicInterface<T>::solveSystem(instance);
        delete instance;
        return result;
    }



    static vector<T> findEigenVector(vector<vector<T>> matrix,T eigenValue) {

        vector<T> x(matrix.size(), -0.25);
        //x[0] = 1.0;

        vector<T> xPrev(matrix.size(), 0);

        shiftMatrix(matrix, eigenValue);
        while (!BasicInterface<T>::compareWithZero(getResidual(x, xPrev))) {

            auto result = QR<T>::solveSystem(matrix, x);

            xPrev=x;
            auto norm=normVector(result);
            for(int i=0;i<x.size();i++){
                x[i]=result[i]/norm;
            }
        }
        return x;
    }

};



#endif //LAB1WITHOOP_QR_H
