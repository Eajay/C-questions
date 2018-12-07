//
// Created by WIN7 on 12/7/2018.
//
#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;
const int House_num = 3;
const int Color_num = 5;
int main(){
    int C[House_num][Color_num] ={{2, 1, 3, 2, 3},
                                  {2, 6, 2, 3, 7},
                                  {2, 0, 4, 8, 2}};
    int T[House_num + 1][Color_num + 1];
    // base case
    for(int i = 1; i <= Color_num; i++){
        T[1][i] = C[0][i-1];
    }

    for(int i = 2; i <= House_num; i++){
        for(int j = 1; j <= Color_num; j++){
            T[i][j] = INT_MAX;
            for(int h = 1; h <= Color_num; h++){
                if(h != j){
                    T[i][j] = min(T[i-1][h] + C[i-1][j-1], T[i][j]);
                }
            }
        }
    }
    int result = INT_MAX;
    for(int j = 1; j <= Color_num; j++){
        result = min(T[House_num][j], result);
    }
    cout << result << endl;
    return 0;
}
