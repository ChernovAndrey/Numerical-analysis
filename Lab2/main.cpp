#include <iostream>
#include <vector>
#include <cmath>
#include "sourceMatrices.h"
#include "workWithConsole.h"
#include "matrixOperations.h"
#include "vectorOperations.h"
#include "SimpleIteration.hpp"
#include "MethodJacobi.hpp"
#include "MethodSeidel.hpp"
#include "MethodRelaxation.hpp"
#include "IterativeMethods.hpp"
#include <tuple>
#include "DiagMethodRelaxation.hpp"
#include "DiagMethodSeidel.hpp"

using namespace std;
using number = double;

tuple<vector<vector<number>>, vector<number>,vector<number>> createDiagMatrix() {
    unsigned countDiag = 3;
    unsigned N = 17;//номер варианта
    auto n = 200 + N;
    vector<vector<number>> matrix(n);
    vector<number> b(n);
    for (int i = 0; i < matrix.size(); i++) {
        vector<number> strMatrix(countDiag);//строка матрицы
        strMatrix[0] = 1;
        strMatrix[1] = 4;
        strMatrix[2] = 1;

        if (i == 0) b[i] = 6;
        else {
            if (i == n - 1) b[i] = 9 - 3 * (n % 2);
            else {
                b[i] = 10 - 2   *((i + 1) % 2);
            }
        }

        matrix[i] = strMatrix;
    }
    return make_tuple(matrix,b,vector<number>(n,0));
}
template <typename T>
void printResult(vector<T> v){
    for (int i = 0; i < v.size(); ++i) {
        cout<<v[i]<<" ";
    }
    cout<<'\t';
}

void runAllMethods(){
    number r1 = 0.05;
    number eps[] = {1e-4,1e-7};
    number w[] = {1.04,1.009};
    vector<number> x0(4,0);

    vector<vector<number>> matrix;
    for (double ep : eps) {
        for (int i = 0; i < 2; ++i) {
            if (i == 0) setMatrixEx1(matrix);
            else setMatrixEx2(matrix);
            cout << "при eps=" << ep << endl;
            auto A = getMatrixA(matrix);
            auto b = getVectorB(matrix);
            if (i == 0) {
                cout << "Метод пр. ит.:" << '\t';
                auto resultSimple = IterativeMethods<number>::solveSystem(
                        new SimpleIteration<number>(ep, x0, A, b, r1));
                cout << "Residual=" << getResidual(b, multiMatrixVector(A, resultSimple)) << '\t' << "tau=" << r1
                     << '\t' << "result= ";
                printResult(resultSimple);
                cout << endl;
            }

            cout << "Метод Якоби:" << '\t';
            auto resultJacobi = IterativeMethods<number>::solveSystem(new MethodJacobi<number>(ep, x0, A, b));
            cout << "Residual=" << getResidual(b, multiMatrixVector(A, resultJacobi)) << '\t' << "result= ";
            printResult(resultJacobi);
            cout << endl;

            cout << "Метод Зейделя:" << '\t';
            auto resultSeidel = IterativeMethods<number>::solveSystem(new MethodSeidel<number>(ep, x0, A, b));
            cout << "Residual=" << getResidual(b, multiMatrixVector(A, resultSeidel)) << '\t' << "result= ";
            printResult(resultSeidel);
            cout << endl;

            cout << "Метод релак.:" << '\t';
            auto resultRelax = IterativeMethods<number>::solveSystem(
                    new MethodRelaxation<number>(ep, x0, A, b, w[i]));
            cout << "Residual=" << getResidual(b, multiMatrixVector(A, resultRelax)) << '\t' << "result= ";
            printResult(resultRelax);
            cout << "w=" << w[i] << '\t' << endl;

            cout
                    << "---------------------------------------------------------------------------------------------------------------"
                    << endl;
        }
    }
}

int main() {
  // runAllMethods();
  /* vector<vector<number>>matrix;
    vector<number> b;
    vector<number>x;
    tie(matrix, b,x) = createDiagMatrix();
    printVector(b);
    printVector(IterativeMethods<number>::solveSystem(new DiagMethodRelaxation<number>(0.00001,x,matrix,b,1.05)));
    printVector(IterativeMethods<number>::solveSystem(new DiagMethodSeidel<number>(0.00001,x,matrix,b)));*/

   vector<vector<number>> matrix;
    setMatrixEx3(matrix);

    number r2 = 0.000001;
    number ep = 1e-4;
    vector<number> x0(4,0);

    auto A = getMatrixA(matrix);
    auto b = getVectorB(matrix);

    auto resultSimple = IterativeMethods<number>::solveSystem(
            new SimpleIteration<number>(ep, x0, A, b, r2));
    printVector(resultSimple);

}
