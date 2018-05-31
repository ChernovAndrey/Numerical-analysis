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


class BasicInterface {

protected:

    vector<vector<double>> originalA;//исходная матрица
    vector<vector<double>> A;
    vector<double> b;
    BasicInterface() = default;

    virtual void convertToTriangleMatrix()=0;

    static bool compareWithZero(double el){
        double E;
        if(typeid(el).name()==typeid(float).name()){
            E = 1e-7;
        }
        if(typeid(el).name()==typeid(double).name()){
            E = 1e-14;
        }
        return abs(el)<E;
    }

    static vector<double> multiMatrixVector(vector<vector<double>> m, vector<double> v){
        vector<double> result(v.size());
        for(int i=0;i < m.size(); i++){
            result[i]=0;
            for (int j = 0; j < v.size(); j++) {
                result[i] += m[i][j]*v[j];
            }
        }
        return result;
    }

    //обратный ход
    vector<double> reverse(){
        const double E = 1e-7;
        vector<double> result(A.size());
        for(int i = static_cast<int>(A.size() - 1); i >= 0; i--){
            double s =0.0;
            for(auto j=i+1;j<A.size();j++){
                s= s - A[i][j]*result[j];
            }
            if(compareWithZero(A[i][i])) {
                cout<<"деление на ноль, BasicInterface, reverse"<<endl;
                result[i]=0.25;
                //return {};
            }else result[i] =(s + b[i])/A[i][i]; // прибавляем: поледний столбец, i-ая строка
        }
        return result;
    }

    void swapStr(int nStr1,int nStr2) {
        if (nStr1 == nStr2) return;
        swap(A[nStr1],A[nStr2]);
        swap(b[nStr1],b[nStr2]);
    }


    double getResidualWithB(vector<double> b1){
        //   cout<<"b1";
        //   printVector(b1);
        double norm;
        for(int i=0;i<this->b.size();i++){
            norm+=(b1[i]-this->b[i])*(b1[i]-this->b[i]);
        }
        return sqrt(norm);
    }

public:

    static vector<vector <double>> matrixMultiplication(vector<vector<double>> a, vector<vector<double>> b){
        vector<vector<double>> multi(a.size(),vector<double>(a[a.size()-1].size(),0.0));
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

    static vector<vector <double>> transposeMatrix(vector<vector <double>> matrix){
        vector<vector<double>> newMatrix(matrix[matrix.size()-1].size(),vector<double>(matrix.size(),0.0));
        for(int i=0;i<matrix.size(); i++) {
            vector<double> help(matrix.size());
            for (int j = 0; j < matrix[i].size(); ++j) {
                newMatrix[j][i]=matrix[i][j];
            }
        }
        return newMatrix;
    }

    static void printVector(vector<double> v){
        cout<<"vector:"<<endl;
        for (double i : v) {
            cout << i << "    ";
        }
        cout << endl;
    }

    static void printMatrix(vector<vector<double>> m) {
        for (auto &str : m) {
            for (double el : str) {
                cout << el << "    ";
            }
            cout << endl;
        }
        cout << endl;
    }

    static vector<double> solveSystem(BasicInterface* instance){
        //  printMatrix(instance->A);
        auto result = instance->reverse();
        if (result.empty()){
            return {};
        }

        //     cout<<"Residual="<< instance->getResidualWithB(multiMatrixVector(instance->A,result)) <<endl;

        return result;
    }

};
#endif //LAB1WITHOOP_BASICINTERFACE_H
