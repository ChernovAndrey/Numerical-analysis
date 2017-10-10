//
// Created by andrey on 21.09.17.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template <typename T>
vector<T> sumVector(vector<T> a, vector<T> b){
    vector<T> c(a.size());
    for(int i=0;i<a.size();i++){
        c[i]= a[i] + b[i];
    }
    return c;
}


template <typename T>
T normVector(vector<T> v){
    T norm =0;
    for (int i = 0; i <v.size() ; ++i) {
        norm+=v[i]*v[i];
    }
    return sqrt(norm);
}

template <typename T>
vector<T> diffVectors(vector<T> a, vector<T> b){
    vector<T> c(a.size());
    for(int i=0;i<a.size();i++){
        c[i]= a[i] - b[i];
    }
    return c;
}

template <typename T>
vector<T> multiNumberVector(vector<T> a, T number){
    vector<T> c(a.size());
    for(int i=0;i<a.size();i++){
        c[i]= number*a[i];
    }
    return c;
}

template <typename T>
T getResidual(vector<T> a,vector<T> b){
    T norm=0;
    for(int i=0;i<a.size();i++){
        norm+=(a[i]-b[i])*(a[i]-b[i]);
    }
    return sqrt(norm);
}
