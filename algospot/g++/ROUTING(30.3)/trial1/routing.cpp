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

int C,N,M;
std::vector<unsigned int> adj[10000];
std::unordered_map<unsigned int, double> weight;
double minweight[10000];

void solve(){
	std::priority_queue<
		std::pair<double, unsigned int>,
		std::vector<std::pair<double, unsigned int>>,
		std::greater<std::pair<double, unsigned int>>
	> minq;

	minweight[0] = 1;

	for(unsigned int n:adj[0]){
		minq.push(std::make_pair(weight[n],n));
	}

	while(!minq.empty()){
		auto curpair = minq.top(); minq.pop();
		double w = curpair.first;
		unsigned int e = curpair.second;
		unsigned int a = (e >> 16);
		unsigned int b = (e & 0xFFFF);

		// printf("%d %d %lf\n",a,b,w);
		if(w >= minweight[b]){
			continue;
		}
		// printf("%d\n",b);
		minweight[b] = w;
		if(b == N-1){
			printf("%.10lf\n", minweight[b]);
			break;
		}

		for(auto n:adj[b]){
			// printf("%d %d\n",b,n);
			unsigned int bn = (b << 16) | n;
			double bweight = minweight[b]*weight[bn];
			minq.push(std::make_pair(bweight,bn));
		}
	}
}

int main(int argc, char** argv){
	unsigned int aa,bb;
	double cc;
	unsigned int e1, e2;

	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d %d", &N, &M);
		for(int n=0; n<N; ++n){
			adj[n].clear();
			minweight[n] = std::numeric_limits<double>::max();
		}
		weight.clear();

		for(int m=0; m<M; ++m){
			scanf("%u %u %lf", &aa, &bb, &cc);
			e1 = (aa << 16) | bb;
			e2 = (bb << 16) | aa;

			if(weight.find(e1) == weight.end()){
				adj[aa].push_back(bb);
				adj[bb].push_back(aa);
				weight[e1] = cc;
				weight[e2] = cc;
			}
			else{
				weight[e1] = std::min(cc,weight[e1]);
				weight[e2] = std::min(cc,weight[e2]);
			}
		}

		solve();
	}
}