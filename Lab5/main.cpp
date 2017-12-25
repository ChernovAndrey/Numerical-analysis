#include <iostream>
#include "Equation.h"
#include "vectorOperations.h"
#include "System.h"

using namespace std;
int main() {
//    double a=0;
//    double b=1;
//    Equation::execute(a,b,Equation::Newton, func);

//    //для кратных корней
//    auto res =Equation::execute(a,b,Equation::Newton, derivative);
//    cout<<"roots:"<<endl;
//    for(int i=0;i<res.size();i++){
//        if(SolveEq::compareWithZero(func(res[i]))){
//            cout<<res[i]<<endl;
//        }
//    }

    double a1 = -10;
    double b1 = 10;
    double a2 = -10;
    double b2 = 10;

    printVector(System::execute(a1,b1,a2,b2));

    return 0;
}