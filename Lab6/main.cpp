#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef double (*F) (vector<double> variables);

void check(F functions[]){
    cout<< functions[0]({0,3})<<endl;
    cout<< functions[1]({0.3,3})<<endl;
}

const double t0=0.0;
void Euler(F functions[],vector<double> variables){//pass initVariables
    double tau =0.01;
    int n =20;
    double t =t0;

    vector<vector<double>> Y(variables.size());
    for(int i=0;i<variables.size();i++){
        Y[i].push_back(variables[i]);
    }

    for(int i=1;i<n;i++) {
        vector<double> nVariables(variables.size());
        for (int j = 0; j < Y.size(); j++) {
            Y[j].push_back(variables.at(j) + tau*functions[j](variables)); // сейчас кол-во элементов равно i
            nVariables[j]=Y[j][i];
            t+=tau;
        }
        variables=nVariables;
    }

    for(int i=0;i<Y.size();i++){
        for(int j=0;j<Y[0].size();j++){
            cout<<Y[i][j]<<" ";
        }
        cout<<endl;
    }

}

int main(){
    F functions[]={
            [](vector<double> variables){// шарик на пружине
                return variables.at(1);
            },
            [](vector<double> variables){
                const double k = 20;
                const double m =0.3;
                const double to =0.0;
                return (-k/m)*variables.at(0);
            }
    };
    check(functions);
    Euler(functions,{1,0});
    return 0;
}
