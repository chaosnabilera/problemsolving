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

const int INIT_INF = 987654321;
const int INF      = 900000000;

struct Edge{
	Edge(int _beg, int _end, int _cost):beg(_beg),end(_end),cost(_cost){}
	int beg, end, cost;
};

int V, W;
vector<Edge> Graph;

void get_input(){
	int beg,end,cost;
	scanf("%d %d", &V, &W);
	Graph.clear();
	for(int i=0; i<W; ++i){
		scanf("%d %d %d", &beg, &end, &cost);
		Graph.push_back(Edge(beg,end,cost));
	}
}

void solve(){
	int mindist[100];
	for(int i=0; i<V; ++i)
		mindist[i] = INIT_INF;
	mindist[0] = 0;

	bool changed;

	for(int it=0; it<V; ++it){
		changed = false;

		for(Edge& e:Graph){
			int cand = mindist[e.beg]+e.cost;
			if(cand < INF && cand < mindist[e.end]){
				changed = true;
				mindist[e.end] = cand;
			}
		}
		if(!changed)
			break;
	}

	if(mindist[1] > INF){
		printf("UNREACHABLE\n");
		return;
	}

	if(changed){
		printf("INFINITY ");
	}
	else{
		printf("%d ", mindist[1]);
	}

	for(int i=0; i<Graph.size(); ++i)
		Graph[i].cost = -Graph[i].cost;
	for(int i=0; i<V; ++i)
		mindist[i] = INIT_INF;
	mindist[0] = 0;

	for(int it=0; it<V; ++it){
		changed = false;
		for(Edge& e:Graph){
			int cand = mindist[e.beg]+e.cost;
			if(cand < INF && cand < mindist[e.end]){
				changed = true;
				mindist[e.end] = cand;
			}
		}
		if(!changed)
			break;
	}

	if(changed){
		printf("INFINITY\n");
	}
	else{
		printf("%d\n",-mindist[1]);
	}

}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}