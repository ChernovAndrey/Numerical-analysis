//
// Created by andrey on 20.10.17.
//

#ifndef LAB3_INTERPOLATE_H
#define LAB3_INTERPOLATE_H

 #include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

class Interpolate {

protected:
    int numberSplit =0;

    const int countPoints=10;//кол-во точек для интерполяции

    vector<double> xValues;
    
    vector<double> fxValues;

public:
    explicit Interpolate(pair<vector<double>,vector<double>> values):xValues(values.first),fxValues(values.second){}

    virtual double calculateInterpolation(double x)=0;//вычислить значение в точке через интерполирование

    double calculateAccurately(double x){
        return func(x);
    }

    void execute(){
        writeValuesInFile(&Interpolate::calculateInterpolation,"/home/andrey/CLionProjects/NumericalMethods/Lab3/files/approx.txt");
        writeValuesInFile(&Interpolate::calculateAccurately,"/home/andrey/CLionProjects/NumericalMethods/Lab3/files/accurate.txt");
    }

private:

    void writeValuesInFile(double (Interpolate::*handlerFunc)(double), const string &fileName){

            ofstream file(fileName,ios_base::out | ios_base::trunc);
            if (file.is_open())
            {

                for(int i=0;i<xValues.size()-1;i++) {
                    numberSplit=i;
                    file<<xValues[i]<<", "<<fxValues[i]<<endl;
                        double h=(xValues[i+1] - xValues[i])/(countPoints+1);
                        for(int j=1;j<=countPoints;j++) {
                            double v = xValues[i]+h*j;
                            file << v << ", " << (this->*handlerFunc)(v) << endl;
                        }
                }
                file<<xValues[xValues.size()-1]<<", "<<fxValues[fxValues.size()-1]<<endl;
                file.close();
            }
           else cout << "Unable to open file";

    };
};


#endif //LAB3_INTERPOLATE_H
