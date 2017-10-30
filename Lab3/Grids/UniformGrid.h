//
// Created by andrey on 20.10.17.
//

#ifndef LAB3_UNIFORMGRID_H
#define LAB3_UNIFORMGRID_H


#include "Grid.h"

class UniformGrid : public Grid{
public:
    UniformGrid(double a, double b, int n) : Grid(a, b, n) {}

protected:
    double getXi(double a, double b, int n, double h, int i) override {
       return a+h*i;
    }
};


#endif //LAB3_UNIFORMGRID_H
