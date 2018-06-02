//
// Created by andrey on 02.06.18.
//

#ifndef LAB10_SOLVESINGULAR_H
#define LAB10_SOLVESINGULAR_H


#include "Equations.h"
#include "MethodSingular.h"

// решаем только на единичной окружности.
class SolveSingular {
public:
    explicit SolveSingular(int n){
        equations= new EquationsSingular(n);
    }
    EquationsSingular *equations;
    MethodSingular *method= new MethodSingular();

    vector<double> calculate() {
        return method->solve(equations);

    }

};


#endif //LAB10_SOLVESINGULAR_H
