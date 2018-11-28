//
// Created by WIN7 on 11/28/2018.
//
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

//based on longestCommonSubsequence

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
    return L[n1][n2];
}

int shortestCommonSupersequence(string s1, string s2){
    // Length of the shortest supersequence  = (Sum of lengths of given two strings) -
    // (Length of LCS of two given strings)
    return (s1.size() + s2.size() - longestCommonSubsequence(s1, s2) );
}
int main(){
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";
    int res = shortestCommonSupersequence(s1, s2);
    cout << res << endl;
}
