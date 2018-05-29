#include <iostream>
#include "Solve.h"
#include "helping/vectorOperations.h"
#include <vector>
using namespace std;


//
//void writingData(vector<double> v, string s){
//    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab9/files/Ui"+s+".txt";
//    ofstream file(pathToFile, ios_base::out | ios_base::trunc);
//    for(int i=0;i<v.size();i++){
//        file<< v[i]<<" ";
//        file<<endl;
//    }
//    file.close();
//}



void writingData(vector<vector<vector<double>>> U){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab9/files/U.txt";
    ofstream file(pathToFile, ios_base::out | ios_base::trunc);

   // file << "{";
    for (int i = 0; i < U.size(); i++) {
        auto v = U[i];
     //   file << "{ ";
        for (int j = 0; j < v.size(); j++) {
            for (int k = 0; k < v[0].size(); ++k) {
                file << v[j][k] << " ";
            }
        }
    }
    file.close();

    const string pathToConfig = "/home/andrey/CLionProjects/NumericalMethods/Lab9/files/config.txt";
    ofstream config(pathToConfig, ios_base::out | ios_base::trunc);
    config<<U.size()<<endl;
    config<<U[0].size()<<endl;
    config<<U[0][0].size()<<endl;
    config.close();
}

//лямда равна единице
vector<vector<double>> getAccuracy1(double h1, double h2, double x1b, double x1f, double x2b, double x2f, double tf){ //для первого уравнения
    auto getSolution = [](double t, double x1,double x2){
        return 1.0;
    };
    auto eps=1e-7;
    vector<vector<double>> U;
    for (double i = x1b; i <= x1f+eps; i+=h1) {
        vector<double> Ui;
        for (double j = x2b; j <= x2f+eps; j+=h2) {
            Ui.push_back( getSolution(tf,i,j) );
        }
        U.push_back(Ui);
    }
    return U;
}


vector<vector<double>> getAccuracy2(double h1, double h2, double x1b, double x1f, double x2b, double x2f, double tf){ //для первого уравнения
    auto getSolution = [](double t, double x1,double x2){
        return 1.0+x2;
    };
    auto eps=1e-7;
    vector<vector<double>> U;
    for (double i = x2b; i <= x2f+eps; i+=h2) {
        vector<double> Ui;
        for (double j = x1b; j <= x1f+eps; j+=h1) {
            Ui.push_back( getSolution(tf,j,i) );
        }
        U.push_back(Ui);
    }
    return U;
}


vector<vector<double>> getAccuracy3(double h1, double h2, double x1b, double x1f, double x2b, double x2f, double tf){ //для первого уравнения
    auto getSolution = [](double t, double x1,double x2){
        return x1*x1+x2*x2;
    };
    auto eps=1e-7;
    vector<vector<double>> U;
    for (double i = x2b; i <= x2f+eps; i+=h2) {
        vector<double> Ui;
        for (double j = x1b; j <= x1f+eps; j+=h1) {
            Ui.push_back( getSolution(tf,j,i) );
        }
        U.push_back(Ui);
    }
    return U;
}


void writeFile2(vector<vector<double>> U, vector<double> X1, vector<double> X2){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab9/files/U2.txt";
    ofstream file(pathToFile, ios_base::out | ios_base::app);

    for (int j = 0; j < X2.size(); ++j) {
        for (int i = 0; i < X1.size(); ++i) {
            file<< X1[i] << " "<< X2[j] <<" " << U[i][j] <<" ";
        }
    }
    file.close();

}

int main() {

    double q =1.0;
    double h1=0.1/q;
    double h2=0.1/q;
    double tau=0.1;
    double x1b=0.0;
    double x2b=0.0;
    double x1f=1.0;
    double x2f=1.0;
    double t0=0.0;
    double tf=20.0;

    auto * solve = new Solve(h1,h2,tau,x1b,x1f,x2b,x2f,t0,tf);
    auto U = solve->calculate();
   // cout<<U[0][0][0]
    printMatrix(U[U.size()-1]);
    cout<<"size="<<U.size()<<'\t'<<U[0].size()<<endl;
    writingData(U);
    writeFile2(U[0],solve->var->X1,solve->var->X2);

    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab9/files/U2.txt";
    ofstream file(pathToFile, ios_base::out | ios_base::trunc);
    file.close();
    for (int i = 0; i < U.size(); ++i) {
        writeFile2(U[i],solve->var->X1,solve->var->X2);
    }

    delete solve;

    auto UAccur =  getAccuracy3(h1,h2,x1b,x1f,x2b,x2f,tf);
    auto ULast = U[U.size()-1] ;
    cout<<"size"<<U[U.size()-1].size()<<" accur "<<UAccur.size()<<endl;
    cout<<"size"<<U[U.size()-1][0].size()<<" accur "<<UAccur[0].size();


    cout<<"UAccur"<<endl;
    printMatrix(UAccur);
    cout<<"diff finish matrix:"<<endl;
    auto diff = getDiffMatrix(ULast,UAccur);
    printMatrix(diff);
    cout<<"error: "<<getNormMatrix3(diff);
    return 0;
}
