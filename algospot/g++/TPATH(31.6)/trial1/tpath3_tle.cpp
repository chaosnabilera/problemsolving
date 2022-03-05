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

void solve(){
	int mindiff = UNREACHABLE;
	int last_ui;
	bool found_path = false;

	std::sort(&edge_weight[0],&edge_weight[M]);

	last_ui = 0;
	for(int li=0; li<M && li <= last_ui; ++li){
		dfs_lowerbound = edge_weight[li];
		for(int ui=last_ui; ui<M; ++ui){
			// printf("%d %d\n",li,ui);
			dfs_upperbound = edge_weight[ui];
			memset(visited, 0, N);
			dfs(0);
			if(visited[N-1]){
				found_path = true;
				last_ui = ui;
				mindiff = std::min(mindiff, edge_weight[ui]-edge_weight[li]);
				break;
			}
		}
		if(!found_path){
			break;
		}
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