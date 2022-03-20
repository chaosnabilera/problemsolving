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

const unsigned int INF = 1234567890;
int V,M,N;

unsigned int Adj[200][200];

void floyd_warshall(){
	for(size_t i=0; i < V; ++i)
		Adj[i][i] = 0;
	for(int k=0; k<V; ++k)
		for(int i=0; i<V; ++i)
			for(int j=0; j<V; ++j)
				Adj[i][j] = min(Adj[i][j], Adj[i][k] + Adj[k][j]);
}

void get_input(){
	unsigned int a,b,c;

	scanf("%d%d%d",&V,&M,&N);
	for(int i=0; i<V; ++i)
		for(int j=0; j<V; ++j)
			Adj[i][j] = INF;

	for(int i=0; i<M; ++i){
		scanf("%d%d%d",&a,&b,&c);
		Adj[a][b] = min(Adj[a][b],c);
		Adj[b][a] = Adj[a][b];
	}
}

void solve(){
	unsigned int a,b,c;
	int cnt = 0;
	floyd_warshall();
	for(int i=0; i<N; ++i){
		scanf("%d%d%d",&a,&b,&c);
		if(Adj[a][b] <= c){
			++cnt;
		}
		else{
			Adj[a][b] = c;
			Adj[b][a] = c;
			for(int u=0; u<V; ++u)
				for(int v=0; v<V; ++v){
					Adj[u][v] = min(Adj[u][v], Adj[u][a]+Adj[a][b]+Adj[b][v]);
					Adj[v][u] = Adj[u][v];
				}
		}
	}
	printf("%d\n",cnt);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}