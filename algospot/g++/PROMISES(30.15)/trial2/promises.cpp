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

const int INF = 987654321;

int V,M,N;
int Graph[200][200];

void get_input(){
	int a,b,t;
	scanf("%d %d %d", &V, &M, &N);

	// initialize Graph
	for(int i=0; i<V; ++i)
		for(int j=0; j<V; ++j)
			Graph[i][j] = INF;
	for(int i=0; i<V; ++i)
		Graph[i][i] = 0;

	// Get initial status
	for(int i=0; i<M; ++i){
		scanf("%d %d %d", &a, &b, &t);
		Graph[a][b] = min(Graph[a][b],t);
		Graph[b][a] = Graph[a][b];
	}
}

void solve(){
	int a,b,t;

	// build all-pair
	for(int k=0; k<V; ++k){
		for(int i=0; i<V; ++i){
			for(int j=i+1; j<V; ++j){
				Graph[i][j] = min(Graph[i][j], Graph[i][k]+Graph[k][j]);
				Graph[j][i] = Graph[i][j];
			}
		}
	}

	// rest of the case
	int cnt = 0;
	for(int it=0; it<N; ++it){
		scanf("%d %d %d", &a, &b, &t);
		if(Graph[a][b] > t){
			Graph[a][b] = t;
			Graph[b][a] = t;
			for(int i=0; i<V; ++i){
				for(int j=i+1; j<V; ++j){
					Graph[i][j] = min(Graph[i][j], min(Graph[i][a]+Graph[a][b]+Graph[b][j], Graph[i][b]+Graph[b][a]+Graph[a][j]));
					Graph[j][i] = Graph[i][j];
				}
			}
		}
		else{
			++cnt;
		}
	}

	printf("%d\n",cnt);
}

int main(int argc, char** argv){
	int C;
	scanf("%d",&C);
	for(int i=0; i<C; ++i){
		get_input();
		solve();
	}
}