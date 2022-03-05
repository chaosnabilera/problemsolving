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

const long long BIGNUM = 999999999999999;

int N,M;
long long A[101];
long long B[101];

long long DP[101][101];

void get_input(){
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; ++i)
		scanf("%lld", &A[i]);
	for(int i=0; i<M; ++i)
		scanf("%lld", &B[i]);
}

long long rec_solve(int a, int b){
	if(DP[a][b] != -1)
		return DP[a][b];

	if(A[a] < B[b]){
		DP[a][b] = (b != M) ? 2 : 1;
		for(int na=a+1; na <= N; ++na){
			if(A[a] < A[na])
				DP[a][b] = max(DP[a][b], 1+rec_solve(na,b));
		}
	}
	else if(A[a] > B[b]){
		DP[a][b] = (a != N) ? 2 : 1;
		for(int nb=b+1; nb <= M; ++nb){
			if(B[b] < B[nb])
				DP[a][b] = max(DP[a][b], 1+rec_solve(a,nb));
		}
	}
	else{ // A[a] == B[b]
		DP[a][b] = 1;
		for(int na=a+1; na <= N; ++na){
			for(int nb=b+1; nb <= M; ++nb){
				if(A[a] < A[na] && B[b] < B[nb]){
					// printf("A[%d]:%lld < A[%d]:%lld && B[%d]:%lld < B[%d]:%lld\n",
						// a,A[a],na,A[na],b,B[b],nb,B[nb]);
					DP[a][b] = max(DP[a][b], 1+rec_solve(na,nb));
				}
			}
		}
	}
	return DP[a][b];
}

void solve(){
	for(int i=0; i<=N; ++i)
		for(int j=0; j<=M; ++j)
			DP[i][j] = -1;

	A[N] = BIGNUM;
	B[M] = BIGNUM;
	DP[N][M] = 0;
	DP[N-1][M] = 1;
	DP[N][M-1] = 1;

	long long max_jlis = 0;
	for(int i=0; i<=N; ++i){
		for(int j=0; j<=M; ++j){
			max_jlis = max(max_jlis, rec_solve(i,j));
			// printf("%4lld ", DP[i][j]);
		}
		// printf("\n");
	}

	printf("%lld\n", max_jlis);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}