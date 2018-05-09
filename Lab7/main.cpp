#include <iostream>
#include "Solve.h"
#include "helping/vectorOperations.h"
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

    const string pathToConfig = "/home/andrey/CLionProjects/NumericalMethods/Lab7/files/config.txt";
    ofstream config(pathToConfig, ios_base::out | ios_base::trunc);
    config<<U.size()<<endl;
    config<<U[0].size()<<endl;
    config.close();
}

//лямда равна единице
vector<double> getAccuracy(double h,  double x0, double xf,  double tf){ //для первого уравнения
    auto getSolution = [](double t, double x){
        int n =1;
        double l =1.0;
        auto pi = M_PI;
        auto C1=8/(pow((M_PI),3));
        return C1*exp( -(pi*n/l)*(pi*n/l) * t)*sin( (n*pi*x)/l );
    };
    vector<double> UAcc;
    for (double i = x0; i <= xf ; i+=h) {
        UAcc.push_back( getSolution(tf,i) );
    }
    return UAcc;
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

vector<double> getAccuracyKv(double h,  double x0, double xf,  double tf){  // квазилинейное
    auto getSolution = [](double t, double x){
        double delta = 2.0;
        double kappa0=0.5;
        double c = 5.0 ;
        return  pow((delta*c/kappa0) *(c*t-x),1.0/delta);
    };
    vector<double> UAcc;
    double c = 5.0;
    for (double i = x0; i <= xf ; i+=h) {
        if (i<=c*tf) {
        //    cout<<"i:"<<i<<'\t'<<"c*tf:"<<c*tf<<endl;
            UAcc.push_back(getSolution(tf, i));
        }else{
            return UAcc;
//            UAcc.push_back(0.0);
        }
    }
    return UAcc;
}

double getArea(vector<double> v,double h){
    double area=0.0;
    for (int i=0;i<v.size()-1;i++){
        area+=0.5*(v[i]+v[i+1])*(h);
    }
    return area;
}

int main() {

    double q =1.0;
    double h=0.2/q;
//    double tau=0.0002/(q*q);  //0.062e-1 -граница сх-ти явного метода  для Ex1
    double tau=0.002/(q*q);  //0.062e-1 -граница сх-ти явного метода  для Ex1
    double x0=0.0;
    double xf=10.0;
    double t0=0.0;
    double tf=1.0;

    double sigma = 1.0;
    auto * solve = new Solve(h,tau,x0,xf,t0,tf,sigma);
    auto U = solve->calculate();

    delete solve;
    printMatrix(U);
    cout<<"size="<<U.size()<<'\t'<<U[0].size()<<endl;
    writingData(U);
    printVector(U[0]);
    printVector(U[1]);

    printMaxTMiddle(U);

    cout.precision(16);
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
        return 0;
}
