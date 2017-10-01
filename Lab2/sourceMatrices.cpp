#include <iostream>
#include <vector>
#include <fstream>
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
}


template<typename T>
void setMatrixEx3(vector<vector<T>> &matrix){
    matrix = {
            {1, 1, 1, 1, 4},
            {2, 3, 3, 3, 11},
            {2, 4, 4, 4, 15},
            {4, 5, 6, 7, 22}
    };
}

template<typename T>
void setMatrixEx4(vector<vector<T >> &matrix){
    matrix = {
            {10, 6, 2, 0, 25},
            {5, 1, -2, 4, 14},
            {3, 5, 1, -1, 10},
            {0, 6, -2, 2, 8}
    };
}

template <typename T>
void setMatrixEx5(vector<vector<T>> &matrix){
    matrix ={
            {28.859, -0.008, 2.406, 19.240, 30.459},
            {14.436, -0.001, 1.203, 9.624, 18.248},
            {120.204, -0.032, 10.024, 80.144, 128.156},
            {-57.714, 0.016, -4.812, -38.478, -60.908}
    };
}

