#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <utility>
#include <queue>
#include <array>
#include <string>

const int UNREACHABLE = 1000000000;
int C,N,M;

std::vector<std::pair<int,int>> adj[2000];
int edge_weight[4000];
int dfs_lowerbound, dfs_upperbound;
bool visited[2000];


void dfs(int cur){
	visited[cur] = true;
	for(auto cp:adj[cur]){
		int n = cp.first;
		int w = cp.second;
		if(!visited[n] && w >= dfs_lowerbound && w <= dfs_upperbound){
			dfs(n);
		}
	}
}

int compute_upperbound(int lbi){
	int li = lbi;
	int hi = M-1;
	int mi;
	int res = UNREACHABLE;

	dfs_lowerbound = edge_weight[li];
	while(li <= hi){
		mi = (li+hi) >> 1;
		dfs_upperbound = edge_weight[mi];
		memset(visited, 0, N);
		dfs(0);
		if(visited[N-1]){
			res = edge_weight[mi];
			hi = mi-1;
		}
		else{
			li = mi+1;
		}
	}

	return res;
}

void solve(){
	int lowerbound, upperbound;
	int mindiff = UNREACHABLE;

	std::sort(&edge_weight[0],&edge_weight[M]);

	for(int i=0; i<M; ++i){
		lowerbound = edge_weight[i];
		upperbound = compute_upperbound(i);
		// printf("%d: %d %d\n", i, lowerbound, upperbound);
		mindiff = std::min(mindiff, upperbound - lowerbound);
	}

	printf("%d\n", mindiff);
}


int main(int argc, char** argv){
	unsigned int a, b, c, e;

	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d %d", &N, &M);

		for(int i=0; i<N; ++i){
			adj[i].clear();
		}

		for(int i=0; i<M; ++i){
			scanf("%d %d %d", &a, &b, &c);
			adj[a].push_back(std::make_pair(b,c));
			adj[b].push_back(std::make_pair(a,c));
			edge_weight[i] = c;
		}
		solve();
	}
}