#include <iostream>
#include <vector>
using namespace std;
//
// Created by andrey on 06.09.17.
//


vector<vector<double >> getMatrixEx1(){
    return {
            {1, 1, 1, 1, 4},
            {0, 1, 1, 1, 3},
            {0, 0, 1, 1, 2},
            {0, 0, 0, 1, 1}
    };
}

vector<vector<double >> getMatrixEx2(){
    return {
            {0, 0, 0, 1, 1},
            {0, 0, 1, 1, 2},
            {0, 1, 1, 1, 3},
            {1, 1, 1, 1, 4}
    };
}


vector<vector<double >> getMatrixEx3(){
    return {
            {1, 1, 1, 1, 4},
            {2, 3, 3, 3, 11},
            {2, 4, 4, 4, 15},
            {4, 5, 6, 7, 22}
    };
}

vector<vector<double >> getMatrixEx4(){
    return {
            {10, 6, 2, 0, 25},
            {5, 1, -2, 4, 14},
            {3, 5, 1, -1, 10},
            {0, 6, -2, 2, 8}
    };
}

vector<vector<double >> getMatrixEx5(){
    return {
            {28.859, -0.008, 2.406, 19.240, 30.459},
            {14.436, -0.001, 1.203, 9.624, 18.248},
            {120.204, -0.032, 10.024, 80.144, 128.156},
            {-57.714, 0.016, -4.812, -38.478, -60.908}
    };
}

