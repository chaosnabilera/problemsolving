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
vector<long long> F;
vector<int> P;

vector<int> Child[100001];
vector<pair<long long,int>> ChildOrder[100001];
vector<int> Order;
vector<bool> Visited;

void get_input(){
    scanf("%d", &N);
    F.resize(N+1);
    F[0] = 0;
    for(int i=1; i<=N; ++i)
        scanf("%lld", &F[i]);
    P.resize(N+1);
    P[0] = 0;
    for(int i=1; i<=N; ++i)
        scanf("%d", &P[i]);
}

long long rec_sort_traverse(int cur){
    if(Child[cur].empty()){
        return F[cur];
    }
    for(int child:Child[cur]){
        long long child_path_max = rec_sort_traverse(child);
        ChildOrder[cur].push_back(make_pair(child_path_max,child));
    }

    sort(ChildOrder[cur].begin(),ChildOrder[cur].end());
    return max(ChildOrder[cur].back().first, F[cur]);
}

void rec_order_traverse(int cur){
    if(ChildOrder[cur].empty()){
        Order.push_back(cur);
        return;
    }
    for(auto& p:ChildOrder[cur]){
        rec_order_traverse(p.second);
    }
}

long long trigger(int cur, long long max_val){
    if(Visited[cur]){
        return max_val;
    }
    else{
        Visited[cur] = true;
        return trigger(P[cur], max(F[cur],max_val));
    }
}

void solve(){
    for(int i=0; i<=N; ++i){
        Child[i].clear();
        ChildOrder[i].clear();
    }
    
    for(int i=1; i<=N; ++i)
        Child[P[i]].push_back(i);

    rec_sort_traverse(0);
    Order.clear();
    rec_order_traverse(0);

    Visited.resize(N+1);
    fill(Visited.begin(),Visited.end(),false);
    
    long long res = 0;
    for(int o:Order){
        //printf("? %d\n",o);
        res += trigger(o, 0);
    }

    printf("%lld\n", res);
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        printf("Case #%d: ",i+1);
        get_input();
        solve();
    }
}