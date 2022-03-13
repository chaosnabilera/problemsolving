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

int DP[1<<24];

void precompute(){
	int mask[12] = {0};
	int final_state = (1<<24)-1; // everything is on right side
	queue<pair<int,int>> bfsq;

	for(int i=0; i<12; ++i){
		mask[i] = (1<<24)-1;
		mask[i] ^= (3 << (i*2));
	}
	memset(DP,0xFF,sizeof(DP));
	bfsq.push(make_pair(final_state,0));
	
	int cnt = 0;
	while(!bfsq.empty()){
		int state = bfsq.front().first;
		int steps = bfsq.front().second;
		bfsq.pop();

		if(DP[state] != -1)
			continue;

		++cnt;
		// if(cnt % 10000 == 0)
		// 	printf("%d\n",cnt);

		DP[state] = steps;
		// printf("%d\n",state);

		int top[4] = {0xFFFF,0xFFFF,0xFFFF,0xFFFF};
		for(int i = 11; i >= 0; --i){
			int q = (state >> (i*2)) & 0x3;
			top[q] = min(top[q],i);
		}

		for(int i=0; i<4; ++i){
			if(top[i] == 0xFFFF)
				continue;
			for(int j=0; j<4; ++j){
				if(top[i] < top[j]){
					int next_state = state;
					int ti = top[i];
					next_state &= mask[ti];
					next_state |= (j << (ti*2));

					if(DP[next_state] == -1){
						bfsq.push(make_pair(next_state,steps+1));
					}
				}
			}
		}
	}
}

void solve(){
	int n, cnt, istate, v;
	scanf("%d", &n);

	istate = 0;
	for(int i=0; i<4; ++i){
		scanf("%d", &cnt);
		for(int j=0; j<cnt; ++j){
			scanf("%d", &v);
			--v; // change to 0-indexed
			istate |= (i << (2*v));
		}
	}
	for(int i=n; i<12; ++i){
		istate |= (3 << (2*i));
	}

	printf("%d\n", DP[istate]);
}

int main(int argc, char** argv){
	int c;
	precompute();
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		solve();
	}
}