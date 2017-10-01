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

using namespace std;
template<typename T>
class IterativeMethods { //базовый абсрактный класс
protected:
    T eps;
    vector <T> x;//начальное приближение
    vector<vector<T>> A;
    vector<T> b;
public:
    IterativeMethods(T eps, vector<T> x, vector<vector<T>> A, vector<T> b){
        this->eps=eps;
        this->x = x;
        this->A = A;
        this->b = b;
    }

    static vector<T> solveSystem(IterativeMethods* instance){
      //  instance->matrixNormalizationA();
        instance->convertToIterativeMatrix();
        return instance->iterations();
    }

protected:

    virtual void convertToIterativeMatrix()=0;//C в уравнении x=C*x + b

    vector<T> iterations(){
        auto normA = getNormMatrix3(A);
        T eps1=abs(eps *(1-normA)/normA);
        cout<<"eps1="<<eps1<<endl;
        auto flag = false;
        vector<T> prevX(x);
        int countIterations=0;
        while( ((normVector(diffVectors(x,prevX))>=eps1) || !flag) ){
            prevX = x;
            //x = sumVector(multiMatrixVector(A,x),b);
            x=modificationX(prevX);
            flag = true;
            countIterations++;
        }
        cout<<"Count iterations="<< countIterations <<endl;
        return x;
    }

    virtual vector<T> modificationX(const vector<T> &prevX)=0; //расчет k-ого x

};


#endif //LAB2_ITERATIVEMETHODS_H
