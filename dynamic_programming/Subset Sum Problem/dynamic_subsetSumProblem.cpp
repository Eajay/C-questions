//
// Created by WIN7 on 12/7/2018.
//
#include <iostream>
#include <algorithm>
const int N = 6;
using namespace std;
bool isSubsetSum(int set[], int n, int sum){
    // The value of subset[i][j] will be true if there is a
    // subset of set[0..i-1] with sum equal to j
    bool subset[n+1][sum+1];

    // case subset[0][0] = true
    for(int i = 0; i <= n; i++){
        subset[i][0] = true;
    }
    for(int j = 1; j <= sum; j++){
        subset[0][j] = false;
    }

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= sum; j++){
            if(j<set[i-1]) subset[i][j] = subset[i-1][j];
            else{
                subset[i][j] = subset[i-1][j] || subset[i-1][j-set[i-1]];
            }
        }
    }
    return subset[n][sum];
}
int main(){
    int set[] = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    cout << isSubsetSum(set, N, sum);
    return 0;
}
