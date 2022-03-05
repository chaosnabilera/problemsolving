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
#include <cmath>

int C,N,M;
double coord[500][2];
bool adj[500][500];
bool connected[500];
int parent[500];
double distance[500];
double edge[500][500];

void init_vars(){
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			adj[i][j] = false;
		}
		adj[i][i] = true;
		connected[i] = false;
		parent[i] = -1;
		distance[i] = std::numeric_limits<double>::max();
	}
}

void compute_distance(){
	double x,y;
	for(int i=0; i<N; ++i){
		edge[i][i] = 0;
		for(int j=i+1; j<N; ++j){
			x = coord[i][0]-coord[j][0];
			y = coord[i][1]-coord[j][1];
			edge[i][j] = sqrt((x*x)+(y*y));
			edge[j][i] = edge[i][j];
		}
	}
}

// Use Prim's algorithm to solve
void solve(){
	double span_tree_length = 0;
	compute_distance();
	
	parent[0] = 0;
	distance[0] = 0;

	for(int i=0; i<N; ++i){
		int u = -1;
		for(int v=0; v<N; ++v){
			if((!connected[v]) && ((u == -1) || (distance[v] < distance[u]))){
				u = v;
			}
		}

		connected[u] = true;
		span_tree_length += distance[u];

		for(int v=0; v<N; ++v){
			if(!connected[v]){
				double uv_edge = adj[u][v] ? 0 : edge[u][v];
				if(uv_edge < distance[v]){
					parent[v] = u;
					distance[v] = uv_edge;
				}
			}
		}
	}

	printf("%.10lf\n", span_tree_length);
}

int main(int argc, char** argv){
	int a,b;
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d %d", &N, &M);
		init_vars();

		for(int j=0; j<N; ++j){
			scanf("%lf", &coord[j][0]);
		}
		for(int j=0; j<N; ++j){
			scanf("%lf", &coord[j][1]);
		}
		for(int j=0; j<M; ++j){
			scanf("%d %d", &a, &b);
			adj[a][b] = true;
			adj[b][a] = true;
		}
		solve();
	}
}