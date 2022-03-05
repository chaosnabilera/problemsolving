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

int C,N,M;
int input_win[12];
int input_edge[100][2];

const int PLAYER = 100;
const int OTHERS = 120;
const int SOURCE = 126;
const int SINK = 127;
const int MAXV = 128;

const int INF = 987654321;

std::vector<int> adj[MAXV];
int capacity[MAXV][MAXV];
int flow[MAXV][MAXV];
int maxwin[12];

void build_graph(){
	//initialize variables
	for(int i=0; i<MAXV; ++i){
		adj[i].clear();
	}
	memset(capacity,0,sizeof(capacity));
	memset(maxwin,0,sizeof(maxwin));

	// calculate maximum amount of win each player can have
	for(int r=0; r<M; ++r){
		maxwin[input_edge[r][0]]++;
		maxwin[input_edge[r][1]]++;
	}

	// capacity of this part of graph will not change over each iteration
	for(int r=0; r<M; ++r){
		int p1, p2;

		adj[SOURCE].push_back(r);
		adj[r].push_back(SOURCE);
		capacity[SOURCE][r] = 1;

		p1 = PLAYER+input_edge[r][0];
		p2 = PLAYER+input_edge[r][1];

		adj[r].push_back(p1);
		adj[p1].push_back(r);
		adj[r].push_back(p2);
		adj[p2].push_back(r);
		capacity[r][p1] = 1;
		capacity[r][p2] = 1;
	}

	// capacity of this part of graph will change over each iteration
	adj[PLAYER+0].push_back(SINK);
	adj[SINK].push_back(PLAYER+0);
	for(int p=1; p<N; ++p){
		adj[PLAYER+p].push_back(OTHERS);
		adj[OTHERS].push_back(PLAYER+p);
	}
	adj[OTHERS].push_back(SINK);
	adj[SINK].push_back(OTHERS);
}

int compute_maxflow(){
	int totalflow = 0;
	int curflow;
	int parent[MAXV];
	std::deque<int> q;

	memset(flow, 0, sizeof(flow));

	while(true){
		std::fill(&parent[0], &parent[MAXV], -1);
		parent[SOURCE] = SOURCE;

		q.clear();
		q.push_back(SOURCE);
		while(!q.empty() && parent[SINK] == -1){
			int cur = q.front(); q.pop_front();
			for(int nxt:adj[cur]){
				if(capacity[cur][nxt] - flow[cur][nxt] > 0 && parent[nxt] == -1){
					parent[nxt] = cur;
					q.push_back(nxt);
				}
			}
		}

		if(parent[SINK] == -1){
			break;
		}

		curflow = INF;
		for(int cur=SINK; cur != SOURCE; cur = parent[cur]){
			curflow = std::min(curflow, capacity[parent[cur]][cur] - flow[parent[cur]][cur]);
		}
		for(int cur=SINK; cur != SOURCE; cur = parent[cur]){
			flow[parent[cur]][cur] += curflow;
			flow[cur][parent[cur]] -= curflow;
		}

		totalflow += curflow;
	}

	return totalflow;
}

bool possible(int numwin){
	int total_p0_win = input_win[0]+numwin;
	for(int p=1; p<N; ++p){
		// printf("%d %d\n", input_win[p], total_p0_win);
		if(input_win[p] >= total_p0_win){
			return false;
		}
	}

	capacity[PLAYER+0][SINK] = numwin;
	for(int p=1; p<N; ++p){
		capacity[PLAYER+p][OTHERS] = total_p0_win - input_win[p] - 1;
	}
	capacity[OTHERS][SINK] = M-numwin;

	return compute_maxflow() == M;
}

void solve(){
	build_graph();

	for(int w=0; w <= maxwin[0]; ++w){
		if(possible(w)){
			printf("%d\n",input_win[0]+w);
			return;
		}
	}
	printf("-1\n");
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d %d", &N, &M);
		for(int j=0; j<N; ++j){
			scanf("%d", &input_win[j]);
		}
		for(int j=0; j<M; ++j){
			scanf("%d %d", &input_edge[j][0], &input_edge[j][1]);
		}
		solve();
	}
}