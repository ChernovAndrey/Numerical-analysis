//
// Created by andrey on 16.09.17.
//

#ifndef LAB1WITHOOP_BASICINTERFACE_H
#define LAB1WITHOOP_BASICINTERFACE_H
#include<iostream>
#include <vector>
#include "cmath"
#include <cassert>
#include <typeinfo>
using namespace std;

template <typename T>
class BasicInterface {

protected:
    vector<vector<T>> A;
    vector<T> b;

    BasicInterface() = default;

    virtual void convertToTriangleMatrix()=0;

    static bool compareWithZero(T el){
        T E;
        if(typeid(el).name()==typeid(float).name()){
            E = 1e-7;
        }
        if(typeid(el).name()==typeid(double).name()){
            E = 1e-14;
        }
        return abs(el)<E;
    }

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

    //обратный ход
    vector<T> reverse(){
        const T E = 1e-7;
        vector<T> result(A.size());
        for(int i = static_cast<int>(A.size() - 1); i >= 0; i--){
            double s =0.0;
            for(auto j=i+1;j<A.size();j++){
                s= s - A[i][j]*result[j];
            }
            if(abs(A[i][i])< E) return {};
            result[i] =(s + b[i])/A[i][i]; // прибавляем: поледний столбец, i-ая строка
        }
        return result;
    }

     void swapStr(int nStr1,int nStr2) {
         if (nStr1 == nStr2) return;

         vector<T> swapHelpA(A[nStr1]);
         A[nStr1] = A[nStr2];
         A[nStr2] = swapHelpA;

         T swapHelpB=b[nStr1];
         b[nStr1] = b[nStr2];
         b[nStr2] = swapHelpB;

     }


    T getResidualWithB(vector<T> b1){
        T norm;
        cout<<"b1";
        printVector(b1);
        printVector(this->b);
        if (b1.size()!=this->b.size()) assert(false);
        for(int i=0;i<this->b.size();i++){
            norm+=(b1[i]-this->b[i])*(b1[i]-this->b[i]);
        }
        return sqrt(norm);
    }

public:

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
    static vector<T> getVectorB(vector<vector<T>> matrix){
        vector<T> result;
        for(int i=0;i< matrix.size();i++){
            result.push_back(matrix[i][matrix[i].size()-1]);
        }
        return result;
    }

    //на вход подается расширенная матрица и просто отбрасывается последний столбец
    static vector<vector<T>> getMatrixA(vector<vector<T>> matrix){
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

    static void printVector(vector<T> v){
        cout<<"vector:"<<endl;
        for (T i : v) {
            cout << i << "    ";
        }
        cout << endl;
    }

    static void printMatrix(vector<vector<T>> m) {
        for (auto &str : m) {
            for (T el : str) {
                cout << el << "    ";
            }
            cout << endl;
        }
        cout << endl;
    }

    static vector<T> solveSystem(BasicInterface* instance){
        //  BasicInterface instance = BasicInterface(A,b);
        //    instance->convertToTriangleMatrix();
        printMatrix(instance->A);
        /*if (matrix.empty()) {
            return {};
        }*/

        auto result = instance->reverse();
        if (result.empty()){
            // cout <<"matrix degenerate"<<endl;
            return {};
        }

        cout<<"Residual="<< instance->getResidualWithB(multiMatrixVector(instance->A,result)) <<endl;

        delete instance;
        return result;
    }

};
#include "Gauss.hpp"
#endif //LAB1WITHOOP_BASICINTERFACE_H
