//
// Created by andrey on 21.10.17.
//
#include <tuple>
#include <cmath>
double func1(double x){
    return x*x;
}


double func2(double x){
    return 1/(1+x*x);
}

double func3(double x){
    return 1/(atan(1+10*x*x));
}

double func4(double x){
    return pow(4*x*x*x+2*x*x - 4*x+2,sqrt(2))+ asin(1/(5+x-x*x))-5;
}


double func5(double x){
    return 1;
}
double func(double x){  //текущая функция
    return func3(x);
}
