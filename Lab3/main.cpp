#include <iostream>
#include "Grids/Grid.h"
#include "Grids/UniformGrid.h"
#include "Interpolating/Interpolate.h"
#include "Interpolating/Lagrange.h"
#include "Grids/ChebyshevGrid.h"
#include "Interpolating/CubicSpline.h"
#include "solveSystem/Sweep.h"


using namespace std;


int main() {
    double a =-1;
    double b =1;
    int n =14;

    Grid* grid = new UniformGrid(a,b,n);
  //  Grid* grid = new ChebyshevGrid(a,b,n);



  // Interpolate* interpolate= new Lagrange(grid->get());
    Interpolate* interpolate= new CubicSpline(grid->get());

    cout<<"grid:"<<endl;
    grid->print();

    interpolate->execute();

 //   auto pair = createDiagMatrix();

   // printVector((new Sweep(pair.first,pair.second))->solveSystem());

    return 0;
}