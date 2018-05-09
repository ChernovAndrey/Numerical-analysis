#include <iostream>
#include "Solve.h"
using namespace std;

void writingData(vector<vector<double>> U){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab8/files/Ui.txt";
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

    const string pathToConfig = "/home/andrey/CLionProjects/NumericalMethods/Lab8/files/config.txt";
    ofstream config(pathToConfig, ios_base::out | ios_base::trunc);
    config<<U.size()<<endl;
    config<<U[0].size()<<endl;
    config.close();
}


vector<double> getAccuracy1(double h,  double x0, double xf,  double tf){ //для первого уравнения
    auto getSolution = [](double t, double x){
        auto pi = M_PI;
        return sin(pi*x)*cos(pi*t);
    };
    vector<double> UAcc;
    for (double i = x0; i <= xf ; i+=h) {
        UAcc.push_back( getSolution(tf,i) );
    }
    return UAcc;
}


int main() {

    double q =1.0;
    double h=0.01/q;
    double tau=0.01/q;
    double x0=0.0;
    double xf=1.0;
    double t0=0.0;
    double tf=0.2;

    auto * solve = new Solve(h,tau,x0,xf,t0,tf);
    auto U = solve->calculate();
    delete solve;
    printMatrix(U);
    cout<<"size="<<U.size()<<'\t'<<U[0].size()<<endl;
    writingData(U);
    cout<<"U0:"<<endl;
    printVector(U[0]);
    cout<<"U1:"<<endl;
    printVector(U[1]);


    auto flagCompare = true;//cравнивать с точным решением

    if (flagCompare==true){

        cout << "Accuracy" << endl;

        auto accur0 = getAccuracy1(h, x0, xf, 0);
        cout<<"accur0:"<<endl;
        printVector(accur0);

        auto accur1 = getAccuracy1(h, x0, xf, tau);
        cout<<"accur1:"<<endl;
        printVector(accur1);

        auto accur = getAccuracy1(h, x0, xf, tf);
        printVector(accur);
        cout<<"Residual:"<<endl;
        cout<<normVectorC( diffVectors(accur,U[U.size()-1]) );
    }

    return 0;
}