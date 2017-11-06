//
// Created by andrey on 20.10.17.
//

#ifndef LAB3_LAGRANGE_H
#define LAB3_LAGRANGE_H


#include <utility>
#include "Interpolate.h"


class Lagrange : public Interpolate {

public:
    bool firstIterFlag=true;
    explicit Lagrange(pair<vector<double>, vector<double>> values) : Interpolate(std::move(values)) {

    }

private:
    vector<double> C;

    void initC(){
        C= vector<double>(xValues.size());
        for (int k = 0; k < xValues.size(); k++) {
            C[k]=1.0;
            for (int j = 0; j < xValues.size(); j++) {
                if (k != j) C[k] *= 1 / (xValues[k] - xValues[j]);
            }
        }
    }

    double calculateInterpolation(double x) override {
        if(firstIterFlag){
            initC();
            firstIterFlag=false;
        }
        double result = 0.0;
        for (int k = 0; k < xValues.size(); k++) {
            double hx = 1.0;
            for (int j = 0; j < xValues.size(); j++) {
                if (k != j) hx *= (x - xValues[j]);
            }
            result += hx * fxValues[k]*C[k];
        }
        return result;
    }
};


#endif //LAB3_LAGRANGE_H
