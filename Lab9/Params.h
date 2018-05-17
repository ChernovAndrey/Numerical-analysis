
// Created by andrey on 08.04.18.
//

#ifndef LAB9_PAR_H
#define LAB9_PAR_H


struct Params {  //объект, который содержит начало, шаг и кол-во шагов какой-либо переменной
public:
    Params(double start,double step, int n):start(start),step(step),n(n){}
    double start;
    double step;
    int n; //кол-во шагов
};

struct GridParam{
public:
    Params* X1;
    Params* X2;
    Params* T;
    GridParam(Params* X1, Params* X2, Params* T):X1(X1),X2(X2), T(T){}
};


#endif //LAB9_PAR_H
