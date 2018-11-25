//
// Created by zheng yijiang on 11/24/18.
//
#include <iostream>
#include <algorithm>
const int n = 3;
using namespace std;
int main(){
    int val[n] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int K[n+1][W+1]; //K[i][w]: allow to choose i items, and the left bag capacity is w
    int i, w;
    for(i = 0; i <= n; i ++){
        for(w = 0; w <= W; w ++){
            if(i == 0 || w == 0)
                K[i][w] = 0;
            // the former one means with No.i item
            // the later one means without No.i item
            else if(wt[i-1] <= w)
                K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]], K[i-1][w]);
            else
                K[i][w] = K[i-1][w];
        }
    }
    cout << K[n][W] << endl;
    return 0;
}
