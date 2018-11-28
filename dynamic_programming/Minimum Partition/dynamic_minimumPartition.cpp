//
// Created by WIN7 on 11/27/2018.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

int minPatition(vector<int> arr){
    int n = arr.size();
    int sum = accumulate(arr.begin(), arr.end(), 0);
    // like 0-1 knapsack problem, but it is exact value rather than maximum value
    // dp[i][j] = true if a subset of {arr[0], arr[1], ..arr[i-1]}
    // has sum equal to j, otherwise false
    bool dp[n+1][sum+1];

    int i, j;
    for(j = 1; j <= sum; j++){
        dp[0][j] = false; // do not have subset
    }
    for(i = 0; i <= n; i++){
        dp[i][0] = true; // we could choose none of them
    }

    for(i = 1; i <= n; i++){
        for(j = 1; j <= sum; j++){
            dp[i][j] = dp[i-1][j];
            if(!dp[i][j] && j >= arr[i-1]){
                dp[i][j] = dp[i-1][j - arr[i-1]];
            }
        }
    }
    int res;
    for(j = sum / 2; j >= 0; j--){
        if(dp[n][j]){
            // only consider (j <= sum - j) => (j <= sum / 2)
            // because j and sum - j are mutual, we only need to consider one case
            // therefore res is positive number
            res = sum - 2*j;
            break;
        }
    }

    return res;
}
int main(){
    vector<int> arr = {3, 1, 4, 2, 2, 100};
    cout << minPatition(arr) << endl;
    return 0;
}

