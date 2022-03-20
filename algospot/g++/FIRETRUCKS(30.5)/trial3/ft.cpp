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

int V,E,N,M;
vector<vector<pair<int,int>>> Adj;
vector<int> F;
vector<int> S;

void get_input(){
	int a,b,t;

	scanf("%d%d%d%d",&V,&E,&N,&M);

	Adj.clear();
	Adj.resize(V);
	for(int i=0; i<E; ++i){
		scanf("%d%d%d",&a,&b,&t);
		--a;
		--b;
		Adj[a].push_back(make_pair(b,t));
		Adj[b].push_back(make_pair(a,t));
	}

	F.clear();
	F.resize(N);
	for(int i=0; i<N; ++i){
		scanf("%d",&F[i]);
		--F[i];
	}

	S.clear();
	S.resize(M);
	for(int i=0; i<M; ++i){
		scanf("%d",&S[i]);
		--S[i];
	}
}

void solve(){
	const int INF = numeric_limits<int>::max();
	vector<int> dist(V, INF);
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> minq;

	for(int s:S)
		minq.push(make_pair(0,s));

	while(!minq.empty()){
		auto p = minq.top(); minq.pop();
		int cost = p.first;
		int cur = p.second;

		if(dist[cur] <= cost)
			continue;

		dist[cur] = cost;

		for(int i=0; i<Adj[cur].size(); ++i){
			int nxt = Adj[cur][i].first;
			int nxt_dist = dist[cur] + Adj[cur][i].second;
			if(nxt_dist < dist[nxt])
				minq.push(make_pair(nxt_dist,nxt));
		}
	}

	int sum = 0;
	for(int f:F)
		sum += dist[f];

	printf("%d\n",sum);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}