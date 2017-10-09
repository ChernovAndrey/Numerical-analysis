#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include "assert.h"
using namespace std;
//
// Created by andrey on 06.09.17.
//



template <typename T>
vector<vector<T>> ReadFile(vector<vector<T>> matrix, int number){//number - номер файла
  //  matrix = new vector(4,vector<T>(5));
    ifstream in;
    if(number==1) {
        in.open("../systems/DATA1.txt");
    }
    if(number==2) {
        in.open("../systems/DATA2.txt");
    }
    if((number!=1)&&(number!=2)){
        cout <<"incorrect number file";
        assert(false);
    }
    if (!in) {
        cout << "Cannot open file.\n";
    }
    for (int i = 0; i < 4; i++) {
        vector<T> help(5);
        for (int j = 0; j < 5; j++) {
            in >> help[j];
           // cout << matrix[i][j] <<endl;
        }
        matrix.push_back(help);
    }
    in.close();
    return matrix;
}

template<typename T>
void setMatrixEx1(vector<vector<T>> &matrix){
    matrix ={
            {15, 2, -3, 7, 53},
            {-5, 11, 2, -3, -90},
            {0, -1, 7, 4, 107},
            {12, 0, -6, 20, 68}
            //lambda max 25.1147
    };
}

template<typename T>
void setMatrixEx2(vector<vector<T>>  &matrix){
    matrix ={
            {86.00, -8.93, -9.59, -3.91, 818.58},
            {4.05, -100.00, -9.10, -8.14, 898.74},
            {0.26, 3.61, -71.80, -4.28,  -912.22},
            {-4.03, -6.88, 6.57, -198.60, -687.06}
    };
    //{-199.045, -97.807, 85.8335, -73.3811} cобственные числа
}
