//
// Created by WIN7 on 11/22/2018.
//
#include <iostream>
#include <vector>
#include <algorithm>
const int N = 6;
using namespace std;
int main(){
    int value[N] = {20, 30, 2, 2, 2, 10};
    int F[N][N] = {0};
    //base cases
    for(int i = 0; i < N - 1; i ++){
        F[i][i] = value[i];
        F[i][i+1] = max(value[i], value[i+1]);
    }
    F[N-1][N-1] = value[N-1];
    for(int gap = 2; gap < N ; gap ++){
        for(int i = 0; i + gap < N; i ++){
            int j = i + gap;
            F[i][j] = max(value[i] + min(F[i+2][j], F[i+1][j-1]),
                    value[j] + min(F[i+1][j-1], F[i][j-2]));
        }
    }
    cout << F[0][N-1] << endl;
    return 0;
}
