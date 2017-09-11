
//
// Created by andrey on 06.09.17.
//

#include <iostream>
#include<vector>
#include <fstream>
#include "gauss.h"
#include "sourceMatrices.h"
#include "QR.h"
using namespace std;

int main() {

     vector<vector<double>> matrix;//поменять константу если меняешь тип, а в плюсах есть рефлексия?
   matrix = ReadFile(matrix,1);
//    getMatrixEx4(matrix);// return double
    printMatrix(matrix);
    //printMatrix(matrix);

    auto result = methodQR(matrix);
    //auto result = methodGauss(matrix);
    if (result.empty()){
        cout<<"matrix degenerate";
    };
    printVector(result);
    result = methodGauss(matrix);
   if (result.empty()){
        cout<<"matrix degenerate";
    }else {
       printVector(result);
   }
    return 0;
}
