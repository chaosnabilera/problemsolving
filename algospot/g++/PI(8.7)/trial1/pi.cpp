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

int N;
char iLine[10001];
int dp[10001];

int same(int beg, int cnt){
	for(int i=1; i<cnt; ++i){
		if(iLine[beg] != iLine[beg+i])
			return 987654321;
	}
	return 1;
}

int is_plus(int beg, int cnt){
	for(int i=1; i<cnt; ++i){
		if(iLine[beg+i] != iLine[beg]+i)
			return 987654321;
	}
	return 2;
}

int is_minus(int beg, int cnt){
	for(int i=1; i<cnt; ++i){
		if(iLine[beg+i] != iLine[beg]-i)
			return 987654321;
	}
	return 2;
}

int is_flip(int beg, int cnt){
	char comp[2] = {iLine[beg], iLine[beg+1]};
	for(int i=2; i<cnt; ++i){
		if(iLine[beg+i] != comp[i&1])
			return 987654321;
	}
	return 4;
}

int is_step(int beg, int cnt){
	char d = iLine[beg+1] - iLine[beg];
	for(int i=2; i<cnt; ++i){
		if(iLine[beg+i]-iLine[beg+i-1] != d)
			return 987654321;
	}
	return 5;
}

void solve(){
	N = strlen(iLine);
	for(int i=0; i<N; ++i)
		dp[i] = BIGNUM;
	dp[N] = 0;

	for(int beg=N-3; beg >= 0; --beg){
		for(int cnt=3; cnt<=5; ++cnt){
			if(beg+cnt > N)
				continue;
			int prev = dp[beg+cnt];
			dp[beg] = min(dp[beg], 10+prev);
			dp[beg] = min(dp[beg], same(beg,cnt)+prev);
			dp[beg] = min(dp[beg], is_plus(beg,cnt)+prev);
			dp[beg] = min(dp[beg], is_minus(beg,cnt)+prev);
			dp[beg] = min(dp[beg], is_flip(beg,cnt)+prev);
			dp[beg] = min(dp[beg], is_step(beg,cnt)+prev);
		}
		// printf("dp[%d]:%d\n", beg, dp[beg]);
	}

	printf("%d\n", dp[0]);
}

int main(int argc, char** argv){
	int C;
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%s", iLine);
		solve();
	}
}