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

int N,S;
int iLine[100];
int iSum[100];
int iSqSum[100];

int dp_sqsum[100][100];
int dp[100][11];

/* stupid version
int sqsum(int beg, int end){
	if(dp_sqsum[beg][end] != -1)
		return dp_sqsum[beg][end];

	double partial_sum = (beg == 0) ? iSum[end] : iSum[end]-iSum[beg-1];
	int avg = int((partial_sum/(end-beg+1))+0.5);

	int res = 0;
	int x;
	for(int i=beg; i<=end; ++i){
		x = iLine[i]-avg;
		res += (x*x);
	}

	dp_sqsum[beg][end] = res;
	return dp_sqsum[beg][end];
}
*/

int sqsum(int beg, int end){
	double partial_sum;
	int partial_sqsum, n, avg;

	if(beg == 0){
		partial_sum = iSum[end];
		partial_sqsum = iSqSum[end];
	}
	else{
		partial_sum = iSum[end]-iSum[beg-1];
		partial_sqsum = iSqSum[end]-iSqSum[beg-1];
	}
	n = end-beg+1;
	avg = int((partial_sum/n)+0.5);

	return (n*(avg*avg)) - (2*avg*partial_sum) + partial_sqsum;
}

int rec_solve(int beg, int s){
	if(dp[beg][s] != -1){
		return dp[beg][s];
	}

	if(N-beg <= s){
		dp[beg][s] = 0;
	}
	else if(s == 1){
		dp[beg][s] = dp_sqsum[beg][N-1];
	}
	else{
		dp[beg][s] = BIGNUM;
		for(int nxt=beg+1; nxt<N; ++nxt){
			dp[beg][s] = min(dp[beg][s], dp_sqsum[beg][nxt-1]+rec_solve(nxt,s-1));
		}
	}

	return dp[beg][s];
}

void print_arr(int* arr){
	for(int i=0; i<N; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void print_dp(){
	for(int s=1; s<=S; ++s){
		for(int i=0; i<N; ++i){
			printf("%d ", dp[i][s]);
		}
		printf("\n");
	}
	printf("\n");
}

void solve(){
	sort(&iLine[0], &iLine[N]);
	// print_arr(iLine);

	iSum[0] = iLine[0];
	iSqSum[0] = iLine[0]*iLine[0];
	for(int i=1; i<N; ++i){
		iSum[i] = iSum[i-1]+iLine[i];
		iSqSum[i] = iSqSum[i-1]+(iLine[i]*iLine[i]);
	}

	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j)
			dp_sqsum[i][j] = sqsum(i,j);

	for(int i=0; i<N; ++i)
		for(int j=1; j<=S; ++j)
			dp[i][j] = -1;

	printf("%d\n", rec_solve(0,S));

	// print_dp();
}

int main(int argc, char** argv){
	int C;
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d %d", &N, &S);
		for(int j=0; j<N; ++j)
			scanf("%d", &iLine[j]);
		solve();
	}
}