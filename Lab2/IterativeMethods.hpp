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
        instance->matrixNormalizationA();
        instance->convertToIterativeMatrix();
        return instance->iterations();
    }

protected:

    virtual void convertToIterativeMatrix()=0;//C в уравнении x=C*x + b

    void matrixNormalizationA(){
        T normA = getNormMatrix3(A);
        while(normA >= (1-1e-10)){
            for(int i=0;i<A.size();i++){
                T max  = abs(A[i][0]);
                for(int j=1;j<A[0].size();j++){
                    if(abs(A[i][j])> max) {
                        max = abs(A[i][j]);
                    }
                }
                max++;//чтобы всегда больше одного
                for(int j=0;j<A[0].size();j++){
                    A[i][j] = A[i][j]/max;
                }
                b[i]=b[i]/max;
            }
            normA = getNormMatrix3(A);
        }
        cout<<"normA="<<normA<<endl;
    }

    vector<T> iterations(){
        auto normA = getNormMatrix3(A);
        T eps1=abs(eps *(1-normA)/normA);
        cout<<"eps1="<<eps1<<endl;
        auto flag = false;
        vector<T> prevX(x);
        int countIterations=0;
        while( ((normVector(diffVectors(x,prevX))>=eps1) || !flag) ){
            prevX = x;
            x = sumVector(multiMatrixVector(A,x),b);
            flag = true;
            countIterations++;
        }
        cout<<"Count iterations="<< countIterations <<endl;
        return x;
    }
    
    
    
};


#endif //LAB2_ITERATIVEMETHODS_H
