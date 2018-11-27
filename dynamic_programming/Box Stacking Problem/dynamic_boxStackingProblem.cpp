//
// Created by WIN7 on 11/27/2018.
//
#include <iostream>
#include <algorithm>
using namespace std;
struct Box{
    int w, d, h;
};
bool compare(Box a, Box b){
    return a.d * a.w > b.d * b.w;
}
int maxStackHeight(Box *arr, int n){
    Box rot[3 * n];  // each box has 3 rotation cases
    int index = 0;
    // consider d >= w
    for(int i = 0; i < n; i++){
        rot[index].h = arr[i].h;
        rot[index].d = max(arr[i].d, arr[i].w);
        rot[index].w = min(arr[i].d, arr[i].w);
        index++;

        rot[index].h = arr[i].d;
        rot[index].d = max(arr[i].h, arr[i].w);
        rot[index].w = min(arr[i].h, arr[i].w);
        index++;

        rot[index].h = arr[i].w;
        rot[index].d = max(arr[i].h, arr[i].d);
        rot[index].w = min(arr[i].h, arr[i].d);
        index++;
    }
    n = 3 * n;
    /*
     * condition 1: base_size[a] < base_size[b]
     * condition 2: a.d < b.d
     * condition 3: a.w < b.w
     */

    // sort the boxes depended on base size: d * w
    // in LIS we have to make sure the order of the result is the same as the input array
    // sort rot in order to create the order of input
    // we can also sort depended on the d or w, which we don't need to consider base size
    sort(rot, rot + n, compare);

    // use LIS for dynamic programming
    int msh[n];
    for(int i = 0; i < n; i++){
        msh[i] = rot[i].h;
        for(int j = 0; j < i; j++) {
            if (rot[j].d > rot[i].d && rot[j].w > rot[i].w && msh[i] < msh[j] + rot[i].h)
                msh[i] = msh[j] + rot[i].h;
        }
    }
    cout << *max_element(msh, msh + n) << endl;
}
int main(){
    Box arr[] = {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}};
    int n = sizeof(arr) / sizeof(arr[0]);
    maxStackHeight(arr, n);
    return 0;
}
