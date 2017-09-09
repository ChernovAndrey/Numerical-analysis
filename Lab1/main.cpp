
//
// Created by andrey on 06.09.17.
//

#include <iostream>
#include<vector>
#include "gauss.h"
#include "sourceMatrices.h"
#include "workWithConsole.h"
#include "QR.h"
using namespace std;



int main() {
    //auto matrix = InputMatrix();
    auto matrix = getMatrixEx4();
    printMatrix(matrix);

   auto result = methodQR(matrix);
    //auto result = methodGauss(matrix);
    if (result.empty()){
        cout<<"matrix degenerate";
    };
    printVector(result);
     result = methodGauss(matrix);
    if (result.empty()){
        cout<<"matrix degenerate";
    };
    printVector(result);

    return 0;
}
