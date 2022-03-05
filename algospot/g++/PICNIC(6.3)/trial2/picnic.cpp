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

using namespace std;

int N,M;
bool IsFriend[10][10];
int DP[(1<<10)];

void get_input(){
	int a,b;
	scanf("%d %d", &N, &M);
	memset(IsFriend,0,sizeof(IsFriend));
	for(int i=0; i<M; ++i){
		scanf("%d %d", &a, &b);
		IsFriend[a][b] = true;
		IsFriend[b][a] = true;
	}
}

int rec_solve(int state){
	if(DP[state] != -1)
		return DP[state];

	int cnt = 0;
	for(int i=0; i<N; ++i){
		if(state & (1<<i)){
			for(int j=i+1; j<N; ++j){
				if((state & (1<<j)) && IsFriend[i][j]){
					int next_state = state;
					next_state ^= (1<<i);
					next_state ^= (1<<j);
					cnt += rec_solve(next_state);
				}
			}
			break;
		}
	}

	// printf("state:%d cnt:%d\n",state,cnt);

	DP[state] = cnt;
	return cnt;
}

void solve(){
	int ilim = 1<<N;
	for(int i=0; i<ilim; ++i)
		DP[i] = -1;

	DP[0] = 1;

	printf("%d\n", rec_solve((1<<N)-1));
}

int main(int argc, char** argv){
	int C;
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		solve();
	}
}