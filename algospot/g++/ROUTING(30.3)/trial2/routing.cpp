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
#include <cmath>

using namespace std;

int N, M;
vector<pair<double,int>> Adj[10000];

void get_input(){
	int a, b;
	double v;
	scanf("%d %d", &N, &M);
	
	for(int i=0; i<N; ++i)
		Adj[i].clear();

	for(int i=0; i<M; ++i){
		scanf("%d %d %lf",&a,&b,&v);
		v = log(v);
		Adj[a].push_back(make_pair(v,b));
		Adj[b].push_back(make_pair(v,a));
	}
}

void solve(){
	bool visited[10000];
	priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> pq;

	memset(visited,0,N);
	visited[0] = true;

	for(auto p:Adj[0])
		pq.push(p);

	while(!pq.empty()){
		auto cp = pq.top(); pq.pop();
		double cost = cp.first;
		int cur = cp.second;

		// printf("%lf %lf %d\n",cost,exp(cost),cur);

		if(visited[cur])
			continue;

		if(cur == N-1){
			printf("%.10lf\n",exp(cost));
			return;
		}

		visited[cur] = true;
		for(auto nxt:Adj[cur]){
			pq.push(make_pair(cost+nxt.first, nxt.second));
		}
	}
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}