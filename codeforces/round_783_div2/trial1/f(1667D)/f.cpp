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
vector<int> E[200001];
int Parent[200001];
char Parity[200001];

bool Contradiction;

void get_input(){
    int u,v;
    scanf("%d", &N);

    for(int i=0; i<=N; ++i)
        E[i].clear();

    for(int i=1; i<N; ++i){
        scanf("%d%d", &u, &v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
}

void dfs(int i){
    int parity_cnt[2] = {0,0};

    // printf("%d\n",i);

    for(int c:E[i]){
        if(c == Parent[i])
            continue;
        Parent[c] = i;
        dfs(c);
        parity_cnt[Parity[c]]++;
    }

    if(i != 1){
        if(parity_cnt[0] < parity_cnt[1])
            Parity[i] = 0;
        else
            Parity[i] = 1;

        parity_cnt[Parity[i]]++;
    }

    // printf("%d %d\n",i,Parity[i]);

    if( (parity_cnt[0] > parity_cnt[1]) || (parity_cnt[1] > parity_cnt[0]+1) ){
        Contradiction = true;
    }
}

void rec_print(int i){
    vector<int> child_parity[2];

    for(int c:E[i]){
        if(c == Parent[i])
            child_parity[Parity[i]].push_back(c);
        else
            child_parity[Parity[c]].push_back(c);
    }

    int cur_par = (E[i].size() & 1) ? 1 : 0;
    for(int it = 0; it < E[i].size(); ++it){
        int c = child_parity[cur_par].back(); child_parity[cur_par].pop_back();
        if(c == Parent[i])
            printf("%d %d\n",c,i);
        else
            rec_print(c);
        cur_par = (cur_par == 0) ? 1 : 0;
    }
}

void solve(){
    Contradiction = false;

    for(int i=1; i<=N; ++i)
        Parent[i] = -1;

    dfs(1);
    if(Contradiction){
        printf("NO\n");
        return;
    }

    printf("YES\n");
    rec_print(1);
}

int main(int argc, char** argv){
    int t = 0;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        solve();
    }
}