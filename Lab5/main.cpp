#include <iostream>
#include "Equation.h"
#include "vectorOperations.h"

using namespace std;
int main() {
    double a=-1;
    double b=10;
    printVector(Equation::execute(a,b,Equation::Newton));
    return 0;
}