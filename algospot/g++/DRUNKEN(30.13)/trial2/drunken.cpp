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
bool Adj[500][500];
int Obs[500];
int Edge[500][500];
int (*MinDist)[500];

void get_input(){
	int a,b,t;

	scanf("%d %d", &V, &E);

	for(int i=0; i<V; ++i)
		scanf("%d", &Obs[i]);

	for(int i=0; i<V; ++i)
		for(int j=0; j<V; ++j)
			Edge[i][j] = INF;
	for(int i=0; i<V; ++i)
		Edge[i][i] = 0;

	memset(Adj,0,sizeof(Adj));
	for(int i=0; i<E; ++i){
		scanf("%d %d %d",&a,&b,&t);
		--a; --b;
		Adj[a][b] = true;
		Adj[b][a] = true;
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
	int mindist1[500][500];
	int mindist2[500][500];
	int maxobs1[500][500];
	int maxobs2[500][500];
	int minpath1[500][500];
	int minpath2[500][500];

	vector<pair<int,int>> obs_order;

	int  (*cur_mindist)[500] = mindist1;
	int (*next_mindist)[500] = mindist2;
	int   (*cur_maxobs)[500] = maxobs1;
	int  (*next_maxobs)[500] = maxobs2;
	int  (*cur_minpath)[500] = minpath1;
	int (*next_minpath)[500] = minpath2;

	obs_order.reserve(V);
	for(int i=0; i<V; ++i)
		obs_order.push_back(make_pair(Obs[i],i));
	sort(obs_order.begin(),obs_order.end());

	// for(int i=0; i<V; ++i)
	// 	printf("[%d,%d] ",obs_order[i].first, obs_order[i].second);
	// printf("\n");

	// compute k = 0
	for(int oi=0; oi<V; ++oi){
		int i = obs_order[oi].second;
		int k = obs_order[0].second;
		for(int oj=0; oj<V; ++oj){
			int j = obs_order[oj].second;
			if(i == j){
				cur_mindist[i][j] = 0;
				cur_maxobs[i][j] = 0;
				cur_minpath[i][j] = 0;
			}
			else if(i == k || j == k){
				cur_mindist[i][j] = Edge[i][j];
				cur_maxobs[i][j] = 0;
				cur_minpath[i][j] = cur_mindist[i][j];
			}
			else{
				if(Edge[i][k] + Edge[k][j] + Obs[k] < Edge[i][j]){
					// printf("Edge[%d][0]:%d Edge[0][%d]:%d Obs[0]:%d Edge[%d][%d]:%d\n",
					// 	i,Edge[i][0],j,Edge[0][j],Obs[0],i,j,Edge[i][j]);
					cur_mindist[i][j] = Edge[i][k] + Edge[k][j] + Obs[k];
					cur_maxobs[i][j] = Obs[k];
					cur_minpath[i][j] = Edge[i][k] + Edge[k][j];
				}
				else{
					cur_mindist[i][j] = Edge[i][j];
					cur_maxobs[i][j] = 0;
					cur_minpath[i][j] = Edge[i][j];
				}
			}
		}
	}

	// print_table(cur_mindist,V);
	// print_table(cur_maxobs,V);

	for(int ok=1; ok<V; ++ok){
		int k = obs_order[ok].second;
		for(int oi=0; oi<V; ++oi){
			int i = obs_order[oi].second;
			for(int oj=0; oj<V; ++oj){
				int j = obs_order[oj].second;
				if(i == j){
					next_mindist[i][j] = 0;
					next_maxobs[i][j] = 0;
					next_minpath[i][j] = 0;
				}
				else if(i == k || j == k){
					next_mindist[i][j] = cur_mindist[i][j];
					next_maxobs[i][j]  = cur_maxobs[i][j];
					next_minpath[i][j] = cur_minpath[i][j];
				}
				else{
					// compute mindist
					if(cur_minpath[i][k] + Obs[k] + cur_minpath[k][j] < cur_mindist[i][j]){
						next_mindist[i][j] = cur_minpath[i][k] + Obs[k] + cur_minpath[k][j];
						next_maxobs[i][j] = Obs[k];
					}
					else{
						next_mindist[i][j] = cur_mindist[i][j];
						next_maxobs[i][j] = cur_maxobs[i][j];
					}

					// compute minpath
					if(cur_minpath[i][k] + cur_minpath[k][j] < cur_minpath[i][j]){
						next_minpath[i][j] = cur_minpath[i][k]+cur_minpath[k][j];
					}
					else{
						next_minpath[i][j] = cur_minpath[i][j];
					}
				}
			}
		}
		swap(cur_mindist,next_mindist);
		swap(cur_maxobs, next_maxobs);
		swap(cur_minpath,next_minpath);
		// print_table(cur_maxobs,V);
	}

	MinDist = cur_mindist;
}

void solve(){
	int a,b,n;
	scanf("%d",&n);
	for(int i=0; i<n; ++i){
		scanf("%d %d", &a, &b);
		--a; --b;
		printf("%d\n",MinDist[a][b]);
	}
}

int main(int argc, char** argv){
	get_input();
	build_graph();
	solve();
}