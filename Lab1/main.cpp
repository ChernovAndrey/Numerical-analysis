
//
// Created by andrey on 06.09.17.
//

#include <iostream>
#include<vector>
#include "gauss.h"
#include "sourceMatrices.h"
#include "QR.h"
using namespace std;

int main() {

     vector<vector<float>> matrix;//поменять константу если меняешь тип, а в плюсах есть рефлексия?
//   matrix = ReadFile(matrix,1);
    getMatrixEx4(matrix);// return double
//    printMatrix(matrix);
    //printMatrix(matrix);

  /*  auto result = methodQR(matrix);
    if (result.empty()){
        cout<<"matrix degenerate";
    }else {
        printVector(result);
    }*/
    auto result = methodQR(matrix);
   if (result.empty()){
        cout<<"matrix degenerate";
    }else {
       printVector(result);
   }
    return 0;
}
