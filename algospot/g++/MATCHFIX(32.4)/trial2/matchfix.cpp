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
#include <cstring>

using namespace std;

const int SOURCE = 0;
const int LIMIT = 1;
const int MATCH = 2;
const int PLAYER = 102;
const int SINK = 114;

const int INF = 987654321;

int N, M;
int InitWin[12];
vector<pair<int,int>> Match;

int Capacity[115][115];
int Flow[115][115];

vector<int> Adj[115];

void get_input(){
	int a,b;

	scanf("%d %d", &N, &M);

	for(int i=0; i<N; ++i)
		scanf("%d", &InitWin[i]);

	Match.clear();
	Match.reserve(M);
	for(int i=0; i<M; ++i){
		scanf("%d %d", &a, &b);
		Match.push_back(make_pair(a,b));
	}
}

void build_adj(){
	for(int i=0; i<115; ++i)
		Adj[i].clear();

	Adj[SOURCE].push_back(LIMIT);
	Adj[LIMIT].push_back(SOURCE);
	for(int i=0; i<M; ++i){
		Adj[LIMIT].push_back(MATCH+i);
		Adj[MATCH+i].push_back(LIMIT);
	}

	for(int i=0; i<M; ++i){
		int a = Match[i].first;
		int b = Match[i].second;
		Adj[MATCH+i].push_back(PLAYER+a);
		Adj[MATCH+i].push_back(PLAYER+b);
		Adj[PLAYER+a].push_back(MATCH+i);
		Adj[PLAYER+b].push_back(MATCH+i);
	}

	for(int i=0; i<N; ++i){
		Adj[PLAYER+i].push_back(SINK);
		Adj[SINK].push_back(PLAYER+i);
	}
}

int compute_necessary_win(){
	int maxwin = InitWin[1];
	for(int i=2; i<N; ++i)
		maxwin = max(maxwin,InitWin[i]);

	return max(maxwin - InitWin[0] + 1, 0);
}

int possible_max_win(){
	int cnt = 0;
	for(pair<int,int>& p:Match){
		if(p.first == 0 || p.second == 0)
			++cnt;
	}
	return cnt;
}

bool possible(int win0){
	int parent[144];
	int win_limit = InitWin[0]+win0-1;

	// construct capacity
	memset(Capacity,0,sizeof(Capacity));
	memset(Flow,0,sizeof(Flow));
	Capacity[SOURCE][LIMIT] = M;
	for(int i=0; i<M; ++i){
		Capacity[LIMIT][MATCH+i] = 1;
		for(int p:Adj[MATCH+i])
			Capacity[MATCH+i][p] = 1;
	}
	Capacity[PLAYER+0][SINK] = win0;
	for(int i=1; i<N; ++i)
		Capacity[PLAYER+i][SINK] = win_limit-InitWin[i];

	// compute max flow
	while(true){
		bool found = false;

		for(int i=1; i<144; ++i)
			parent[i] = -1;

		parent[SOURCE] = SOURCE;
		queue<int> q;
		q.push(SOURCE);

		while(!q.empty() && parent[SINK] == -1){
			int cur = q.front(); q.pop();
			// printf("<%d>\n",cur);
			for(int nxt:Adj[cur]){
				if(parent[nxt] != -1 || Capacity[cur][nxt] - Flow[cur][nxt] <= 0)
					continue;
				parent[nxt] = cur;
				q.push(nxt);
				if(nxt == SINK)
					break;
			}
		}

		if(parent[SINK] == -1)
			break;

		int node = SINK;
		int minres = INF;
		while(node != SOURCE){
			minres = min(minres, Capacity[parent[node]][node] - Flow[parent[node]][node]);
			node = parent[node];
		}

		node = SINK;
		while(node != SOURCE){
			Flow[parent[node]][node] += minres;
			Flow[node][parent[node]] -= minres;
			node = parent[node];
		}
	}

	return Flow[SOURCE][LIMIT] == M;
}

void solve(){
	int minwin = compute_necessary_win();
	int maxwin = possible_max_win();

	// printf("%d %d\n",minwin,maxwin);

	if(minwin > maxwin){
		printf("-1\n");
		return;
	}

	build_adj();

	for(int w=minwin; w <= maxwin; ++w){
		if(possible(w)){
			printf("%d\n",InitWin[0]+w);
			return;
		}
	}

	printf("-1\n");
}

int main(int argc, char** argv){
	int C;
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		solve();
	}
}