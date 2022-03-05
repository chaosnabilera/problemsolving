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
#include <cmath>

using namespace std;

int C, N, K, M;
int sLen[50];
float prob[50][50];
int sLike[10];

void get_input(){
	scanf("%d %d %d", &N, &K, &M);
	for(int i=0; i<N; ++i)
		scanf("%d", &sLen[i]);

	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			scanf("%f", &prob[i][j]);
		}
	}

	for(int i=0; i<M; ++i){
		scanf("%d", &sLike[i]);
	}
}

void print_table(float dp[][50]){
	for(int i=0; i<N; ++i){
		for(int s=0; s<8; ++s){
			printf("%.8f ", dp[s][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void solve(){
	float dp[8][50] = {0};
	int s = 0; //circular queue starting point

	// base case
	dp[0][0] = 1;
	for(int i=0; i<N; ++i)
		dp[sLen[0]][i] = prob[0][i];

	// print_table(dp);

	s = sLen[0]+1;
	for(int _l=sLen[0]+1; _l<=K; ++_l){
		// printf("t=%d\n",_l);
		for(int i=0; i<N; ++i){
			float p = 0;
			for(int j=0; j<N; ++j){
				if(sLen[j]>_l)
					continue;
				int js = (8+s-sLen[j]) & 0x7;
				// printf("\t%d->%d : s:%d dp[%d][%d]:%lf prob[%d][%d]:%lf x:%lf\n",
					// j,i,s,js,j,dp[js][j],j,i,prob[j][i],dp[js][j]*prob[j][i]);
				p += dp[js][j]*prob[j][i];
			}
			// printf("\tp=%.8lf\n",p);
			dp[s][i] = p;
		}
		// print_table(dp);
		s = (s+1)&0x7;
	}

	s = (8+s-1)&0x7; // last s is the final s
	for(int i=0; i<M; ++i){
		float p = 0;
		for(int j=0; j<sLen[sLike[i]]; ++j)
			p += dp[(8+s-j)&0x7][sLike[i]];
		printf("%.8f ", p);
	}
	printf("\n");
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		solve();
	}
}