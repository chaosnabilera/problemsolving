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
vector<int> S;

void get_input(){
    scanf("%d", &N);
    S.resize(N);
    for(int i=0; i<N; ++i){
        scanf("%d",&S[i]);
    }
}

void solve(){
    sort(S.begin(),S.end());
    int cur = 1;
    for(int s:S){
        if(s >= cur)
            ++cur;
    }
    printf("%d\n",cur-1);
}

int main(int argc, char** argv){
    int t = 0;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        printf("Case #%d: ",i+1);
        get_input();
        solve();
    }
}