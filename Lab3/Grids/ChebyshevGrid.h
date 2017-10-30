//
// Created by andrey on 22.10.17.
//

#ifndef LAB3_CHEBYSHEVGRID_H
#define LAB3_CHEBYSHEVGRID_H


#include "Grid.h"
#include <cmath>
class ChebyshevGrid : public Grid {

public:
    ChebyshevGrid(double a, double b, int n) : Grid(a, b, n) {}

protected:
    double getXi(double a, double b, int n, double h, int i) override {
        double argCos=(M_PI*(2*i+1))/(2*n+1);
        return (a+b)/2.0 + ((b-a)/2.0*cos(argCos));
    }
};


#endif //LAB3_CHEBYSHEVGRID_H
