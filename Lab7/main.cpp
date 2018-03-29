#include <iostream>
#include "Solve.h"

using namespace std;

int main() {

    double h=0.1;
    double tau=0.1;
    double x0=0;
    double xf=1;
    double t0=0.5;
    double tf=1;

    auto solve = new Solve(h,tau,x0,xf,t0,tf);
    auto U = solve->calculateExplicit();
    printMatrix(U);

    delete solve;
    return 0;
}
