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

/*
    Ford-Fulkerson Algorithm
    Adjascency array 대신 Adjascency list를 사용하는 버전
    edge의 숫자가 적다면 이게 더 빠를 것임
*/

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

int ford_fulkerson(vector<vector<FFEdge*>>& adj, int source, int sink){
    const int INF = numeric_limits<int>::max();
    int total_flow = 0;
    int vcnt = adj.size();
    vector<int> parent(vcnt);
    vector<FFEdge*> path(vcnt);

    while(true){
        queue<int> q;
        fill(parent.begin(),parent.end(),-1);
        fill(path.begin(), path.end(), nullptr);

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
    return total_flow;
}


int main(int argc, char** argv){
    vector<vector<FFEdge*>> adj;
    vector<vector<int>> capacity;
    vector<vector<int>> flow;
    int source = 0;
    int sink = 0;

    ford_fulkerson(adj, source, sink);
}