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

template <typename T>
void dfs(vector<vector<pair<int,T>>>& graph, vector<bool>& visited, int cur){
	if(visited[cur])
		return;
	visited[cur] = true;
	for(auto& p:graph[cur]){
		dfs(graph,visited,p.first);
	}
}

template <typename T>
vector<T> bellman_ford(vector<vector<pair<int,T>>>& adj, int src){
	const T INF = 987654321; // Big enough to represent Infinity. Small enough for checking dist[v] > dist[u] + w(u,v)
	vector<T> upper(adj.size(), INF);
	vector<bool> visited(adj.size(),false);
	upper[src] = 0;
	bool updated = false;

	dfs<int>(adj, visited, src);

	for(int it=0; it<adj.size(); ++it){
		updated = false;
		for(int u=0; u<adj.size(); ++u){
			if(!visited[u])
				continue;
			for(auto& p:adj[u]){
				int v = p.first;
				T cost = p.second;
				if(upper[v] > upper[u] + cost){ // relaxable
					upper[v] = upper[u] + cost;
					updated = true;
				}
			}
		}
		if(!updated)
			break;
	}

	if(updated) // negative cycle exist
		upper.clear();

	return upper;
}

int V,W;
vector<vector<pair<int,int>>> Adj;

void get_input(){
	int a,b,d;
	scanf("%d%d",&V,&W);
	Adj.clear();
	Adj.resize(V);
	for(int i=0; i<W; ++i){
		scanf("%d%d%d",&a,&b,&d);
		Adj[a].push_back(make_pair(b,d));
	}
}

void solve(){
	const int TEST = 900000000;

	vector<int> ans1 = bellman_ford<int>(Adj, 0);

	if(ans1.empty()){
		printf("INFINITY ");
	}
	else{
		if(ans1[1] > TEST){
			printf("UNREACHABLE\n");
			return;
		}
		else{
			printf("%d ", ans1[1]);
		}
	}

	for(int u=0; u<Adj.size(); ++u){
		for(auto& p:Adj[u]){
			p.second = -p.second;
		}
	}

	vector<int> ans2= bellman_ford<int>(Adj, 0);

	if(ans2.empty()){
		printf("INFINITY\n");
	}
	else{
		if(ans2[1] > TEST){
			printf("UNREACHABLE\n");
			return;
		}
		else{
			printf("%d\n", -ans2[1]);
		}
	}

}

int main(int argc, char** argv){
	int c=0;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}