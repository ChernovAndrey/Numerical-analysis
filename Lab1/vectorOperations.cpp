//
// Created by andrey on 24.09.17.
//
template <typename T>
T getResidual(vector<T> a,vector<T> b){
    T norm=0;
    for(int i=0;i<a.size();i++){
        norm+=(a[i]-b[i])*(a[i]-b[i]);
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
    cout<<"norm="<<norm<<endl;
    return sqrt(norm);
}

template<typename T>
void printVector(vector<T> v){
    cout<<"vector:"<<endl;
    for (T i : v) {
        cout << i << "    ";
    }
    cout << endl;
}