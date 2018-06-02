//
// Created by andrey on 02.06.18.
//

#ifndef LAB10_METHODSINGULAR_H
#define LAB10_METHODSINGULAR_H


class MethodSingular {
public:
    vector<double> solve(EquationsSingular* eq){
        int n = eq->n;
        vector<vector<double>> A(n+1);
        vector<double> f(n+1);

        //первые n уравнений.
        for (int i = 0; i < n; ++i) {
            vector<double> strMatrix(n+1);
            pair<double,double> valueIntegral(0.0,0.0);
            auto k =eq->getCheckPoint(i+1); // так как в формулах от 1 до N
            auto normal = eq->getNormal(k);
            for (int j = 0; j < n; ++j) {
                auto c = eq->getCalcPoint(j+1);  // так как в формулах от 1 до N
                auto q = eq->getKernel(k,c);
                q.first*=eq->arcLen;
                q.second*=eq->arcLen;
                strMatrix[j]=normal.first*q.first + normal.second*q.second; // скалярное произведение
            }
            strMatrix[n] = 1.0;// коэффицент для невязки
            f[i] = eq->getF(i+1);
            A[i] = strMatrix;
        }
        vector<double> lastStrMatrix(n+1);
        for (int l = 0; l < lastStrMatrix.size() - 1; ++l) {
            lastStrMatrix[l] = eq->arcLen;
        }
        lastStrMatrix[n] = 0.0;
        A[n] = lastStrMatrix;
        f[n] = 0.0;
//        printMatrix(A);
        auto result = Gauss::solveSystem(A, f);
        return result;
    }
};


#endif //LAB10_METHODSINGULAR_H
