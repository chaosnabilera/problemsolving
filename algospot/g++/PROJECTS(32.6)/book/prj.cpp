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
#include <deque>

const int MAXV = 256;
const int SOURCE = 0;
const int SINK = 1;
const int INF = 987654321;

int C, N, M;
int profit[100];
int cost[100];
bool need[100][100];

std::vector<int> adj[MAXV];
int capacity[MAXV][MAXV];
int flow[MAXV][MAXV];
bool is_valid[MAXV];

void get_input(){
	int b;
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; ++i)
		scanf("%d", &profit[i]);
	for(int i=0; i<M; ++i)
		scanf("%d", &cost[i]);
	for(int i=0; i<N; ++i)
		for(int j=0; j<M; ++j){
			scanf("%d", &b);
			need[i][j] = (b==1);
		}
}

void print_graph(){
	for(int v=0; v<MAXV; ++v){
		if(is_valid[v]){
			printf("%d : ",v);
			for(int n:adj[v]){
				printf("%d(%d/%d) ", n, flow[v][n], capacity[v][n]);
			}
			printf("\n");
		}
	}
}

void build_graph(){
	for(int i=0; i<256; ++i){
		adj[i].clear();
	}
	memset(capacity,0,sizeof(capacity));
	memset(flow,0,sizeof(flow));
	memset(is_valid,0,sizeof(is_valid));

	is_valid[SOURCE] = true;
	is_valid[SINK] = true;
	for(int i=0; i<N; ++i){
		int v_prj = 2+i;
		capacity[SOURCE][v_prj] = profit[i];
		adj[SOURCE].push_back(v_prj);
		adj[v_prj].push_back(SOURCE);
		is_valid[v_prj] = true;

		for(int j=0; j<M; ++j){
			int v_eq = 2+N+j;
			if(need[i][j]){
				capacity[v_prj][v_eq] = profit[i];
				adj[v_prj].push_back(v_eq);
				adj[v_eq].push_back(v_prj);
			}
		}
	}

	for(int i=0; i<M; ++i){
		int v_eq = 2+N+i;
		capacity[v_eq][SINK] = cost[i];
		adj[v_eq].push_back(SINK);
		adj[SINK].push_back(v_eq);
		is_valid[v_eq] = true;
	}
}

int compute_maxflow(){
	int maxflow = 0;
	int parent[MAXV];
	std::deque<int> q;

	memset(flow, 0, sizeof(flow));
	int d = 0;

	while(true){
		std::fill(&parent[0],&parent[MAXV],-1);
		parent[SOURCE] = SOURCE;
		q.clear();
		q.push_back(SOURCE);

		// printf("%d %d\n", SINK, parent[SINK]);
		while(!q.empty() && parent[SINK] == -1){
			int cur = q.front(); q.pop_front();
			for(int nxt:adj[cur]){
				if(nxt == SINK){
					// printf("S: %d %d\n", capacity[cur][nxt], flow[cur][nxt]);
				}
				if(is_valid[nxt] && parent[nxt] == -1 && capacity[cur][nxt]-flow[cur][nxt] > 0){
					// printf("%d %d\n", cur, nxt);
					parent[nxt] = cur;
					q.push_back(nxt);
				}
			}
		}

		if(parent[SINK] == -1){
			break;
		}

		int curflow = INF;
		for(int cur = SINK; cur != SOURCE; cur = parent[cur]){
			curflow = std::min(curflow, capacity[parent[cur]][cur]-flow[parent[cur]][cur]);
		}
		for(int cur = SINK; cur != SOURCE; cur = parent[cur]){
			flow[parent[cur]][cur] += curflow;
			flow[cur][parent[cur]] -= curflow;
		}

		// printf("curflow:%d\n", curflow);
		maxflow += curflow;
	}
	
	return maxflow;
}

bool has_unnnecessary(){
	bool res = false;
	for(int i=0; i<M; ++i){
		int v_eq = 2+N+i;
		if(is_valid[v_eq] && flow[v_eq][SINK] < capacity[v_eq][SINK]){
			res = true;
			is_valid[v_eq] = false;
		}
	}
	for(int i=0; i<N; ++i){
		int v_prj = 2+i;
		if(is_valid[v_prj]){
			for(int v_eq:adj[v_prj]){
				if(!is_valid[v_eq]){
					res = true;
					is_valid[v_prj] = false;
					break;
				}
			}
		}
	}
	return res;
}

void solve(){
	int totalearn = 0;
	int totalcost = 0;

	do{
		totalcost = compute_maxflow();
		// print_graph();
	} while(has_unnnecessary());

	for(int i=0; i<N; ++i){
		int v_prj = 2+i;
		if(is_valid[v_prj]){
			totalearn += profit[i];
		}
	}

	// printf("totalearn: %d totalcost: %d\n", totalearn, totalcost);

	printf("%d\n", totalearn-totalcost);
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		// printf("%d\n",i);
		get_input();
		// printf("%d\n",i);
		build_graph();
		// printf("%d\n",i);
		solve();
	}
}