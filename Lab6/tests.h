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


vector<double> example2(vector<double> variables) {
    return
            vector<double>({
                                   1- variables.at(0)*variables.at(0)-variables.at(1)*variables.at(1),
                                   2*variables.at(0)
                           });
}



vector<double> example3(vector<double> variables) {
    const double sigma = 10;
    const double r = 10;
    const double b = 8.0/3.0;

    return
            vector<double>({ sigma*(variables[1]-variables[0]),
                             variables[0]*(r-variables[2])-variables[1],
                             variables[0]*variables[1]-b*variables[2]
                           });
}

vector<double> example4(vector<double> variables) {
    const double A =0.4;
    const double B =1.5;
    return
        vector<double>({
                  A - (B+1)*variables[0]+ variables[0]*variables[0]*variables[1],
                  B*variables[0]-variables[0]*variables[0]*variables[1]
                       });
}


vector<double> example5(vector<double> variables,double t) {
    const double sigma =0.1;
    const double nu =0.3;
    const double v =0.5;
    const double M =0.25;
    return
            vector<double>({
                                  variables[1],
                                 M-2*sigma*variables[1] -0.2*(nu+v*sin(t))*sin(variables[0])
                           });
}


vector<double> Func(vector<double> variables, double t) { // pass functions and init variables
   //return basicEx(std::move(variables));
   return example5(std::move(variables),t);

};

vector<double> initVariables() {
    const double eps = 0.0001;
 //  return {0.0+eps,-1.0+eps};
    //return {1.0,0.0};
    return {0.1,0.1};
   // return {1.0,0.0,0.0};
}


#endif //LAB6_TESTS_H