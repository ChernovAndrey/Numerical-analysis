#include <iostream>
#include "Solve.h"
#include "helping/vectorOperations.h"
#include <vector>
using namespace std;


//
//void writingData(vector<double> v, string s){
//    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/LAB9/files/Ui"+s+".txt";
//    ofstream file(pathToFile, ios_base::out | ios_base::trunc);
//    for(int i=0;i<v.size();i++){
//        file<< v[i]<<" ";
//        file<<endl;
//    }
//    file.close();
//}



void writingData(vector<vector<double>> U){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/LAB9/files/Ui.txt";
    ofstream file(pathToFile, ios_base::out | ios_base::trunc);

   // file << "{";
    for (int i = 0; i < U.size(); i++) {
        auto v = U[i];
     //   file << "{ ";
        for (int j = 0; j < v.size(); j++) {
            file << v[j]<<" ";
            if (j!=v.size()-1){
               // file << " ";
            }
        }
       // file << "} ";
    }
   // file << "}"<<endl;
    file.close();

    const string pathToConfig = "/home/andrey/CLionProjects/NumericalMethods/LAB9/files/config.txt";
    ofstream config(pathToConfig, ios_base::out | ios_base::trunc);
    config<<U.size()<<endl;
    config<<U[0].size()<<endl;
    config.close();
}

//лямда равна единице
vector<vector<double>> getAccuracy(double h1, double h2, double x1b, double x1f, double x2b, double x2f, double tf){ //для первого уравнения
    //TODO: размерность на один не совпадает
    auto getSolution = [](double t, double x1,double x2){
        return 1.0;
    };
    vector<vector<double>> U;
    for (double i = x1b; i <= x1f; i+=h1) {
        vector<double> Ui;
        for (double j = x2b; j <= x2f; j+=h2) {
            Ui.push_back( getSolution(tf,i,j) );
        }
        U.push_back(Ui);
    }
    return U;
}


vector<double> getAccuracy2(double h,  double x0, double xf,  double tf){
    auto getSolution = [](double t, double x){
        return (1/sqrt(t))*exp(-x*x/(4*t) );
    };
    vector<double> UAcc;
    for (double i = x0; i <= xf ; i+=h) {
        UAcc.push_back( getSolution(tf,i) );
    }
    return UAcc;
}

int main() {

    double q =2.0;
    double h1=0.2/q;
    double h2=0.2/q;
//    double tau=0.0002/(q*q);  //0.062e-1 -граница сх-ти явного метода  для Ex1
    double tau=0.2/(q);  //0.062e-1 -граница сх-ти явного метода  для Ex1
    double x1b=0.0;
    double x2b=0.0;
    double x1f=1.0;
    double x2f=1.0;
    double t0=0.0;
    double tf=2.0;

    auto * solve = new Solve(h1,h2,tau,x1b,x1f,x2b,x2f,t0,tf);
    auto U = solve->calculate();
   // cout<<U[0][0][0]
    delete solve;
    printMatrix(U[U.size()-1]);
    cout<<"size="<<U.size()<<'\t'<<U[0].size()<<endl;
    writingData(U[U.size()-1]);
//    printMatrix(U[0]);

//    printMatrix(U[1]);


//    cout.precision(16);
//    for(int t=0;t<U.size() ; t++){
//
//        cout<<"area:"<<getArea(U[t],h)<<endl;
//    }

//    cout<<"area first"<<getArea(U[0],h)<<endl;
//
//    auto flagCompare = true;//cравнивать с точным решением, только для тестовой задачи
//
//    if (flagCompare==true){
//
//        cout << "Accuracy" << endl;
//        auto accur = getAccuracyKv(h, x0, xf, tf);
//        printVector(accur);
//        cout<<"Residual:"<<endl;
//        cout<<normVectorC( diffVectors(accur,U[U.size()-1]) );
//    }
    auto UAccur =  getAccuracy(h1,h2,x1b,x1f,x2b,x2f,tf);
    auto ULast = U[U.size()-1] ;
    cout<<"size"<<U[U.size()-1].size()<<" accur "<<UAccur.size();
    cout<<"Resid:"<<getNormMatrix3(ULast)-getNormMatrix3(UAccur);
    return 0;
}
