//
// Created by andrey on 28.02.18.
//
#ifndef LAB6_TESTS_H
#define LAB6_TESTS_H

#include <utility>
#include <vector>

using namespace std;


vector<double> basicEx(vector<double> variables) { //шарик с пружиной
    const double k = 20;
    const double m = 0.3;
    return
            vector<double>({
                                   variables.at(1),
                                   (-k / m) * variables.at(0)
                           });
}

vector<double> F(vector<double> variables) { // pass functions and init variables
    return basicEx(std::move(variables));

};

vector<double> initVariables() {
    return {1.0,0.0};
}


#endif //LAB6_TESTS_H