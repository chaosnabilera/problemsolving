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

int T,V,E,N,M;

int mindist[1001];
bool visited[1001];
int weight[1001][1001];
std::unordered_set<unsigned int> fire;
std::unordered_set<unsigned int> station;
std::vector<unsigned int> adj[1001];

void solve(){
	std::priority_queue<
		std::pair<int,unsigned int>,
		std::vector<std::pair<int,unsigned int>>,
		std::greater<std::pair<int,unsigned int>>
	> minq;

	for(unsigned int s:station){
		mindist[s] = 0;
		visited[s] = true;
		for(unsigned int n:adj[s]){
			unsigned int sn = (s<<16) | n;
			minq.push(std::make_pair(weight[s][n], sn));
		}
	}

	while(!minq.empty()){
		auto cp = minq.top(); minq.pop();
		int w = cp.first;
		unsigned int a = cp.second >> 16;
		unsigned int b = cp.second & 0xFFFF;

		if(visited[b]){
			continue;
		}

		visited[b] = true;
		mindist[b] = w;
		for(unsigned int n:adj[b]){
			if(!visited[n]){
				unsigned int bn = (b<<16) | n;
				minq.push(std::make_pair(mindist[b]+weight[b][n],bn));
			}
		}
	}

	int sum = 0;
	for(auto f:fire){
		sum += mindist[f];
	}

	printf("%d\n",sum);
}

int main(int argc, char** argv){
	unsigned int a,b,w;

	scanf("%d", &T);
	for(int t=0; t<T; ++t){
		scanf("%d %d %d %d", &V, &E, &N, &M);

		fire.clear();
		station.clear();
		for(int i=1; i<=V; ++i){
			adj[i].clear();
			visited[i] = false;
		}
		for(int i=0; i<E; ++i){
			scanf("%u %u %u", &a, &b, &w);
			adj[a].push_back(b);
			adj[b].push_back(a);
			weight[a][b] = w;
			weight[b][a] = w;
		}
		for(int i=0; i<N; ++i){
			scanf("%u",&a);
			fire.insert(a);
		}
		for(int i=0; i<M; ++i){
			scanf("%u",&a);
			station.insert(a);
		}

		solve();
	}
}