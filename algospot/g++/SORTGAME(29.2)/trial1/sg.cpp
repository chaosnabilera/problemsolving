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

int C, N;
bool did_precompute[9];
int inum[8];
int snum[8];
int iorder[8];

std::unordered_map<int,int> cost;

void standardize_input(){
	std::unordered_map<int,int> order;
	for(int i=0; i<N; ++i){
		snum[i] = inum[i];
	}
	std::sort(&snum[0],&snum[N]);
	for(int i=0; i<N; ++i){
		order[snum[i]] = i+1;
	}
	for(int i=0; i<N; ++i){
		iorder[i] = order[inum[i]];
	}
}

int vec_to_num(std::vector<char>& ivec){
	int ret = 0;
	for(int i=0; i<ivec.size(); ++i){
		ret = (ret*10)+ivec[i];
	}
	return ret;
}

void printvec(std::vector<char>& ivec){
	for(auto i:ivec){
		printf("%d ", i);
	}
	printf("\n");
}

void precompute(int S){
	std::vector<char> start_value;
	for(int i=1; i<=S; ++i){
		start_value.push_back(i);
	}

	cost[vec_to_num(start_value)] = 0;

	std::queue<std::pair<std::vector<char>,int>> q;
	q.push(std::make_pair(start_value,0));

	while(!q.empty()){
		auto curpair = q.front(); q.pop();
		std::vector<char>& curvec = curpair.first;
		int curcost = curpair.second;

		// printvec(curvec);
		// printf("%d\n", vec_to_num(curvec));

		for(int beg=0; beg<S-1; ++beg){
			for(int end=beg+1; end<S; ++end){
				std::vector<char> flip = curvec;
				std::reverse(&flip[beg],&flip[end+1]);
				int flip_num = vec_to_num(flip);
				if(cost.find(flip_num) == cost.end()){
					cost[flip_num] = curcost+1;
					q.push(std::make_pair(flip,curcost+1));
				}
			}
		}
	}

	did_precompute[S] = true;
}

void solve(){
	if(!did_precompute[N]){
		precompute(N);
	}
	standardize_input();
	int cur = 0;
	for(int i=0; i<N; ++i){
		cur = (cur*10)+iorder[i];
	}
	// printf("%d\n",cur);
	printf("%d\n", cost[cur]);
}

int main(int argc, char** argv){
	memset(did_precompute, 0, sizeof(did_precompute));
	
	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d", &N);
		for(int i=0; i<N; ++i){
			scanf("%d", &inum[i]);
		}
		solve();
	}
}