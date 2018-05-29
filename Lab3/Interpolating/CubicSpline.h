//
// Created by andrey on 22.10.17.
//

#ifndef LAB3_CUBICSPLINE_H
#define LAB3_CUBICSPLINE_H


#include "Interpolate.h"
#include "../helping/workWithConsole.h"
#include "../solveSystem/Sweep.h"

class CubicSpline : public Interpolate {

public:
    double calculateInterpolation(double x) override {
        return a[numberSplit]+b[numberSplit]*(x-xValues[numberSplit])+c[numberSplit]*(x-xValues[numberSplit])*(x-xValues[numberSplit])+
               d[numberSplit]*(x-xValues[numberSplit])*(x-xValues[numberSplit])*(x-xValues[numberSplit]);
    }

    explicit CubicSpline(const pair<vector<double>, vector<double>> &values) : Interpolate(values) {
        tie(a,b,c,d)=getCoefPolinom();
    }


private:
    vector<double> a;
    vector<double> b;
    vector<double> c;
    vector<double> d;


    tuple<vector<double>, vector<double>, vector<double>, vector<double>> getCoefPolinom() {
        vector<double> g(fxValues.size());
        vector<double> h(xValues.size());
        h[0] = 0.0;
        g[0] = 0.0;

        vector<double> a(fxValues.size()-1);
        for(int i=0;i<a.size();i++){
            a[i]=fxValues[i];
        }


        for (int i = 1; i < g.size(); i++) {
            h[i] = xValues[i] - xValues[i - 1];
            g[i] = (fxValues[i] - fxValues[i - 1]) / h[i];
        }
        vector<vector<double>> matrix;
        vector<double> f;
        vector<double> x;
        tie(matrix, f) = createDiagMatrix(h, g);


        auto sweep = new Sweep(matrix,f);
        auto c=sweep->solveSystem();
        delete sweep;
        vector<double> b(fxValues.size()-1);
        vector<double> d(fxValues.size()-1);

        c.push_back(0.0);//временно
        for(int i=0;i<b.size();i++){
            b[i]=g[i+1]-((c[i+1]+2*c[i])*h[i+1])/3;
            d[i]=(c[i+1]-c[i])/(3*h[i+1]);
        }
        c.pop_back();
        a.push_back(fxValues[fxValues.size()-1]);
        return make_tuple(a,b,c,d);
    }


    pair<vector<vector<double>>, vector<double>>
    createDiagMatrix(const vector<double> &h, const vector<double> &g) {
        unsigned countDiag = 3;
        auto n = fxValues.size() - 1;
        vector<vector<double>> matrix(n);
        vector<double> b(n);
        for (int i = 0; i < n; i++) {
            vector<double> strMatrix(countDiag);//строка матрицы
            b[i] = 3 * (g[i + 1] - g[i]);
            strMatrix[0] = h[i];
            strMatrix[1] = 2 * (h[i] + h[i + 1]);

            if (i == n - 1) strMatrix[2] = 0.0;
            else strMatrix[2] = h[i];

            matrix[i] = strMatrix;
        }
        return make_pair(matrix, b);
    }
};

#endif //LAB3_CUBICSPLINE_H
