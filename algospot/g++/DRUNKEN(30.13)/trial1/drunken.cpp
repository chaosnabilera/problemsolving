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

int V, E, T;
int delay[501];
std::vector<std::pair<int,int>> sorted_delay;
int mindist[501][501];
int minworst[501][501];

void precompute(){
	for(int k=0; k<V; ++k){
		int kv = sorted_delay[k].first;
		int ki = sorted_delay[k].second;

		for(int i=1; i<=V; ++i){
			for(int j=1; j<=V; ++j){
				mindist[i][j] = std::min(mindist[i][ki]+mindist[ki][j], mindist[i][j]);
				minworst[i][j] = std::min(mindist[i][ki]+kv+mindist[ki][j], minworst[i][j]);
			}
		}
	}
}

int main(int argc, char** argv){
	int v,a,b,c,s,t;

	//initialize global state
	for(int i=0; i<501; ++i){
		for(int j=0; j<501; ++j){
			mindist[i][j] = 0xFFFFFF;
			minworst[i][j]= 0xFFFFFF;
		}
	}
	for(int i=0; i<501; ++i){
		mindist[i][i] = 0;
		minworst[i][i] = 0;
	}

	scanf("%d %d", &V, &E);
	for(int i=1; i<=V; ++i){
		scanf("%d", &delay[i]);
		sorted_delay.push_back(std::make_pair(delay[i],i));
	}
	std::sort(sorted_delay.begin(), sorted_delay.end());

	for(int i=0; i<E; ++i){
		scanf("%d %d %d", &a, &b, &c);
		mindist[a][b] = c;
		mindist[b][a] = c;
		minworst[a][b] = c;
		minworst[b][a] = c;
	}

	precompute();

	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		scanf("%d %d", &s, &t);
		printf("%d\n", minworst[s][t]);
	}
}