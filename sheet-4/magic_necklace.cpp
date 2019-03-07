#include <iostream>
#include <limits>
#include <cstdio>
#include "bits/stdc++.h"
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

void findLIS(int n, vector<int> LIS, vector<int> pos, vector<int> A) {
    int i, L = -1, l, r, m, newSet;
    int j;
    for(i = 0; i < n; i++) {
        l = 0, r = L, newSet = -1;
        while(l <= r) {
            m = (l+r)/2;
            if(pos[m] <= A[i]) {
                if(m == L || pos[m+1] > A[i]) {
                    newSet = m+1;break;
                } else
                    l = m+1;
            } else {
                r = m-1;
            }
        }
        if(newSet == -1)	newSet++;
        pos[newSet] = A[i];
        LIS[i] = newSet+1;
        if(L < newSet)	L = newSet;
    }
}
void findLDS(int n, vector<int> LDS, vector<int> pos, vector<int> A) {
    int i, L = -1, l, r, m, newSet;
    int j;
    for(i = 0; i < n; i++) {
        l = 0, r = L, newSet = -1;
        while(l <= r) {
            m = (l+r)/2;
            if(pos[m] >= A[i]) {
                if(m == L || pos[m+1] < A[i]) {
                    newSet = m+1;break;
                } else
                    l = m+1;
            } else {
                r = m-1;
            }
        }
        if(newSet == -1)	newSet++;
        pos[newSet] = A[i];
        LDS[i] = newSet+1;
        if(L < newSet)	L = newSet;
    }
}
int main() {
    int tc, n, i, input;
    cin >> tc;
    while(tc--) {
        cin >> n;
        vector<int> A(n);vector<int> LDS(n);vector<int> LIS(n); vector<int> pos(n);
        for(i = 0; i < n; i++) {
            cin >> input;
            A.insert(A.end()-i-1,input);
//            scanf("%d", &A[N-i-1]);
        }

        findLIS(n, LIS, pos, A);
        findLDS(n, LDS, pos, A);
        int max = 0;
        for(i = 0; i < n; i++) {
            if(LIS[i]+LDS[i]-1 > max)
                max = LIS[i]+LDS[i]-1;
        }
        cout << max << "\n";
//        printf("%d\n", max);
    }
    return 0;
}

//int main() {
//
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    int tc, n, input;
//
//    cin >> tc;
//    //vector<int> arr;
//
//    for (int i = 0; i < tc; i++) {
//        cin >> n;
//        vector<int> arr(n);
//        for (int j = 0; j < n; j++) {
//            cin >> input;
//            arr.push_back(input);
//        }
//    }
//
//}