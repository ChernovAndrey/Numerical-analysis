//
// Created by andrey on 28.02.18.
//
#ifndef LAB6_TESTS_H
#define LAB6_TESTS_H

#include <utility>
#include <vector>

using namespace std;

//параметры для уравнения колебаний мат маятника
const double getK(){return 20.0;} //k
const double getM(){return 0.3;} //m

vector<double> basicEx(vector<double> variables) { //шарик с пружиной
    const double k = getK();
    const double m = getM();
    return
            vector<double>({
                                   variables.at(1),
                                   (-k / m) * variables.at(0)
                           });
}


vector<double> example1(vector<double> variables) {
    return
            vector<double>({
                                   2*variables.at(0)+variables.at(1)*variables.at(1)-1,
                                   6*variables.at(0) - variables.at(1)*variables.at(1)+1
                           });
}

//ответ на шарик с пружинкой ( cos(wt))
double getAnswerEx1(double t){
    const double k = getK();
    const double m = getM();
    const double omega = sqrt(k/m);
    return cos(omega*t);
}


vector<double> example2(vector<double> variables) { //шарик с пружиной
    return
            vector<double>({
                                   1- variables.at(0)*variables.at(0)-variables.at(1)*variables.at(1),
                                   2*variables.at(0)
                           });
}



vector<double> example3(vector<double> variables) { //шарик с пружиной
    const double sigma = 10;
    const double r = 10;
    const double b = 8.0/3.0;

    return
            vector<double>({ sigma*(variables[1]-variables[0]),
                             variables[0]*(r-variables[2])-variables[1],
                             variables[0]*variables[1]-b*variables[2]
                           });
}

vector<double> Func(vector<double> variables, double t) { // pass functions and init variables
   return basicEx(std::move(variables));
   //return example2(std::move(variables));

};

vector<double> initVariables() {
    const double eps = 0.01;
  //  return {0.0+eps,1.0+eps};
    return {1.0,0.0};
   // return {1.0,0.0,0.0};
}


#endif //LAB6_TESTS_H