#include <iostream>
#include "Grids/Grid.h"
#include "Grids/UniformGrid.h"
#include "Interpolating/Interpolate.h"
#include "Interpolating/Lagrange.h"
#include "Grids/ChebyshevGrid.h"
#include "Interpolating/CubicSpline.h"
#include "solveSystem/Sweep.h"


using namespace std;

void runAll() {
    string path = "/home/andrey/CLionProjects/NumericalMethods/Lab3/files/";
    int i = 1;
    int n = 10;
    double a = -1;
    double b = 1;
    while (i <= 3) {
        if (i == 1) n = 5;
        if (i == 2) n = 10;
        if (i == 3) n = 100;

        cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
        Grid *grid = new UniformGrid(a, b, n);
        Interpolate *interpolate = new Lagrange(grid->get());
        cout << "grid:" << endl;
        grid->print();
        interpolate->execute(path+"approx"+"LU"+to_string(i)+".txt",path+"accur"+"LU"+to_string(i)+".txt");
        cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;

        grid = new ChebyshevGrid(a, b, n);
        interpolate = new Lagrange(grid->get());
        cout << "grid:" << endl;
        grid->print();
        interpolate->execute(path+"approx"+"LC"+to_string(i)+".txt",path+"accur"+"LC"+to_string(i)+".txt");
        cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;

        grid = new UniformGrid(a, b, n);
        interpolate = new CubicSpline(grid->get());
        cout << "grid:" << endl;
        grid->print();
        interpolate->execute(path+"approx"+"CUB"+to_string(i)+".txt",path+"accur"+"CUB"+to_string(i)+".txt");
        cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;


        i++;
    }
}


int main() {
    double a = -1;
    double b = 1;
    int n = 11;

    //Grid* grid = new UniformGrid(a,b,n);
    //  Grid* grid = new ChebyshevGrid(a,b,n);


    int i=3;
    cout<< to_string(3);

   runAll();

    //Interpolate* interpolate= new Lagrange(grid->get());
    // Interpolate* interpolate= new CubicSpline(grid->get());

    // cout<<"grid:"<<endl;
    //  grid->print();

    // interpolate->execute();

    //  auto pair = createDiagMatrix();

    // printVector((new Sweep(pair.first,pair.second))->solveSystem());

    return 0;
}