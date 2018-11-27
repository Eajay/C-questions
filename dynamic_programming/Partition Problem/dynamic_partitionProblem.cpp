//
// Created by WIN7 on 11/27/2018.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

bool findPartition(vector<int> arr){
    int n = arr.size();
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if(sum % 2 != 0) return false;
    sum = sum / 2;
    // like 0-1 knapsack problem, but it is exact value rather than maximum value
    // part[i][j] = true if a subset of {arr[0], arr[1], ..arr[i-1]}
    // has sum equal to j, otherwise false
    bool part[n+1][sum+1];

    int i, j;
    for(j = 1; j <= sum; j++){
        part[0][j] = false; // do not have subset
    }
    for(i = 0; i <= n; i++){
        part[i][0] = true; // we could choose none of them
    }

    for(i = 1; i <= n; i++){
        for(j = 1; j <= sum; j++){
            part[i][j] = part[i-1][j];
            if(!part[i][j] && j >= arr[i-1]){
                part[i][j] = part[i-1][j - arr[i-1]];
            }
        }
    }
    for(i = 0; i <= n ; i++){
        for(j = 0; j <= sum; j++){
            cout << part[i][j] <<" ";
        }
        cout << endl;
    }
    return part[n][sum];
}
int main(){
    vector<int> arr = {3, 1, 1, 2, 2, 1};
    if(findPartition(arr)) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}

