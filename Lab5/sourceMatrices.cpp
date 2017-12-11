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
void  getMatrixEx1(vector<vector<T>> &matrix){
    matrix ={
            {1.50, 0.00, -0.43, -0.75},
            {0.00, 3.00, 0.87, -0.50},
            {-0.43, 0.87, 2.90, -0.22},
            {-0.75, -0.50, -0.22, 2.60}
    };
}




template<typename T>
void  getMatrixEx2(vector<vector<T>> &matrix){
    matrix ={
            {5.0, 6.0, 3.0, 3.0},
            {-1, 0, 1, 0.0},
            {1, 2, -1, 0},
            {0.0, 0.0, 0.0, 8.0}
    };
}