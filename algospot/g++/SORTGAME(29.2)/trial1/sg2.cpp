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

std::unordered_map<unsigned long long, int> cost;
bool precompute_done[9];

void precompute(int S){
	char start_value[8] = {0};
	std::queue<std::pair<unsigned long long, int>> bfs;

	for(int i=0; i<S; ++i){	start_value[i] = i+1; }

	bfs.push(std::make_pair(*((unsigned long long*)start_value), 0));
	cost[*((unsigned long long*)start_value)] = 0;

	while(!bfs.empty()){
		auto curpair = bfs.front(); bfs.pop();
		unsigned long long sval = curpair.first;
		int sdepth = curpair.second;

		for(int beg=0; beg < S-1; ++beg){
			for(int end=beg+2; end <= S; ++end){
				unsigned long long flipval = sval;
				char* farr = (char*)&flipval;
				std::reverse(&farr[beg], &farr[end]);
				if(cost.find(flipval) == cost.end()){
					cost[flipval] = sdepth+1;
					bfs.push(std::make_pair(flipval, sdepth+1));		
				}
			}
		}
	}

	precompute_done[S] = true;
}

void solve(int iarr[8], int N){
	int sarr[8] = {0};
	char tarr[8] = {0};
	std::unordered_map<int, char> order;

	if(!precompute_done[N]){
		precompute(N);
	}

	for(int i=0; i<N; ++i){
		sarr[i] = iarr[i];
	}
	
	std::sort(&sarr[0], &sarr[N]);
	for(char i=0; i<N; ++i){
		order[sarr[i]] = i+1;
	}
	for(int i=0; i<N; ++i){
		tarr[i] = order[iarr[i]];
	}

	printf("%d\n", cost[*((unsigned long long*)&tarr)]);
}

int main(int argc, char** argv){
	int C,N;
	int iarr[8];
	memset(precompute_done,0,sizeof(precompute_done));

	scanf("%d",&C);
	for(int c=0; c<C; ++c){
		scanf("%d", &N);
		for(int n=0; n<N; ++n){
			scanf("%d", &iarr[n]);
		}
		solve(iarr, N);
	}
}