
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
    Params* X;
    Params* S;
    explicit GridParam(Params* X, Params* S):X(X), S(S){}
};


#endif //LAB9_PAR_H
