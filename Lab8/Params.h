
// Created by andrey on 08.04.18.
//

#ifndef LAB7_PAR_H
#define LAB7_PAR_H


struct Params {  //объект, который содержит начало, шаг и кол-во шагов какой-либо переменной
public:
    Params(double start,double step, int n):start(start),step(step),n(n){}
    double start;
    double step;
    int n; //кол-во шагов
};

struct GridParam{
public:
    Params* X;
    Params* T;
    GridParam(Params* X, Params* T):X(X), T(T){}
};


#endif //LAB7_PAR_H
