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

struct FFEdge{
    FFEdge(int tgt, int cap) : target(tgt), capacity(cap) {flow = 0; reverse = nullptr;}
    int residual_capacity() const { return capacity - flow; }
    void add_flow(int amount){ flow += amount; reverse->flow -= amount; }
    int target, capacity, flow;
    FFEdge* reverse;
};

void add_edge(vector<vector<FFEdge*>>& adj, int u, int v, int capacity){
    FFEdge* uv = new FFEdge(v,capacity);
    FFEdge* vu = new FFEdge(u,0);
    uv->reverse = vu;
    vu->reverse = uv;
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}

const int INF = numeric_limits<int>::max();
int N,M;
vector<int> iWin;
vector<pair<int,int>> iMatch;

void get_input(){
    scanf("%d%d",&N,&M);

    iWin.resize(N);
    for(int i=0; i<N; ++i)
        scanf("%d", &iWin[i]);

    iMatch.resize(M);
    for(int i=0; i<M; ++i)
        scanf("%d%d", &iMatch[i].first, &iMatch[i].second);
}

int solve(){
    int max_other_win = *max_element(&iWin[1],&iWin[iWin.size()]);
    int match_0_cnt = 0;
    int min_win, max_win;
    int source, sink;
    int vcnt = M+N+2;
    vector<vector<FFEdge*>> adj;
    vector<int> parent(vcnt);
    vector<FFEdge*> path(vcnt);
    int total_flow;

    // check simply impossible case
    for(auto& p:iMatch)
        if(p.first == 0 || p.second == 0)
            match_0_cnt++;
    if(iWin[0]+match_0_cnt <= max_other_win)
        return -1;

    // simply possible case
    if(M == 0) 
        return 0;

    // possibles
    min_win = max(0, max_other_win - iWin[0] + 1);
    max_win = match_0_cnt;

    //printf("min: %d max: %d\n", min_win, max_win);

    // build adj
    adj.resize(M+N+2);
    source = M+N;
    sink = M+N+1;
    for(int i=0; i<M; ++i) // source to each match
        add_edge(adj,source,i,1);

    for(int m=0; m<M; ++m){
        int u = M + iMatch[m].first;
        int v = M + iMatch[m].second;
        add_edge(adj, m, u, 1);
        add_edge(adj, m, v, 1);
    }

    add_edge(adj, M+0, sink, min_win);
    for(int n=1; n<N; ++n)
        add_edge(adj, M+n, sink, iWin[0]+min_win-1-iWin[n]);

    total_flow = 0;
    for(int win_cnt = min_win; win_cnt <= max_win; ++win_cnt){
        while(true){
            queue<int> q;
            fill(parent.begin(),parent.end(),-1);
            fill(path.begin(),path.end(),nullptr);
            parent[source] = source;
            q.push(source);

            while(!q.empty() && parent[sink] == -1){
                int u = q.front(); q.pop();
                for(auto uv: adj[u]){
                    int v = uv->target;
                    if(parent[v] == -1 && uv->residual_capacity() > 0){
                        q.push(v);
                        parent[v] = u;
                        path[v] = uv;
                    }
                }
            }

            if(parent[sink] == -1)
                break;

            int amount = INF;
            for(int v = sink; v != source; v = parent[v])
                amount = min(amount, path[v]->residual_capacity());
            for(int v = sink; v != source; v = parent[v]){
                path[v]->add_flow(amount);
            }
            total_flow += amount;
        }

        //printf("%d %d\n", win_cnt, total_flow);

        if(total_flow == M)
            return iWin[0]+win_cnt;

        for(int n=0; n<N; ++n){
            for(auto p:adj[M+n]){
                if(p->target == sink)
                    p->capacity++;
            }
        }
    }

    return -1;
}

int main(int argc, char** argv){
    int c = 0;
    scanf("%d", &c);
    for(int i=0; i<c; ++i){
        get_input();
        printf("%d\n", solve());
    }
}