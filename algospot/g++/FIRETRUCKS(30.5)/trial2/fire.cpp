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

int V, E, N, M;
vector<pair<int,int>> Adj[1000];
vector<int> Station;
bool IsF[1000];

void get_input(){
	int a,b,t,p;
	scanf("%d %d %d %d",&V, &E, &N, &M);

	for(int i=0; i<V; ++i)
		Adj[i].clear();

	for(int i=0; i<E; ++i){
		scanf("%d %d %d", &a, &b, &t);
		--a;
		--b;
		Adj[a].push_back(make_pair(t,b));
		Adj[b].push_back(make_pair(t,a));
	}

	memset(IsF,0,sizeof(IsF));

	for(int i=0; i<N; ++i){
		scanf("%d",&p);
		--p;
		IsF[p] = true;
	}

	Station.clear();
	for(int i=0; i<M; ++i){
		scanf("%d",&p);
		--p;
		Station.push_back(p);
	}

	// printf("%d %d %d %d\n",V,E,N,M);
}

void solve(){
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	bool visited[1000] = {0};
	int fire_left = N;

	for(int s:Station){
		visited[s] = true;
		for(auto p:Adj[s])
			pq.push(p);
	}

	int ans = 0;
	while(!pq.empty()){
		auto p = pq.top(); pq.pop();
		int cost = p.first;
		int cur = p.second;

		if(visited[cur])
			continue;

		visited[cur] = true;
		if(IsF[cur]){
			ans += cost;
			fire_left--;
			if(fire_left == 0)
				break;
		}

		for(auto nxt:Adj[cur]){
			pq.push(make_pair(cost+nxt.first,nxt.second));
		}
	}

	printf("%d\n",ans);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}