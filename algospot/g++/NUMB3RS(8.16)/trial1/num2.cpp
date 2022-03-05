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

int C, N, D, P, T;
int adj[50][50];
int village[50];
double dp[101][50];

void print_matrix(double matrix[][50]){
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			printf("%.8f ", matrix[i][j]);
		}
		printf("\n");
	}
}

void solve(){
	int deg[50];
	for(int i=0; i<N; ++i){
		deg[i] = 0;
		for(int j=0; j<N; ++j)
			deg[i] += adj[i][j];
	}

	for(int i=0; i<N; ++i)
		dp[0][i] = (i == P) ? 1.0 : 0.0;

	for(int d=1; d<=D; ++d){
		for(int i=0; i<N; ++i){
			dp[d][i] = 0;
			for(int j=0; j<N; ++j){
				if(adj[i][j])
					dp[d][i] += dp[d-1][j]/deg[j];
			}
		}
	}
}

int main(int argc, char** argv){
	int v;
	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d %d %d", &N, &D, &P);
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				scanf("%d", &adj[i][j]);
		scanf("%d", &T);

		solve();

		for(int i=0; i<T; ++i){
			scanf("%d", &v);
			printf("%.8f ", dp[D][v]);
		}
		printf("\n");
	}
}
