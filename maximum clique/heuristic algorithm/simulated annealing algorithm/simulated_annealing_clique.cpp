//
// Created by WIN7 on 12/2/2018.
//
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string.h>
#include <fstream>
#include <ctime>
using namespace std;
const double T = 3000; // the first temperature
const double ENDT = 1e-6;// the last temperature
const double DELTA = 0.98; // the temperature changing rate
const int ILOOP = 3000;

const int maxn = 2001;
int a[maxn][maxn];
int v, e;
vector<int> include;
int best = 0; // current clique size

void readGraph(string filename){
    string line;
    char * cString;
    char * token;
    unsigned temp, v1, v2;
    ifstream myfile(filename);
    if(myfile.is_open()){
        while(myfile.good()){
            getline(myfile, line);
            switch(line[0]){
                case 'c':
                    break;
                case 'p':
                    cString = new char[line.size()+1];
                    strcpy (cString, line.c_str());		/// convert to cstring to
                    temp = 0;							/// count the split occurrences
                    token = strtok(cString," ");
                    while(token != NULL){
                        if(temp == 2) v = (unsigned)atoi(token);
                        if(temp == 3) e = (unsigned)atoi(token);
                        token = strtok(NULL, " ");
                        temp++;
                    }
                    delete[] cString;
                    break;
                case 'e':
                    cString = new char[line.size()+1];
                    strcpy(cString, line.c_str());		/// convert to cstring to
                    temp = 0;							/// count the split occurances

                    token = strtok(cString," ");
                    while (token != NULL){
                        if(temp == 1) v1  = (unsigned)atoi(token);
                        if(temp == 2) v2  = (unsigned)atoi(token);
                        token = strtok(NULL, " ");
                        temp++;
                    }
                    a[v1][v2] = (a[v2][v1] = 1);
                    delete[] cString;
                default:
                    break;
            }
        }
    }
}

bool initialClique(){
    for(int i = 1; i <= v; i++){
        for(int j = i + 1; j <= v; j++){
            if(a[i][j]){
                include.push_back(i);
                include.push_back(j);
                best = 2;
                return 1;
            }
        }
    }
    return 0;
}
int max_clique = 2;
void simulatedAnnealingClique(){
    if(!initialClique()){
        cout << "maximum clique is 1" << endl;
        return;
    }

    double curtemp = T;
    vector<int> exist;
    while(curtemp > ENDT){
        for(int k = 0; k < ILOOP; k++){
            int index = rand() % v + 1;
            vector<int>::iterator it;
            it = find(include.begin(), include.end(), index);
            if(it == include.end()){
                int flag = 0;
                for(int i = 0; i < include.size(); i++){
                    if(a[include[i]][index] == 0){
                        flag = 1;
                        break;
                    }
                }
                if(!flag){
                    best ++;
                    max_clique = max(max_clique, best);
                    include.push_back(index);
                }
            }
            else{
                double r_num = rand()%10000/(double)10001;     //r_num: between 0 to 1
                double temp = (exp(-1/curtemp));
                if(temp > r_num){
                    include.erase(it);
                    best --;
                }
            }
        }
//        cout << "temperature " << curtemp << ":" << endl;
//        for(int i = 0; i < include.size(); i++){
//            cout << include[i] << " ";
//        }
//        cout << endl;
//        cout << "--------------------" << endl;
        // change current temperature
        curtemp *= DELTA;
    }
}
int main(){
    string file = "C:\\clion\\cmake-build-debug\\DIMACS_all_ascii\\brock400_4.clq";
    readGraph(file);
    srand((unsigned) time(0));
    clock_t start = clock();
    simulatedAnnealingClique();
    clock_t end = clock();
    cout << "v: " << v << ", " << "e:" << e << endl;
    cout << "find: " << max_clique << "  last: " << best << endl;
    cout << "time cost: " << double(end - start)/CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << "-----------------" << endl;
    return 0;
}
