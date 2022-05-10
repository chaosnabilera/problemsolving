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

int N,K;
vector<long long> E;

void get_input(){
    long long v;
    scanf("%d%d", &N, &K);
    E.clear();
    for(int i=0; i<N; ++i){
        scanf("%lld", &v);
        E.push_back(v);
    }
}

void solve(){
    if(K != 1){
        printf("IMPOSSIBLE\n");
        return;
    }

    long long Esum = 0;
    long long Esum_sq = 0;
    long long sq_single = 0;

    for(int i=0; i<N; ++i){
        Esum += E[i];
        sq_single += E[i]*E[i];
    }
    Esum_sq = Esum*Esum;

    if(Esum_sq == sq_single){
        printf("0\n");
        return;
    }

    if(Esum == 0){
        printf("IMPOSSIBLE\n");
        return;
    }

    long long a = Esum_sq - sq_single;
    long long t = 2*Esum;

    if(a % t == 0){
        printf("%lld\n",-a/t);
    }
    else{
        printf("IMPOSSIBLE\n");
    }
}

int main(int argc, char** argv){
    int t = 0;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        printf("Case #%d: ", i+1);
        solve();
    }
}