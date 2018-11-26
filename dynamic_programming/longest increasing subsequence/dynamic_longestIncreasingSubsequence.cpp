//
// Created by WIN7 on 11/26/2018.
//
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 6;
int main(){
    int a[N] = {50, 3, 10, 7, 40, 80};
    int M[N];
    for(int i = 0; i < N; i ++){
        M[i] = 1;
        for(int j = 0; j < i; j ++){
            if(a[j] < a[i] && M[i] < M[j] + 1){
                M[i] = M[j] + 1;
            }
        }
    }
    cout << *max_element(M, M + N) << endl;
    return 0;
}
