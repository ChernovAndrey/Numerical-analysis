#include <iostream>
#include "Solve.h"
#include <vector>
using namespace std;


//
//void writingData(vector<double> v, string s){
//    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab7/files/Ui"+s+".txt";
//    ofstream file(pathToFile, ios_base::out | ios_base::trunc);
//    for(int i=0;i<v.size();i++){
//        file<< v[i]<<" ";
//        file<<endl;
//    }
//    file.close();
//}



void writingData(vector<vector<double>> U){
    const string pathToFile = "/home/andrey/CLionProjects/NumericalMethods/Lab7/files/Ui.txt";
    ofstream file(pathToFile, ios_base::out | ios_base::trunc);

    file << "{";
    for (int i = 0; i < U.size(); i++) {
        auto v = U[i];
        file << "{ ";
        for (int j = 0; j < v.size(); j++) {
            file << v[j]<<" ";
            if (j!=v.size()-1){
               // file << " ";
            }
        }
        file << "} ";
    }
    file << "}"<<endl;
    file.close();
}

//лямда равна единице
vector<double> getAccuracy(double h,  double x0, double xf,  double tf){ //для первого уравнения
    auto getSolution = [](double t, double x){
        auto C1=0.2;
        auto C2=C1*(1- cos(1.0))/( sin(1) );
        return exp(-t)*( C1*cos(x) + C2*sin(x) ) ;
    };
    vector<double> UAcc;
    for (double i = x0; i <= xf ; i+=h) {
        UAcc.push_back( getSolution(tf,i) );
    }
    return UAcc;
}
void printMaxTMiddle(vector<vector<double>> U){
    double max =0.0;
    auto imid= static_cast<int>(U[0].size() / 2);

    for (auto && el :U ) {
        if (el[imid]>max){
            max=el[imid];
        }
    }
    cout <<"max="<<max<<endl;
}


int main() {

    double h=0.25;
    double tau=0.002;  //0.062e-1 -граница сх-ти явного метода  для Ex1
    double x0=0;
    double xf=1;
    double t0=0.0;
    double tf=0.5;

    double sigma = 0.5;
    Solve* solve = new Solve(h,tau,x0,xf,t0,tf,sigma);
    auto U = solve->calculate();
    delete solve;
    printMatrix(U);
    cout<<"size="<<U.size()<<'\t'<<U[0].size()<<endl;
     writingData(U);
//    writingData(U[50],"2");
//    writingData(U[100],"3");
//    writingData(U[200],"4");
    printVector(U[0]);
    printVector(U[1]);

    printMaxTMiddle(U);

//    cout<<"Accuracy"<<endl;
//    printVector(getAccuracy(h,x0,xf,tf));
    return 0;
}
