//
// Created by andrey on 30.10.17.
//

#ifndef LAB9_SWEEP_H
#define LAB9_SWEEP_H
#include<iostream>
#include <utility>
#include <vector>

using namespace std;

//only for diag matrix
class Sweep {
private:
    vector<vector<double>> matrix;
    vector<double> b;
    vector<double> alpha;
    vector<double> beta;//alpha[0] и beta[0] не используются
    vector<double> result;
    void evaluateCoef(int i){//i-номер alpha и beta
        if(i==2){
            double a=matrix[i-2][1];
            alpha[i-1]=-matrix[i-2][2]/a;
            beta[i-1]=b[i-2]/a;
        }else{
            if(i!=matrix.size()+1){
                double a = (matrix[i-2][1]+matrix[i-2][0]*alpha[i-2]);
                alpha[i-1]=-matrix[i-2][2]/a;
                beta[i-1]=(b[i-2]-matrix[i-2][0]*beta[i-2])/a;
            }else{
                return;
            }
        }
        evaluateCoef(i+1);
    }

    void evaluateResult(int i){//шаг итерации
        if(i==matrix.size()-1){
            result[i]=(b[i]-matrix[i][0]*beta[i])/(matrix[i][1]+matrix[i][0]*alpha[i]);
        }else{
            result[i]=alpha[i+1]*result[i+1]+ beta[i+1];
            if(i==0) return;
        }
        evaluateResult(i-1);
    }

public:
    explicit Sweep(vector<vector<double>> matrix, vector<double> b){
        alpha= vector<double>(matrix.size());
        beta = vector<double>(matrix.size());

        this->b = std::move(b);
        result = vector<double>(matrix.size());
        this->matrix = std::move(matrix);
    }

    vector<double> solveSystem(){
        evaluateCoef(2);
        evaluateResult(static_cast<int>(matrix.size() - 1));
        return result;
    }
};


#endif //LAB9_SWEEP_H
