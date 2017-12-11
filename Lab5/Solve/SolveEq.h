//
// Created by andrey on 11.12.17.
//

#ifndef LAB5_SOLVEEQ_H
#define LAB5_SOLVEEQ_H


class SolveEq {
public:
    double a;
    double b;
    explicit SolveEq(double a, double b):a(a),b(b){}
    virtual double execute()=0;

protected:
    bool compareWithZero(double x){
        return abs(x)<1e-6;
    }
};


#endif //LAB5_SOLVEEQ_H
