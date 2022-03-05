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

int C, N, M;

int iCost[20];
int iScore[20];
int dp[10000001];

int rec_solve(int budget){
	if(dp[budget] != -1)
		return dp[budget];

	int best = 0;
	for(int i=0; i<N; ++i){
		if(iCost[i] <= budget){
			best = max(best, iScore[i]+rec_solve(budget-iCost[i]));
		}
	}
	// printf("%d:%d\n",budget,best);
	dp[budget] = best;
	return best;
}

void get_input(){
	int cost, score;
	scanf("%d %d", &N, &M);
	M /= 100;
	for(int i=0; i<N; ++i){
		scanf("%d %d", &iCost[i], &iScore[i]);
		iCost[i] /= 100;
	}
}

void solve(){
	for(int i=1; i<=M; ++i)
		dp[i] = -1;

	dp[0] = 0;
	for(int budget=1; budget<=M; ++budget){
		rec_solve(budget);
	}

	printf("%d\n", dp[M]);
}

// bool custom_compare(pair<int,int> p1, pair<int,int> p2){
// 	if(p1.first == p2.first){
// 		return (p1.second > p2.second);
// 	}
// 	return (p1.first < p2.first);
// }

// void precompute(){
// 	pair<int,int> cs[20];
// 	bool necessary[20] = { false };
// 	int c1,s1,c2,s2;

// 	for(int i=0; i<N; ++i){
// 		cs[i].first  = iCost[i];
// 		cs[i].second = iScore[i];
// 		necessary[i] = true;
// 	}

// 	sort(&cs[0], &cs[N], custom_compare);
// 	for(int i=0; i<N; ++i){
// 		if(!necessary[i])
// 			continue;
// 		c1 = cs[i].first;	s1 = cs[i].second;
// 		for(int j=i+1; j<N; ++j){
// 			c2 = cs[j].first; s2 = cs[j].second;
// 			if((c1/c2)*s1 >= s2){
// 				necessary[j] = false;
// 			}
// 		}
// 	}

// 	N = 0;
// 	for(int i=0; i<20; ++i){
// 		if(necessary[i]){
// 			++N;
// 			iCost[i]  = cs[i].first;
// 			iScore[i] = cs[i].second;
// 		}
// 	}
// }

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		// precompute();
		solve();
	}
}