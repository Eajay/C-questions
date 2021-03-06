//
// Created by WIN7 on 11/17/2018.
//
//create a DFS tree
//1) u is root of DFS tree and it has at least two children
//2) u is not root of DFS and it has a child v such that no vertex in
//   subtree rooted with v has a back edge to one of the ancestors of u
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <windows.h>
uint64_t rdtsc(){
    return __rdtsc();
}

const int NIL = -1;
using namespace std;

class Graph{
    int V; //number of vertices
    list<int> *adj; //a dynamic array of adjacency lists
    void APUtil(int v, bool visited[], int disc[], int low[], int parent[], bool ap[]);

public:
    Graph(int V); //Constructor
    void addEdge(int v, int w);
    void add(int v, int w);
    void AP(); // print articulate points

};

Graph::Graph(int V){
    this->V = V;
    adj = new list<int>[V];
}
// un-direction edge
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}


// low[i] means the smallest points that point i can reach
void Graph::APUtil(int u, bool *visited, int *disc, int *low, int *parent, bool *ap) {
    static int time = 0; //to mark the number of node in DFS tree

    // Count how many children of a node
    int children = 0;

    visited[u] = true;

    // Initialize discovery time and low value
    // disc[u] means point n is the No.disc[u] to go through
    disc[u] = low[u] = ++time;

    // Go through all vertices adjacent to node u
    list<int>::iterator i;
    for(i = adj[u].begin(); i != adj[u].end(); i++){
        int v = *i; //adjacent nodes of u
        if(!visited[v]){
            children++;
            parent[v] = u;
            // Check if sub-graph rooted with v has an articulation point
            APUtil(v, visited, disc, low, parent, ap);

            // check if the subtree rooted with v has a connection to
            // one of the ancestor of u
            low[u] = min(low[u], low[v]);

            // u is an articulation point in following cases
            //(1) u is the root of DFS tree and has two or more children
            if(parent[u] == NIL && children > 1) ap[u] = true;

            //(2) If u is not root and low value of one of its child is
            // more than discovery value of u.
            if(parent[u] != NIL && low[v] >= disc[u]) ap[u] = true;
        }

        // update low value of u for parent function calls.
        else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }
}
void Graph::AP(){
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    bool *ap = new bool[V];

    for(int i = 0; i < V; i++){
        parent[i] = NIL;
        visited[i] = false;
        ap[i] = false;
    }
    uint64_t tick = rdtsc();
    APUtil(0, visited, disc, low, parent, ap);
    for(int i = 0; i < V; i++){
        if(visited[i] == false){
            cout << "This graph is not connected" << endl;
            return;
        }
    }

    int flag = 0;
    for(int i = 0; i < V; i++){
        if(ap[i] == true){
            cout << i << " ";
            flag = 1;
        }
    }
    auto time = rdtsc() - tick;

    cout << endl;
    if(flag) cout << "It is not a bi-connected graph" << endl;
    else cout << "It is a bi-connected graph" << endl;
    cout << "This costs "<< time << "ns" << endl;

}

void dataFromFile(int num, string path){
    ifstream file(path);
    int a, b;
    Graph g(num);   // we have to know how many nodes in advanced
    string line;
    while(getline(file, line)){
        stringstream stream(line);
        stream >> a >> b;
        g.addEdge(a, b);  // this is for undirected edge
    }
    g.AP();
}

int main(){
    // example: data inside the code
//    Graph g1(5);
//    g1.addEdge(1, 0);
//    g1.addEdge(0, 2);
//    g1.addEdge(2, 1);
//    g1.addEdge(0, 3);
//    g1.addEdge(3, 4);
//    g1.AP();
//    cout << "---------------------------" << endl;

    //example: data from outside file
    dataFromFile(7, "test.txt");

    return 0;
}
