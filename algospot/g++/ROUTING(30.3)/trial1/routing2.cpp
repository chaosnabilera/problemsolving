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
#include <cmath>

int T,N,M;
std::vector<unsigned int> adj[10000];
std::unordered_map<unsigned int, double> logweight;
double minweight[10000];
bool visited[10000];

void solve(){
	std::priority_queue<
		std::pair<double,unsigned int>,
		std::vector<std::pair<double,unsigned int>>,
		std::greater<std::pair<double,unsigned int>>
	> minq;

	minweight[0] = 0;
	visited[0] = true;
	for(unsigned int n:adj[0]){
		minq.push(std::make_pair(logweight[n],n));
	}

	while(!minq.empty()){
		auto cp = minq.top(); minq.pop();
		double w = cp.first;
		unsigned int a = cp.second >> 16;
		unsigned int b = cp.second & 0xFFFF;

		if(visited[b]){
			continue;
		}
		visited[b] = true;
		minweight[b] = w;
		if(b == N-1){
			break;
		}

		for(unsigned int n:adj[b]){
			if(!visited[n]){
				unsigned int e = (b<<16)|n;
				minq.push(std::make_pair(minweight[b]+logweight[e], e));
			}
		}
	}

	printf("%.10lf\n", exp(minweight[N-1]));
}

int main(int argc, char** argv){
	unsigned int a,b,e1,e2;
	double c;

	scanf("%d", &T);
	for(int t=0; t<T; ++t){
		scanf("%d %d", &N, &M);
		for(int i=0; i<N; ++i){
			adj[i].clear();
			minweight[i] = 0;
			visited[i] = false;
		}
		logweight.clear();
		for(int i=0; i<M; ++i){
			scanf("%u %u %lf", &a, &b, &c);
			e1 = (a<<16) | b;
			e2 = (b<<16) | a;
			c = log(c);
			if(logweight.find(e1) == logweight.end()){
				adj[a].push_back(b);
				adj[b].push_back(a);
				logweight[e1] = c;
				logweight[e2] = c;
			}
			else if(c < logweight[e1]){
				logweight[e1] = c;
				logweight[e2] = c;
			}
		}
		solve();
	}
}