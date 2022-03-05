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

#define UNREACHABLE 1000000000

int C,V,M,N;
int adj[200][200];

void initialize_vars(){
	for(int i=0; i<V; ++i){
		for(int j=0; j<V; ++j){
			adj[i][j] = UNREACHABLE;
		}
	}
	for(int i=0; i<V; ++i){
		adj[i][i] = 0;
	}
}

void floyd_warshall(){
	for(int k=0; k<V; ++k){
		for(int i=0; i<V; ++i){
			for(int j=0; j<V; ++j){
				adj[i][j] = std::min(adj[i][j], adj[i][k]+adj[k][j]);
			}
		}
	}
}

void update_connection(int a, int b, int c){
	adj[a][b] = c;
	adj[b][a] = c;

	for(int i=0; i<V; ++i){
		for(int j=0; j<V; ++j){
			adj[i][j] = std::min(adj[i][j], adj[i][a] + adj[a][b] + adj[b][j]);
			adj[i][j] = std::min(adj[i][j], adj[i][b] + adj[b][a] + adj[a][j]);
		}
	}
}

void print_adj(){
	printf("\n");
	for(int i=0; i<V; ++i){
		for(int j=0; j<V; ++j){
			printf("%10d ", adj[i][j]);
		}
		printf("\n");
	}
}



int main(int argc, char** argv){
	int a,b,c;
	int cnt;

	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d %d %d", &V, &M, &N);

		initialize_vars();

		for(int j=0; j<M; ++j){
			scanf("%d %d %d", &a, &b, &c);
			adj[a][b] = std::min(adj[a][b], c);
			adj[b][a] = adj[a][b];
		}

		floyd_warshall();
		// print_adj();

		cnt = 0;
		for(int j=0; j<N; ++j){
			scanf("%d %d %d", &a, &b, &c);
			// printf("adj[%d][%d]:%d  c:%d\n", a,b,adj[a][b], c);
			if(c < adj[a][b]){
				update_connection(a,b,c);
			}
			else{
				++cnt;
			}
			// print_adj();
		}

		printf("%d\n", cnt);
	}
}