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
    Prim's algorithm

    한 정점에서 부터 시작해서 현재 까지 찾은 minimum spanning tree에 연결 할 수 있는 vertex중 
    가장 적은 cost로 연결할 수 있는 vertex를 찾아 연결한다. 
    이걸 계속 하는 것을 통해 minimum spanning tree를 만든다

    정당성 증명은 Kruskal's algorithm과 비슷함
    가장 적은 cost로 연결 안하고 다른걸로 minimum spanning tree를 만들었다고 가정해 보자
    그거 끊고 가장 적은 cost인 edge로 연결할 수 있는걸로 연결하면 언제나 줄일 수 있음

    여기서 중요한건 가장 적은 cost로 연결할 수 있는 vertex가 무엇인지 효율적으로 찾는것
    무식하게 생각해 보면 모든 edge를 다 봐야 할 것 같지만
    잘 생각해 보면 각 정점마다 이 정점에 연결하기 위한 최소 cost를 한 정점을 minimum spanning에 추가할 때 마다
    업데이트 할 수 있다 (하나씩 discover 하고 있는 거니까)
    이렇게 해두면 가장 적은 cost로 연결할 수 있는 정점은 정점 숫자 만큼만 보면 된다. 즉 한 iteration은 O(V)

    그리고 생각해 보면 우리는 모든 edge를 딱 두번 본다
    한 edge가 a-b를 연결한다 치면, a를 추가할때 a에 연결된 모든 edge를 한번 다 보니 이때 한번
    b를 추가할 때 b에 연결 된 모든 edge를 한번 다 보니 이때 한번
    그래서 총 두번

    그래서 총 time complexity는 O(V^2 + E) 가 된다

    E의 최대치는 V^2인데, 만약 E가 크면 결국 O(V^2) = O(E) 가 되는 셈
    E가 크면 클수록 Prim이 Kruskal보다 유리하다
*/

template <typename T>
T mst_prim(vector<vector<pair<int,T>>>& adj, vector<pair<pair<int,int>,T>>& selected){
    int vcnt = adj.size();
    vector<bool> added(vcnt, false);
    vector<T> mincost(vcnt, numeric_limits<T>::max());
    vector<int> parent(vcnt,-1);
    T total_weight = 0;

    mincost[0] = parent[0] = 0;
    for(int it=0; it<vcnt; ++it){
        int u = -1;
        for(int v=0; v<vcnt; ++v){
            if(!added[v] && (u == -1 || mincost[u] > mincost[v]))
                u = v;
        }
        if(parent[u] != u)
            selected.push_back(make_pair(make_pair(u,parent[u]),mincost[u]));
        
        total_weight += mincost[u];
        added[u] = true;
        for(auto& p:adj[u]){
            int v = p.first;
            T cost = p.second;
            if(!added[v] && mincost[v] > cost){
                parent[v] = u;
                mincost[v] = cost;
            }
        }
    }
    return total_weight;
}

int main(int argc, char** argv){
    vector<vector<pair<int,double>>> adj;
    vector<pair<pair<int,int>,double>> selected;
    mst_prim(adj,selected);
}