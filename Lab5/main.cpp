#include <iostream>
#include "Equation.h"
#include "vectorOperations.h"
#include "System.h"

using namespace std;
int main() {
//    double a=0;
//    double b=1;
//    printVector(Equation::execute(a,b,Equation::Newton));

    double a1 = 1;
    double b1 = 10;
    double a2 = 0;
    double b2 = 1.5;

    printVector(System::execute(a1,b1,a2,b2));

    return 0;
}