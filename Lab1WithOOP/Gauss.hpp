
// Created by andrey on 16.09.17.
//
#ifndef LAB1WITHOOP_GAUSS_H
#define LAB1WITHOOP_GAUSS_H
#include<vector>
#include <stack>
#include<utility>
using namespace std;

template<typename T>
class BasicInterface;

template <typename T>
class Gauss : public BasicInterface<T>{
private:
    stack<pair<int,int>> shiftColumn;//для поиска главного элемента по всей матрице, чтобы вернуть вектор в нужном порядке

    Gauss(vector<vector<T>> A, vector<T> b){
        this->A=A;
        this->originalA=A;
        this->b=b;
    }
//поиск максимального элемента в столбце nColumn, начиная со строки nBeginStr
    int findMaxStr(int nColumn,int nBeginStr, vector<vector<T>> matrix){
        if (nBeginStr+1 >= matrix.size()){  //проверка на выход за пределы
            return nBeginStr;
        }
        int nMax=nBeginStr;
        T max = matrix[nBeginStr][nColumn];
        for(int i = nBeginStr+1; i< matrix.size(); i++){
            if (matrix[i][nColumn] > max){
                max = matrix[i][nColumn];
                nMax = i;
            }
        }
        return nMax;
    }

    static void swapColumn(vector<vector<T>> &matrix, int n1,int n2){
        for (int i = 0; i < matrix[0].size(); i++) {
            swap(matrix[i][n1], matrix[i][n2]);
        }
    }
    //поиск по подматрице начиная с элемента на главной диагонали с номером nEl, возвращается номер строки макс элемента
    int findMaxElementMatrix(int nEl){
        int nMaxStr = nEl;
        int nMaxColumn= nEl;
        auto max =this->A[nEl][nEl];
        for(int i =nEl;i<this->A.size();i++) {
            for (int j = nEl; j<this->A[0].size(); j++) {
                if(max<this->A[i][j]){
                    max =this->A[i][j];
                    nMaxStr=i;
                    nMaxColumn=j;
                }
            }
        }
        if(nEl!=nMaxColumn) {
            swapColumn(this->A,nEl,nMaxColumn);
            shiftColumn.push(make_pair(nEl,nMaxColumn));
        }
        return nMaxStr;
    }

    void convertToTriangleMatrix(){
        int i=0;
        for (; i < this->A.size()-1; i++){ //сколько проходов глобально итерации прямого обхода
            int nMaxStr =this->findMaxStr(i,i,this->A);
           // int nMaxStr= findMaxElementMatrix(i);
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

    void shiftVectorsEl(vector<T> &v){
        while(!shiftColumn.empty()){
            pair<int,int> p = static_cast<pair<int, int> &&>(shiftColumn.top());
            shiftColumn.pop();
            swap(v[p.first],v[p.second]);
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
        auto result= BasicInterface<T>::solveSystem(instance);
        //для выбора главного элемента по всей матрице, потом через флаги надо все организовать
     //   instance->shiftVectorsEl(result);
        //-----------
        delete instance;
        return result;
    }


};


#endif //LAB1WITHOOP_GAUSS_H
