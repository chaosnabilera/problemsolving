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

struct Edge{
	Edge(int _a, int _b, int _w) : a(_a), b(_b), w(_w) { } 
	int a;
	int b;
	int w;
};

int T,G,W;
std::vector<Edge> init_edges;
std::vector<Edge> edges; 
std::vector<int> adj[100];
bool reachable[100][100];
bool discovered[100];
int distance[100];

void dfs(int cur){
	discovered[cur] = true;
	for(int n:adj[cur]){
		if(!discovered[n])
			dfs(n);
	}
}

void reach_dfs(int g, int cur){
	reachable[g][cur] = true;
	for(int n:adj[cur]){
		if(!reachable[g][n])
			reach_dfs(g, n);
	}
}

void determine_reacheable(){
	memset(reachable,0,sizeof(reachable));
	for(int g=0; g<G; ++g){
		if(discovered[g])
			reach_dfs(g, g);
	}
}

bool bellman_ford(){
	bool no_cycle = true;
	bool updated = false;

	for(int g=0; g<G; ++g){
		distance[g] = 2000000000;
	}
	distance[0] = 0;

	for(int g=0; g<G-1; ++g){
		updated = false;
		for(auto e:edges){
			if(distance[e.a] + e.w < distance[e.b]){
				distance[e.b] = distance[e.a]+e.w;
				updated = true;
			}
		}
		if(!updated){
			break;
		}
	}

	if(updated){
		for(auto e:edges){
			if(distance[e.a] + e.w < distance[e.b]){
				if(reachable[e.b][1]){
					no_cycle = false;
					break;
				}
			}
		}
	}

	return no_cycle;
}

int main(int argc, char** argv){
	int a,b,d;

	scanf("%d", &T);
	for(int t=0; t<T; ++t){
		scanf("%d %d", &G, &W);

		init_edges.clear();
		edges.clear();
		for(int i=0; i<G; ++i){
			adj[i].clear();
		}

		for(int i=0; i<W; ++i){
			scanf("%d %d %d", &a, &b, &d);
			adj[a].push_back(b);
			init_edges.push_back(Edge(a,b,d));
		}

		memset(discovered, 0, sizeof(discovered));
		dfs(0);	
		if(!discovered[1]){
			printf("UNREACHABLE\n");
			continue;
		}

		determine_reacheable();

		for(auto e:init_edges){
			if(discovered[e.a] && discovered[e.b]){
				edges.push_back(e);
			}
		}

		//fastest way
		if(bellman_ford()){
			printf("%d ", distance[1]);
		}
		else{
			printf("INFINITY ");
		}

		//slowest way
		for(int i=0; i<edges.size(); ++i){
			edges[i].w = -edges[i].w;
		}
		if(bellman_ford()){
			printf("%d\n", -distance[1]);
		}
		else{
			printf("INFINITY\n");
		}
	}
}