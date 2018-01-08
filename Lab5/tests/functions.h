//
// Created by andrey on 21.10.17.
//

#ifndef LAB5_FUNC_H
#define LAB5_FUNC_H

#include <tuple>
#include <cmath>

const double eps= 1e-6;
double func1(double x){
    return (x-0.1)*(x-0.22)*(x-0.55)*(x-0.7)*(x-0.75);
}

double derivative1(double x){
    return 0.121495 - 1.5119*x + 5.9535*x*x- 9.28*x*x*x + 5*x*x*x*x;
}

double func2(double x){
    return sqrt(x+1)-1;
}

double derivative2(double x){
    return 1/(2*sqrt(1+x));
}

double func3(double x){
    return 35*x*x*x-67*x*x-3*x+3;
}


double func5(double x){
    //return x*x -1;
    return (x-1)*(x-1)*(x-1)*(x-1);
}
double func6(double x){
    return exp(x)-1;
}


double derivative3(double x){
    return -3 - 134*x + 105*x*x;
}



double func(double x){  //текущая функция
    return func2(x);
}

double analyticallyDerivative(double x){
    return derivative1(x);
}


double numericallyDerivative(double x){
    return (func(x+eps)-func(x))/eps;
}

double derivative(double x){
    return numericallyDerivative(x);
}

double secondDerivative(double x){
    return (derivative(x+eps)-derivative(x))/eps;
}
#endif //LAB5_FUNC_H