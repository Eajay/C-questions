//
// Created by WIN7 on 11/28/2018.
//
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int longestCommonSubsequence(string s1, string s2){
    int n1 = s1.size();
    int n2 = s2.size();
    int L[n1+1][n2+1]; // L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1]
    for(int i = 0; i <= n1; i++){
        for(int j = 0; j <= n2; j++){
            if(i == 0 || j == 0) L[i][j] = 0;
            else if (s1[i-1] == s2[j-1]) L[i][j] = L[i-1][j-1] + 1;
            else L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }
    // the following code is to get characters
    string sub; // to save the characters
    int i = n1, j = n2;
    while(i > 0 && j > 0){
        //if current chars are the same, then it is part of the sub
        if(s1[i-1] == s2[j-1]){
            sub = s1[i-1] + sub;
            i--;
            j--;
        }
        // If not same, then find the larger of two and
        // go in the direction of larger value
        else if(L[i-1][j] > L[i][j-1]) i--;
        else j--;
    }
    cout << sub << endl;
    return L[n1][n2];
}
int main(){
    string s1 = "AGGTAB";
    string s2 = "X";
    int res = longestCommonSubsequence(s1, s2);
    cout << res << endl;
}
