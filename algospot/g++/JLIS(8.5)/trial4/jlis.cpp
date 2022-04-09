#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

vector<int> A;
vector<int> B;

int DP[101][101];

void get_input(){
    int n,m;
    scanf("%d%d", &n, &m);
    A.resize(n);
    B.resize(m);
    for(int i=0; i<n; ++i)
        scanf("%d", &A[i]);
    for(int i=0; i<m; ++i)
        scanf("%d", &B[i]);
}

int rec_solve(int a, int b){
    if(DP[a][b] != -1)
        return DP[a][b];
    
    DP[a][b] = 1;
    if(A[a] < B[b]){
        DP[a][b] = 1 + DP[A.size()][b];
        for(int aa = a+1; aa<A.size(); ++aa){
            if(A[aa] > A[a])
                DP[a][b] = max(DP[a][b], 1+rec_solve(aa,b));
        }
    }
    else if(B[b] < A[a]){
        DP[a][b] = 1 + DP[a][B.size()]; 
        for(int bb = b+1; bb<B.size(); ++bb){
            if(B[bb] > B[b])
                DP[a][b] = max(DP[a][b], 1+rec_solve(a,bb));
        }
    }
    else{
        for(int aa = a+1; aa<A.size(); ++aa){
            for(int bb = b+1; bb<B.size(); ++bb){
                if(A[a] < A[aa] && B[b] < B[bb])
                    DP[a][b] = max(DP[a][b], 1+rec_solve(aa,bb));
            }
        }
    }
    return DP[a][b];
}

void print_dp(){
    for(int a=0; a <= A.size(); ++a){
        for(int b=0; b <= B.size(); ++b){
            printf("%3d", DP[a][b]);
        }
        printf("\n");
    }
}

void solve(){
    memset(DP,0xFF,sizeof(DP));

    // precompute simple case
    DP[A.size()][B.size()] = 0;
    for(int a=A.size()-1; a>=0; --a){
        DP[a][B.size()] = 1;
        for(int aa=a+1; aa<A.size(); ++aa)
            if(A[a] < A[aa])
                DP[a][B.size()] = max(DP[a][B.size()], 1+DP[aa][B.size()]);
    }
    for(int b=B.size()-1; b>=0; --b){
        DP[A.size()][b] = 1;
        for(int bb=b+1; bb<B.size(); ++bb)
            if(B[b] < B[bb])
                DP[A.size()][b] = max(DP[A.size()][b], 1 + DP[A.size()][bb]);
    }

    //print_dp();

    // compute complicated case
    int maxlen = 0;
    for(int a=0; a<A.size(); ++a)
        for(int b=0; b<B.size(); ++b)
            maxlen = max(maxlen, rec_solve(a,b));

    //print_dp();

    printf("%d\n", maxlen);
}

int main(int argc, char** argv){
    int c = 0;
    scanf("%d", &c);
    for(int i=0; i<c; ++i){
        get_input();
        solve();
    }
}