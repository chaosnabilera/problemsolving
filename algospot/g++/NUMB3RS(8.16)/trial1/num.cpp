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
double ans[50];

void print_matrix(double matrix[][50]){
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			printf("%.8f ", matrix[i][j]);
		}
		printf("\n");
	}
}

void solve(){
	double precompute[7][50][50];
	double prob[50][50];
	double init[50];
	bool is_first_prob = true;

	for(int i=0; i<N; ++i){
		int cnt = 0;
		for(int j=0; j<N; ++j){
			if(adj[i][j])
				++cnt;
		}

		for(int r=0; r<N; ++r){
			if(adj[i][r])
				precompute[0][r][i] = 1.0/double(cnt);
			else
				precompute[0][r][i] = 0;
		}
	}

	for(int i=1; (1<<i)<=D; ++i){
		int p = i-1;
		for(int r=0; r<N; ++r){
			for(int c=0; c<N; ++c){
				precompute[i][r][c] = 0;
				for(int x=0; x<N; ++x){
					precompute[i][r][c] += precompute[p][r][x]*precompute[p][x][c];
				}
			}
		}
	}

	for(int i=6; i>=0; --i){
		double prev_prob[50][50];

		if((D & (1<<i)) == 0)
			continue;
		if(is_first_prob){
			is_first_prob = false;
			for(int r=0; r<N; ++r)
				for(int c=0; c<N; ++c)
					prob[r][c] = precompute[i][r][c];
			continue;
		}

		memcpy(prev_prob, prob, sizeof(prob));
		for(int r=0; r<N; ++r){
			for(int c=0; c<N; ++c){
				prob[r][c] = 0;
				for(int x=0; x<N; ++x){
					prob[r][c] += prev_prob[r][x]*precompute[i][x][c];
				}
			}
		}
	}

	for(int i=0; i<N; ++i)
		init[i] = 0;
	init[P] = 1;

	for(int c=0; c<N; ++c){
		ans[c] = 0;
		for(int x=0; x<N; ++x){
			ans[c] += init[x]*prob[c][x];
		}
	}
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d %d %d", &N, &D, &P);
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				scanf("%d", &adj[i][j]);
		scanf("%d", &T);
		for(int i=0; i<T; ++i)
			scanf("%d", &village[i]);

		solve();

		for(int i=0; i<T; ++i)
			printf("%.8f ", ans[village[i]]);
		printf("\n");
	}
}