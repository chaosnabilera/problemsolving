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
void floyd_warshall(vector<vector<T>>& adj){
	const size_t V = adj.size();
	for(size_t i=0; i < V; ++i)
		adj[i][i] = 0;
	for(int k=0; k<V; ++k)
		for(int i=0; i<V; ++i)
			for(int j=0; j<V; ++j)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

const int INF = 987654321;
int V,E;
vector<int> Delay;
vector<vector<int>> Dist;
vector<vector<int>> Total;

void get_map(){
	int a,b,t;
	scanf("%d%d", &V, &E);

	Delay.resize(V);
	for(int i=0; i<V; ++i)
		scanf("%d", &Delay[i]);

	Dist.resize(V);
	for(int i=0; i<V; ++i)
		Dist[i].resize(V, INF);

	for(int i=0; i<E; ++i){
		scanf("%d%d%d",&a,&b,&t);
		--a; --b;
		Dist[a][b] = t;
		Dist[b][a] = t;
	}
}

bool compare_delay(int a, int b){
	return Delay[a] < Delay[b];
}

void precompute(){
	vector<int> order;
	order.resize(V);
	for(int i=0; i<order.size(); ++i)
		order[i] = i;
	sort(order.begin(),order.end(),compare_delay);

	for(size_t i=0; i < V; ++i)
		Dist[i][i] = 0;

	Total = Dist;
	for(int k:order){
		// printf("%d:%d\n",k,Delay[k]);
		for(int i=0; i<V; ++i){
			for(int j=0; j<V; ++j){
				Dist[i][j] = min(Dist[i][j], Dist[i][k] + Dist[k][j]);
				Total[i][j] = min(Total[i][j], Dist[i][k] + Delay[k] + Dist[k][j]);
			}
		}
	}

}

int main(int argc, char** argv){
	int t,a,b;
	get_map();
	precompute();
	scanf("%d", &t);
	for(int i=0; i<t; ++i){
		scanf("%d%d", &a, &b);
		--a; --b;
		printf("%d\n",Total[a][b]);
	}
}