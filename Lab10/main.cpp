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


void writeFile(vector<double> U, vector<double> X){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab10/files/U2.txt";
    ofstream file(pathToFile, ios_base::out | ios_base::app);

        for (int i = 0; i < X.size(); ++i) {
            file<< X[i] <<" " << U[i] <<" ";
        }

    file.close();

}

int main() {

//    double h=0.11;
//    double h=0.075;
    double a = 0.0;
    double b = 1.0;

    int nx = 22;
    double h = (b-a)/(nx-1);
    double as=a;
    double bs=b;
    double hs=h;
    int ns = nx;

//    auto *solve = new Solve(h,a,b,hs,as,bs);
    auto *solve = new Solve(h,a,nx,hs,as,ns);
    auto U = solve->calculate();
    printVector(U);
    writeFile(U,solve->var->X);
    delete solve;
    return 0;
}
