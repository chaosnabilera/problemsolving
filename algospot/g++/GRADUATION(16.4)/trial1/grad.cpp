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

using namespace std;

const int BIGNUM = 987654321;

int BitCnt[(1<<12)];
int DP[(1<<12)][11];

int N,K,M,L;
int Req[12];
vector<int> Sem[10];

void get_input(){
	int cnt, num;
	scanf("%d %d %d %d", &N, &K, &M, &L);
	for(int i=0; i<N; ++i){
		Req[i] = 0;
		scanf("%d", &cnt);
		for(int j=0; j<cnt; ++j){
			scanf("%d", &num);
			Req[i] |= (1<<num);
		}
		// printf("Req[%d]:%d\n",i,Req[i]);
	}

	for(int i=0; i<M; ++i){
		Sem[i].clear();
		scanf("%d", &cnt);
		for(int j=0; j<cnt; ++j){
			scanf("%d", &num);
			Sem[i].push_back(num);
		}
	}
}

void precompute(){
	for(int i=0; i<(1<<12); ++i){
		BitCnt[i] = 0;
		for(int b=0; b<12; ++b){
			if(i & (1<<b))
				++BitCnt[i];
		}
	}
}

int rec_solve(int mask, int si){
	if(DP[mask][si] != -1){
		return DP[mask][si];
	}

	// printf("%d %d\n", mask, si);

	if(BitCnt[mask] >= K){
		// printf("%d %d res:%d\n",mask,si,0);
		DP[mask][si] = 0;
		return 0;
	}

	if(si >= M){
		DP[mask][si] = BIGNUM;
		return BIGNUM;
	}

	int can_take = 0;
	// printf("%d: ",si);
	for(int r:Sem[si]){
		if(mask & (1<<r)){
			// printf("%d(T) ",r);
			continue;
		}
		// printf("%d(F) ",r);
		if((Req[r] & mask) == Req[r]){
			can_take |= (1<<r);
		}
	}
	// printf("\n");

	// printf("%d %d %d %d\n", mask, si, can_take, BitCnt[can_take]);

	int res = rec_solve(mask, si+1);
	int cur_take = can_take;
	int max_cnt = min(L, BitCnt[can_take]);
	while(cur_take){
		// printf("%d\n",cur_take);
		if(BitCnt[cur_take] == max_cnt){
			// printf("%d %d res: %d\n", mask, si, res);
			res = min(res, 1 + rec_solve(mask | cur_take, si+1));
			// printf("%d %d res: %d\n", mask, si, res);
		}
		cur_take = (cur_take-1) & can_take;
	}

	DP[mask][si] = res;

	// printf("%d %d res: %d\n", mask, si, res);
	return res;
}

void solve(){
	for(int mask=0; mask < (1<<N); ++mask){
		for(int si=0; si <= M; ++si){
			DP[mask][si] = -1;
		}
	}
	rec_solve(0,0);
	if(DP[0][0] > M){
		printf("IMPOSSIBLE\n");
	}
	else{
		printf("%d\n", DP[0][0]);
	}
}

int main(int argc, char** argv){
	int T;
	precompute();
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}