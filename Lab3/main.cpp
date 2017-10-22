#include <iostream>
#include "Grid.h"
#include "UniformGrid.h"
#include "Interpolate.h"
#include "Lagrange.h"
#include "ChebyshevGrid.h"


using namespace std;

int main() {
    double a =-1;
    double b =1;
    int n =5;

  //  Grid* grid = new UniformGrid(a,b,n);
    Grid* grid = new ChebyshevGrid(a,b,n);



    Interpolate* interpolate= new Lagrange(grid->get());

    grid->print();

    interpolate->execute();

    return 0;
}