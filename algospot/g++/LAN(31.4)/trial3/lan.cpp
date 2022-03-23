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

int N,M;
vector<double> X;
vector<double> Y;

vector<vector<pair<int,double>>> Adj;

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

template <typename T>
T mst_kruskal(vector<vector<pair<int,T>>>& adj, vector<pair<pair<int,int>,T>>& selected, DisjointSet& ds){
    T total_cost = 0;
    int vcnt = adj.size();
    vector<pair<T,pair<int,int>>> edges;

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

void get_input(){
    scanf("%d%d",&N,&M);
    X.resize(N);
    Y.resize(N);
    Adj.clear();
    Adj.resize(N);

    for(int i=0; i<N; ++i)
        scanf("%lf",&X[i]);

    for(int i=0; i<N; ++i)
        scanf("%lf",&Y[i]);

    for(int u=0; u<N; ++u){
        for(int v=u+1; v<N; ++v){
            double dx = X[u]-X[v];
            double dy = Y[u]-Y[v];
            double dist = sqrt(dx*dx + dy*dy);
            Adj[u].push_back(make_pair(v,dist));
            Adj[v].push_back(make_pair(u,dist));
        }
    }
}

void solve(){
    int u,v;
    vector<pair<pair<int,int>,double>> selected;
    DisjointSet ds(N);

    for(int i=0; i<M; ++i){
        scanf("%d%d",&u,&v);
        ds.merge(u,v);
    }

    double res = mst_kruskal<double>(Adj, selected, ds);
    printf("%.10lf\n",res);
}

int main(int argc, char** argv){
    int c = 0;
    scanf("%d", &c);
    for(int i=0; i<c; ++i){
        get_input();
        solve();
    }
}