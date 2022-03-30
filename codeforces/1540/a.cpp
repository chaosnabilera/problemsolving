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

int N;
int D[100000];

void get_input(){
    scanf("%d",&N);
    for(int i=0; i<N; ++i)
        scanf("%d", &D[i]);
}

void solve(){
    int zcnt = 0;
    sort(&D[0],&D[N]);
    for(int i=0; i<N; ++i){
        if(D[i] != 0)
            break;
        zcnt++;
    }

    unsigned long long curterm = 0;
    unsigned long long cumul = 0;

    for(int i=0; i < N-2; ++i){
        curterm += D[N-1]-D[i];
    }
    cumul = curterm;
    // printf("%lld\n",cumul);
    for(unsigned long long i=N-1; i>=2; --i){
        curterm -= ((D[i]-D[i-1])*(i-1));
        // printf("%lld\n",curterm);
        curterm -= (D[i-1]-D[i-2]);
        // printf("%lld\n",curterm);
        cumul += curterm;
        // printf("%d %lld, %lld\n",i,curterm,cumul);
    }

    if(cumul == 0){
        printf("0\n");
    }
    else{
        printf("-%lld\n", cumul);
    }
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        solve();
    }
}