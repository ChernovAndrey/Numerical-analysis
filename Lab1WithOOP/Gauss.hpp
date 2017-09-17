
// Created by andrey on 16.09.17.
//
#ifndef LAB1WITHOOP_GAUSS_H
#define LAB1WITHOOP_GAUSS_H
#include<vector>
using namespace std;

template<typename T>
class BasicInterface;

template <typename T>
class Gauss : public BasicInterface<T>{
private:
    Gauss(vector<vector<T>> A, vector<T> b){
        this->A=A;
        this->b=b;
    }
//поиск максимального элемента в столбце nColumn, начиная со строки nBeginStr
    int findMaxStr(int nColumn,int nBeginStr, vector<vector<T>> matrix){
        const T E = 1e-7;
        if (nBeginStr+1 >= matrix.size()){  //проверка на выход за пределы
            return nBeginStr;
        }
        int nMax=nBeginStr;
        T max = matrix[nBeginStr][nColumn];
        for(int i = nBeginStr+1; i< matrix.size(); i++){
            if (matrix[i][nColumn] - max > E){
                max = matrix[i][nColumn];
                nMax = i;
            }
        }
        return nMax;
    }

    void convertToTriangleMatrix(){
        int i=0;
        for (; i < this->A.size()-1; i++){ //сколько проходов глобально итерации прямого обхода
            int nMaxStr =this->findMaxStr(i,i,this->A);
            if (BasicInterface<T>::compareWithZero(this->A[nMaxStr][i])){
                throw INFINITY;
            }
            this->swapStr(nMaxStr,i);
            vector<T> strMatrix(this->A[i]);
            for(int j=i+1; j< this->A.size(); j++){ // итерации по срокам матрицы, которые ниже текущего положения
                T c = this->A[j][i]/strMatrix[i]; //коэфф вычитания
                this->b[j]=this->b[j] - c*this->b[i];
                for(int k=0; k< strMatrix.size(); k++){ //вычитание строк, итерация по cтолбцам
                    this->A[j][k] = this->A[j][k] - c * strMatrix[k];
                }
            }
        }
        if (BasicInterface<T>::compareWithZero(this->A[i][i])){
            this->A.clear();
            return;
        }
    }

public:
    static vector<T> solveSystem(vector<vector<T>> A, vector<T> b){
        auto* instance = new Gauss(A,b);
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


#endif //LAB1WITHOOP_GAUSS_H
