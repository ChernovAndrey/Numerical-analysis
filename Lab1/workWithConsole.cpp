//
// Created by andrey on 10.09.17.
//
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template<typename T>
void printVector(vector<T> v){
    cout<<"vector:"<<endl;
    for (double i : v) {
        cout << i << "    ";
    }
    cout << endl;
}
template<typename T>
void printMatrix(vector<vector<T>> m) {

    for (auto &str : m) {
        for (double el : str) {
            cout << el << "    ";
        }
        cout << endl;
    }
    cout << endl;
}




/*
vector<vector<double>> InputMatrix() {
    int n, m;
    cout << "input matrix size:" << endl;
    cout << "n=";
    cin >> n;
    cout << "m=";
    cin >> m;
    vector<vector<double>> matrix(n);
    for (int i = 0; i < n; i++) {
        vector<double> help(m);
        cout <<"input "<< i+1 <<" str:"<< endl;
        for(int j = 0; j<m ;j++){
            cin >> help[j];
        }
        matrix[i]=help;
    }
    return matrix;
}*/
