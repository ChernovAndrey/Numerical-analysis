//
// Created by andrey on 21.10.17.
//


double func1(double x){
    return x*x;
}


double func2(double x){
    return 1/(1+x*x);
}

double func(double x){  //текущая функция
    return func2(x);
}