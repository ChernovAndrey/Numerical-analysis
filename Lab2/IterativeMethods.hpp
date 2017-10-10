//
// Created by andrey on 21.09.17.
//
#ifndef LAB2_ITERATIVEMETHODS_H
#define LAB2_ITERATIVEMETHODS_H

#include <iostream>
#include <vector>
#include "matrixOperations.h"
#include "vectorOperations.h"
#include "workWithConsole.h"
#include <typeinfo>

using namespace std;

template<typename T>
class IterativeMethods { //базовый абсрактный класс
protected:
    T eps;
    vector<T> x;//начальное приближение
    vector<vector<T>> A;
    vector<T> b;
public:
    IterativeMethods(T eps, vector<T> x, vector<vector<T>> A, vector<T> b) {
        this->eps = eps;
        this->x = x;
        this->A = A;
        this->b = b;
    }

    static vector<T> solveSystem(IterativeMethods *instance) {
        try {
            instance->convertToIterativeMatrix();
        }catch (invalid_argument& ex){
            cout<< ex.what()<<endl;
            return {};
        }
        auto norm = getNormMatrix3(instance->A);
        cout<<"norm C ="<< norm <<'\t';
        //hard code for first ex
       /* vector<T> res = {5, -7, 12, 4};
        vector<T> x0(4,0);
        auto suggestCountIter=1;
        while(norm*normVector(diffVectors(res,x0))>instance->eps){
            suggestCountIter++;
            norm*=norm;
        }
        cout<<"suggest count iter>="<<suggestCountIter<<'\t';*/
        //end hard
        return instance->iterations();
    }

protected:

    //переставляется i строка со первой строкой после нее с ненул. диаг эл.
    static vector<vector<T>> swapStrIMatrix(vector<vector<T>> matrix, int i){
        int j=i+1;
        while (IterativeMethods<T>::compareWithZero(matrix[j][j])){
            j++;
            if(j==matrix.size()) return {};
        }
        swap(matrix[i],matrix[j]);
        return matrix;
    }

    virtual void convertToIterativeMatrix()=0;//C в уравнении x=C*x + b

    virtual vector<T> iterations() {
        auto normA = getNormMatrix3(A);
        T eps1 = abs(eps * (1 - normA) / normA);
        cout << "eps1=" << eps1 << '\t';
        auto flag = false;
        vector<T> prevX(x);
        int countIterations = 0;
        while (((normVector(diffVectors(x, prevX)) >= eps1) || !flag)) {
            prevX = x;
            //x = sumVector(multiMatrixVector(A,x),b);
            x = modificationX(prevX);
            flag = true;
            countIterations++;
        }
        cout << "Count iterations=" << countIterations << '\t';
        return x;
    }

    virtual vector<T> modificationX(const vector<T> &prevX)=0; //расчет k-ого x


    static bool compareWithZero(T el) {
        if (typeid(T).name() == typeid(double).name()) {
            return (abs(el) < 1e-14);
        }

        if (typeid(T).name() == typeid(float).name()) {
            return (abs(el) < 1e-07);
        }

        cout << "Invalid type";
        assert(false);
        return false;
    }

};


#endif //LAB2_ITERATIVEMETHODS_H
