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

// Kruskal algorithm은 disjoint set을 이용하여 어떤 edge를 minimum spanning tree의 일부인지 아닌지 판별한다
class DisjointSet{
public:
	DisjointSet(int _V) : V(_V) {
		parent.resize(V);
		size.resize(V);
		plist.resize(V);
		for(int i=0; i<V; ++i){
			parent[i] = i;
			size[i] = 1;
		}
	}
	~DisjointSet(){
	}
	int find_parent(int cur){ // change a->b->c->d ==> a,b,c -> d all the way up
		int p = cur;
		int plist_size = 0;
		int res;

		while(parent[p] != parent[parent[p]]){
			plist[plist_size++] = p;
			p = parent[p];
		}
		res = parent[p];

		for(int i=0; i<plist_size; ++i){
			parent[plist[i]] = res;
		}

		return res;
	}
	void merge(int a, int b){
		a = find_parent(a);
		b = find_parent(b);
		if(size[a] > size[b]){
			size[a] += size[b];
			parent[b] = a;
		}
		else{
			size[b] += size[a];
			parent[a] = b;
		}
	}
private:
	int V;
	vector<int> parent;
	vector<int> size;
	vector<int> plist;
};

/*
    <Kruskal's algorithm>
    Edge들을 cost순으로 정렬한 뒤 순서대로 보면서 edge a-b가 이미 같은 그룹이 아니라면 그것을 채택하고 a와 b를 같은 그룹으로 넣는다
    a와 b가 같은 그룹인지 여부 판단을 쉽게 하기 위해 Disjoint Set을 사용한다

    저렇게 하면 왜 minimum spanning tree가 만들어 지는가?

    일단 a-b가 이미 같은 그룹 = 즉 이미 연결되어 있는 상태라면 또 다시 연결할 필요가 없다
    즉 이런식으로 만들어 지는 그래프는 path가 하나라도 있으면 더 이상 path를 만들지 않는, tree가 될 수 밖에 없다
    그렇다고 쳤을 때 cost가 더 낮은 edge x를 하나 무시하고 다른 edge y를 채택해서 minimum spanning tree를 만들었다고 치자
    근데 그렇게 만들어진 minimum spanning tree에서 y를 빼버리면? 그럼 일단 그 그래프는 두개의 tree로 쪼개지게 된다
    tree에는 모든 정점간의 path는 하나밖에 없으니, edge하나를 빼면 당연히 두개로 쪼개지게 된다
    여기에서 x를 넣으면 두개는 무조건 연결된다
    왜냐하면 x는 y와 같은 기능을 하지만 x대신 y를 선택한 거였으니까
    근데 x는 y보다 cost가 적다
    즉 x를 선택하는 쪽이 언제나 유리한 것이다

    대략 이런 원리로 minimum spanning tree가 완성된다
    구종만 책 2권 974쪽 참고

    Edge를 정렬하는 시간이 모든걸 좌우하니 결국 O(ElogE)
*/
template <typename T>
T mst_kruskal(vector<vector<pair<int,T>>>& adj, vector<pair<pair<int,int>,T>>& selected){
    T total_cost = 0;
    int vcnt = adj.size();
    vector<pair<T,pair<int,int>>> edges;
    DisjointSet ds(vcnt);

    for(int u=0; u<vcnt; ++u){
        for(auto& p:adj[u]){
            int v = p.first;
            T cost = p.second;
            edges.push_back(make_pair(cost,make_pair(u,v)));
        }
    }

    sort(edges.begin(),edges.end());

    selected.clear();
    for(auto& p:edges){
        T cost = p.first;
        int u = p.second.first;
        int v = p.second.second;

        if(ds.find_parent(u) == ds.find_parent(v))
            continue;
        
        ds.merge(u,v);
        selected.push_back(make_pair(make_pair(u,v),cost));
        total_cost += cost;
    }

    return total_cost;
}

int main(int argc, char** argv){
    vector<vector<pair<int,double>>> adj;
    vector<pair<pair<int,int>,double>> selected;
    mst_kruskal<double>(adj, selected);
}
