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

int V,E;
int Obs[500];
int Edge[500][500];
int Arr1[500][500];
int Arr2[500][500];
int (*MinDist)[500];

void get_input(){
	int a,b,t;
	scanf("%d %d", &V, &E);
	for(int i=0; i<V; ++i)
		for(int j=0; j<V; ++j){
			Edge[i][j] = INF;
		}

	for(int i=0; i<V; ++i)
		scanf("%d", &Obs[i]);
	
	for(int i=0; i<E; ++i){
		scanf("%d %d %d", &a, &b, &t);
		--a; --b;
		Edge[a][b] = t;
		Edge[b][a] = t;
	}
}

void print_table(int t[][500], int V){
	for(int i=0; i<V; ++i){
		for(int j=0; j<V; ++j){
			if(t[i][j] == INF)
				printf(" INF");
			else
				printf("%4d",t[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void build_graph(){
	int Obs1[500][500] = {0};
	int Obs2[500][500] = {0};

	int (*cur_mindist)[500] = Arr1;
	int (*next_mindist)[500] = Arr2;
	int (*cur_maxobs)[500] = Obs1;
	int (*next_maxobs)[500] = Obs2;

	// create k=0
	for(int i=0; i<V; ++i)
		for(int j=0; j<V; ++j){
			if(i == j){
				cur_mindist[i][j] = 0;
				cur_maxobs[i][j] = 0;
				continue;
			}
			int i0j_path = Edge[i][0]+Edge[0][j];
			if(i0j_path + Obs[0] < Edge[i][j]){
				cur_mindist[i][j] = i0j_path + Obs[0];
				cur_maxobs[i][j] = Obs[0];
			}
			else{
				cur_mindist[i][j] = Edge[i][j];
				cur_maxobs[i][j] = 0; // Undefined
			}
		}

	memcpy(next_mindist,cur_mindist,sizeof(Arr2));
	memcpy(next_maxobs,cur_maxobs,sizeof(Obs2));

	// print_table(cur_mindist,V);

	for(int k=1; k<V; ++k){
		for(int i=0; i<V; ++i){
			for(int j=0; j<V; ++j){
				int path_ik, obs_ik, path_kj, obs_kj, cand_maxobs, cand_dist;

				path_ik = cur_mindist[i][k] - cur_maxobs[i][k];

				if(i == k)
					obs_ik = 0;
				else if (cur_maxobs[i][k] == 0)
					obs_ik = Obs[k];
				else
					obs_ik = max(cur_maxobs[i][k],Obs[k]);

				path_kj = cur_mindist[k][j] - cur_maxobs[k][j];

				if(j == k)
					obs_kj = 0;
				else if (cur_maxobs[k][j] == 0)
					obs_kj = Obs[k];
				else
					obs_kj = max(Obs[k],cur_maxobs[k][j]);

				cand_maxobs = max(obs_ik,obs_kj);
				cand_dist = path_ik + path_kj + cand_maxobs;

				// if(i == j || i == k || j == k)
				// 	printf("i:%d j:%d k:%d path_ik:%d path_kj:%d cand_maxobs:%d\n",i,j,k,path_ik,path_kj,cand_maxobs);

				if(cand_dist < cur_mindist[i][j]){
					next_mindist[i][j] = cand_dist;
					next_maxobs[i][j] = cand_maxobs;
				}
				else{
					next_mindist[i][j] = cur_mindist[i][j];
					next_maxobs[i][j]  = cur_maxobs[i][j];
				}
			}
		}

		swap(cur_mindist, next_mindist);
		swap(cur_maxobs, next_maxobs);
		// print_table(cur_mindist,V);
	}

	MinDist = cur_mindist;
}

void solve(){
	int n,a,b;
	scanf("%d", &n);
	for(int i=0; i<n; ++i){
		scanf("%d %d",&a,&b);
		--a; --b;
		printf("%d\n",MinDist[a][b]);
	}
}

int main(int argc, char** argv){
	get_input();
	build_graph();
	solve();
}