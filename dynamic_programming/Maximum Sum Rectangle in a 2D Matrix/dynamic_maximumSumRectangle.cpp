//
// Created by WIN7 on 12/7/2018.
//
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <string.h>
#define ROW 4
#define COL 5
using namespace std;

// Implementation of Kadane's algorithm for 1D array. The function
// returns the maximum sum and stores starting and ending indexes of the
// maximum sum subarray at addresses pointed by start and finish pointers
// respectively.
int kadane(int *arr, int *start, int *finish, int n){
    int maxSum = arr[0];
    *finish = 0;
    *start = 0;
    int dp[ROW];
    dp[0] = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] > dp[i-1] + arr[i]){
            dp[i] = arr[i];
            if(dp[i] > maxSum){
                maxSum = dp[i];
                *start = *finish = i;
            }
        }
        else{
            dp[i] = dp[i-1] + arr[i];
            if(dp[i] > maxSum){
                maxSum = dp[i];
                *finish = i;
            }
        }
    }
    return maxSum;
}

void findMaxSum(int M[][COL]){
    // Variables to store the final output
    int maxSum = INT_MIN, finalLeft, finalRight, finalTop, finalBottom;
    int left, right, i;
    int temp[ROW] = {0}, sum, start, finish;

    // Set the left column
    for(left = 0; left < COL; left++){
        memset(temp, 0, sizeof(temp));
        for(right = left; right < COL; right++){
            for(i = 0; i < ROW; i++){
                temp[i] += M[i][right];
            }
            // Find the maximum sum subarray in temp[]. The kadane()
            // function also sets values of start and finish.  So 'sum' is
            // sum of rectangle between (start, left) and (finish, right)
            //  which is the maximum sum with boundary columns strictly as
            //  left and right.
            sum = kadane(temp, &start, &finish, ROW);

            // Compare sum with maximum sum so far. If sum is more, then
            // update maxSum and other output values
            if(sum > maxSum){
                maxSum = sum;
                finalLeft = left;
                finalRight = right;
                finalTop = start;
                finalBottom = finish;
            }
        }
    }
    cout << "(Top, Left) " << "( " << finalTop << ", " << finalLeft << ")" << endl;
    cout << "(Bottom, Right) " << "( " << finalBottom << ", " << finalRight << ")" << endl;
    cout << "Max sum is: " << maxSum << endl;
}
int main(){
    int M[ROW][COL] = {{1, 2, -1, -4, -20},
                       {-8, -3, 4, 2, 1},
                       {3, 8, 10, 1, 3},
                       {-4, -1, 1, 7, -6}
                        };
    findMaxSum(M);
    return 0;
}
