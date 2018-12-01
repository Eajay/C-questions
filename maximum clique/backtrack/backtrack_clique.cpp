//
// Created by WIN7 on 12/1/2018.
//
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
const int MAX_v = 50;
using namespace std;
typedef struct {
    int a[MAX_v][MAX_v]; // store the map
    int v; // vertex
    int x[50]; // connection between vertex and current clique
    int bestx[50]; // current best solution, for print the solution
    int cnum; // current clique number
    int bestn; // biggest clique number
}MPC;

// i: tree depth or the order of node
void Backtrack(MPC &G, int i){
    // this branch is over
    // when we can get to this step means cnum larger than former bestn
    if(i > G.v){
        for(int j = 1; j <= G.v; j++){
            G.bestx[j] = G.x[j];
        }
        cout << G.cnum << endl;
        G.bestn = G.cnum;
        return ;
    }
    // check current point i's connection with current clique
    // OK for left branch
    int OK = 1;
    for (int j = 1; j < i; j++){
        // G.x[j] = 1 means node j in the current clique
        if(G.x[j] && G.a[i][j] == 0){
            OK = 0;
            break;
        }
    }
    if(OK){
        G.x[i] = 1; // add node i into current clique
        G.cnum++;
        Backtrack(G, i + 1);
        // after this branch, we have to recover the parameters
        G.x[i] = 0;
        G.cnum--;
    }
    // for right branch
    if(G.cnum + G.v - i > G.bestn){
        G.x[i] = 0; // without node i
        Backtrack(G, i + 1);
    }
}
int main(){
    MPC G;
    G.cnum = 0;
    G.v = 6;
    G.x[MAX_v] = 0;
    G.bestn = 0;
    int edge1[] = {1, 2, 3, 4, 1, 1, 2, 1, 4, 5};
    int edge2[] = {2, 3, 5, 5, 4, 5, 5, 6, 6, 6};
    for(int i = 0; i < 10; i ++){
        G.a[edge1[i]][edge2[i]] = (G.a[edge2[i]][edge1[i]] = 1);
    }
    Backtrack(G, 1);
    cout << G.bestn << endl;
    return 0;
}
