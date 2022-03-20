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

int N,M;
vector<vector<pair<int,double>>> Adj;

template <typename T>
vector<pair<int, T>> dijkstra(vector<vector<pair<int, T>>>& adj, int src, int dst = -1){
	const T INF = numeric_limits<T>::max();
	vector<T> dist(adj.size(), INF);
	priority_queue<pair<T,int>,vector<pair<T,int>>,greater<pair<T,int>>> minq;
	vector<pair<int,T>> ans;

	minq.push(make_pair(0,src));
	while(!minq.empty()){
		auto p = minq.top(); minq.pop();
		T cost = p.first;
		int cur = p.second;

		if(dist[cur] <= cost)
			continue;

		dist[cur] = cost;
		ans.push_back(make_pair(cur,dist[cur]));

		if(cur == dst)
			break;

		for(int i=0; i<adj[cur].size(); ++i){
			int nxt = adj[cur][i].first;
			T nxt_dist = dist[cur] + adj[cur][i].second;
			if(nxt_dist < dist[nxt])
				minq.push(make_pair(nxt_dist,nxt));
		}
	}
	return ans;
}

void get_input(){
	int a,b;
	double c;
	scanf("%d%d",&N,&M);

	Adj.clear();
	Adj.resize(N);
	for(int i=0; i<M; ++i){
		scanf("%d%d%lf",&a,&b,&c);
		c = log(c);
		Adj[a].push_back(make_pair(b,c));
		Adj[b].push_back(make_pair(a,c));
	}
}

void solve(){
	vector<pair<int,double>> ans = dijkstra<double>(Adj,0,N-1);
	double ans_dist = ans.back().second;
	printf("%.10lf\n", exp(ans_dist));
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}