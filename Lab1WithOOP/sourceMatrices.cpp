#include <iostream>
#include <vector>
#include <fstream>
#include "assert.h"
using namespace std;
//
// Created by andrey on 06.09.17.
//



template <typename T>
vector<vector<T>> readFile(vector<vector<T>> matrix, int number){//number - номер файла
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
void getMatrixEx1(vector<vector<T>> &matrix){
    matrix ={
            {1, 1, 1, 1, 4},
            {0, 1, 1, 1, 3},
            {0, 0, 1, 1, 2},
            {0, 0, 0, 1, 1}
    };
}

template<typename T>
void getMatrixEx2(vector<vector<T>>  &matrix){
    matrix ={
            {0, 0, 0, 1, 1},
            {0, 0, 1, 1, 2},
            {0, 1, 1, 1, 3},
            {1, 1, 1, 1, 4}
    };
}


template<typename T>
void getMatrixEx3(vector<vector<T>> &matrix){
    matrix = {
            {1, 1, 1, 1, 4},
            {2, 3, 3, 3, 11},
            {2, 4, 4, 4, 15},
            {4, 5, 6, 7, 22}
    };
}

template<typename T>
void getMatrixEx4(vector<vector<T >> &matrix){
    matrix = {
            {10, 6, 2, 0, 25},
            {5, 1, -2, 4, 14},
            {3, 5, 1, -1, 10},
            {0, 6, -2, 2, 8}
    };
}

template <typename T>
void getMatrixEx5(vector<vector<T>> &matrix){
    matrix ={
            {28.859, -0.008, 2.406, 19.240, 30.459},
            {14.436, -0.001, 1.203, 9.624, 18.248},
            {120.204, -0.032, 10.024, 80.144, 128.156},
            {-57.714, 0.016, -4.812, -38.478, -60.908}
    };
}

