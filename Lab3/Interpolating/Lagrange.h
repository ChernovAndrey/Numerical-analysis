//
// Created by andrey on 20.10.17.
//

#ifndef LAB3_LAGRANGE_H
#define LAB3_LAGRANGE_H


#include <utility>
#include "Interpolate.h"


class Lagrange : public Interpolate {

public:
    explicit Lagrange(pair<vector<double>, vector<double>> values) : Interpolate(std::move(values)) {

    }

private:

    double calculateInterpolation(double x) override {
        double result = 0.0;
        for (int k = 0; k < xValues.size(); k++) {
            double Ck = 1.0;
            for (int j = 0; j < xValues.size(); j++) {
                if (k != j) Ck *= (x - xValues[j]) / (xValues[k] - xValues[j]);
            }
            result += Ck * fxValues[k];
        }
        return result;
    }
};


#endif //LAB3_LAGRANGE_H
