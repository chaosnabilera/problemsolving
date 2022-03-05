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

const long long MODNUM = 10000000;

long long dp[101][101];
long long dp_ans[101];

long long rec_poly(int h, int n);

long long ans(int N){
	if(dp_ans[N] != -1)
		return dp_ans[N];

	long long cnt = 0;
	for(int h=1; h<=N; ++h){
		long long cur = rec_poly(h,N-h);
		// printf("rec_poly(%d,%d):%d\n", h,N-h,cur);
		cnt += cur;
		cnt %= MODNUM;
	}
	dp_ans[N] = cnt;
	return dp_ans[N];
}

long long rec_poly(int h, int n){
	if(dp[h][n] != -1)
		return dp[h][n];

	long long cnt = h+n-1; // case where we spend all n for single line
	for(int h0 = 1; h0 <= n; ++h0){
		for(int h1 = 1; h1 <= n-h0; ++h1){
			cnt += (h+h0-1) * (h0+h1-1) * rec_poly(h1,n-h0-h1);
			cnt %= MODNUM;
		}
	}
	dp[h][n] = cnt;
	return dp[h][n];
}

int main(int argc, char** argv){
	int C, N;

	for(int h=0; h<=100; ++h)
		for(int n=0; n<=100; ++n)
			dp[h][n] = -1;
	dp[0][0] = 0;
	for(int h=1; h<=100; ++h)
		dp[h][0] = 1;

	for(int n=0; n<=100; ++n)
		dp_ans[n] = -1;
	dp_ans[0] = 0;
	dp_ans[1] = 1;

	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d", &N);
		printf("%lld\n", ans(N));
	}
}