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
#include "../helping/vectorOperations.h"

using namespace std;

class Interpolate {

protected:
    int numberSplit = 0;

    const int countPoints = 10;//кол-во точек для интерполяции

    vector<double> xValues;

    vector<double> fxValues;

    vector<double> ResidualExp;//невязка экспоненты в точке 2.2

public:
    explicit Interpolate(pair<vector<double>, vector<double>> values) : xValues(values.first),
                                                                        fxValues(values.second) {}

    virtual double calculateInterpolation(double x)=0;//вычислить значение в точке через интерполирование

    double calculateAccurately(double x) {
        return func(x);
    }

    void execute(const string &filenameApprox, const string &filenameAccur) {
        if (flagExtraPolate) {
            cout << "ExtraPolate:" << endl;
        }
        writeValuesInFile(&Interpolate::calculateInterpolation, filenameApprox, 1);
        if (flagExtraPolate) {
            cout << "AccurateValue:" << endl;
        }
        writeValuesInFile(&Interpolate::calculateAccurately, filenameAccur, 2);

        if (flagExtraPolate) {
            if (ResidualExp.size() == 2) {
                cout << "ResidualExp:" << abs(ResidualExp[1] - ResidualExp[0]) << endl;
            }
        }

        cout << "Residual in node Grid:" << endl;
        for (int i = 0; i < xValues.size(); i++) {
            numberSplit = i;
            cout << abs(calculateInterpolation(xValues[i]) - fxValues[i]) << " ";
        }
        cout << endl;

        cout << "Residual in node Interpolate:" << endl;
        double max=-1;
        for (int i = 0; i < MvalAccur.size(); i++) {
            for (int j = 0; j < MvalAccur[i].size(); j++) {
                if(max< abs(MvalAccur[i][j] - MvalInter[i][j])) max =  abs(MvalAccur[i][j] - MvalInter[i][j]);
                cout << abs(MvalAccur[i][j] - MvalInter[i][j]) << " ";
            }
        }
        cout<<endl;
        cout<<"max="<<max;
        cout << endl;

    }


private:
    vector<vector<double>> MvalAccur;
    vector<vector<double>> MvalInter;
    vector<double> valAccur;
    vector<double> valInter;
    bool flagExtraPolate = false;
    int countExtra = 5;//кол-во точек экстраполяции с каждой стороны
    double hExtra = 0.2;

    void writeValuesInFile(double (Interpolate::*handlerFunc)(double), const string &fileName, int flag) {

        ofstream file(fileName, ios_base::out | ios_base::trunc);
        if (file.is_open()) {
            if (flagExtraPolate) {
                for (int i = 1; i <= countExtra; i++) {
                    double v = xValues[0] - hExtra * i;
                    cout << "при x=" << v << " " << "f(x)=" << (this->*handlerFunc)(v) << endl;
                    file << v << ", " << (this->*handlerFunc)(v) << endl;
                }
            }

            for (int i = 0; i < xValues.size() - 1; i++) {
                numberSplit = i;
                file << xValues[i] << ", " << fxValues[i] << endl;
                double h = (xValues[i + 1] - xValues[i]) / (countPoints + 1);
                valAccur.clear();
                valInter.clear();
                for (int j = 1; j <= countPoints; j++) {
                    double v = xValues[i] + h * j;
                    file << v << ", " << (this->*handlerFunc)(v) << endl;
                    if (flag == 1) valInter.push_back((this->*handlerFunc)(v));
                    if (flag == 2) valAccur.push_back((this->*handlerFunc)(v));
                }
                if (flag == 1) MvalInter.push_back(valInter);
                if (flag == 2) MvalAccur.push_back(valAccur);
            }


            file << xValues[xValues.size() - 1] << ", " << fxValues[fxValues.size() - 1] << endl;
            // file<<xValues[xValues.size()-1]<<", "<<((this->*handlerFunc)(fxValues[fxValues.size()-1]))<<endl;

            if (flagExtraPolate) {
                for (int i = 1; i <= countExtra; i++) {
                    double v = xValues[xValues.size() - 1] + hExtra * i;
                    if (v == 2.2) ResidualExp.push_back((this->*handlerFunc)(v));
                    cout << "при x=" << v << " " << "f(x)=" << (this->*handlerFunc)(v) << endl;
                    file << v << ", " << (this->*handlerFunc)(v) << endl;
                }
            }

            file.close();
        } else cout << "Unable to open file";

    };
};


#endif //LAB3_INTERPOLATE_H
