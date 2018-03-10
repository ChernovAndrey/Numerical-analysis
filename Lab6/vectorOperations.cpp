//
// Created by andrey on 24.09.17.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
template <typename T>
T getResidual(vector<T> a,vector<T> b){
    T norm=0;
    for(int i=0;i<a.size();i++){
        norm+=(a[i]-b[i])*(a[i]-b[i]);
    }
    return sqrt(norm);
}

template <typename T>
T getABSResidual(vector<T> a,vector<T> b){
    T norm=0;
    for(int i=0;i<a.size();i++){
        norm+=(abs(a[i])-abs(b[i]))*(abs(a[i])-abs(b[i]));
    }
    return sqrt(norm);
}


template <typename T>
vector<T> multiMatrixVector(vector<vector<T>> m, vector<T> v){
    vector<T> result(v.size());
    for(int i=0;i < m.size(); i++){
        result[i]=0;
        for (int j = 0; j < v.size(); j++) {
            result[i] += m[i][j]*v[j];
        }
    }
    return result;
}

template <typename T>
T normVector(vector<T> v){
    T norm =0;
    for (int i = 0; i <v.size() ; ++i) {
        norm+=v[i]*v[i];
    }
    return sqrt(norm);
}

//cкалярное произведение
template <typename T>
T dotProduct(vector<T> v1, vector<T> v2){
    T result=0.0;
    for(int i=0;i<v1.size();i++){
        result+=v1[i]*v2[i];
    }
    return result;
}


template<typename T>
void printVector(vector<T> v){
    cout<<"vector:"<<endl;
    for (T i : v) {
        cout << i << "    ";
    }
    cout << endl;
}


template <typename T>
void normalizeVector(vector<T> &v){
    T normV=normVector(v);
    for(int i=0;i<v.size();i++){
        v[i]=v[i]/normV;
    }
}

template <typename T>
vector<T> diffVectors(vector<T> v1, vector<T> v2){
    vector<double> res(v1.size());
    for(int i=0;i<v1.size();i++){
        res[i]=abs(v1[i]-v2[i]);
    }
    return res;
}

template <typename T>
T normC(vector<T> v1,vector<T> v2){
    T norm =0;
    auto v = diffVectors(v1,v2);

    for(int i=0;i<v.size();i++){
        if (v[i]>norm){
            norm =v[i];
        }
    }
    return norm;
}