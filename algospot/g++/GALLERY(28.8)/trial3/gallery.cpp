#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int G,H;

unordered_set<int> Graph[1000];
int Parent[1000];
bool Visited[1000];
bool Have[1000];
bool Lighted[1000];
int GCnt;

void get_input(){
	int a,b;
	scanf("%d%d",&G,&H);

	for(int i=0; i<G; ++i)
		Graph[i].clear();
	
	for(int i=0; i<H; ++i){
		scanf("%d%d",&a,&b);
		Graph[a].insert(b);
		Graph[b].insert(a);
	}
}

void rec_topological_sort(int cur, int parent, vector<int>& topology){
	Visited[cur] = true;
	Parent[cur] = parent;
	for(int c:Graph[cur]){
		if(Visited[c])
			continue;
		rec_topological_sort(c, cur, topology);
	}
	topology.push_back(cur);
}

void solve(){
	vector<int> topology;
	memset(Parent,0xFF,sizeof(Parent));
	memset(Visited,0,sizeof(Visited));
	memset(Have,0,sizeof(Have));
	memset(Lighted,0,sizeof(Lighted));
	GCnt = 0;

	for(int i=0; i<G; ++i){
		if(!Visited[i]){
			if(Graph[i].empty()){
				GCnt++;
				Visited[i] = Have[i] = Lighted[i] = true;
			}
			else{
				topology.clear();
				rec_topological_sort(i, -1, topology);
				for(int c:topology){
					if(Parent[c] != -1 && Have[Parent[c]]){
						Lighted[c] = true;
					}
					if(!Lighted[c]){
						if(Parent[c] != -1){
							GCnt++;
							Have[Parent[c]] = true;
							Lighted[Parent[c]] = true;
							if(Parent[Parent[c]] != -1)
								Lighted[Parent[Parent[c]]] = true;
							Lighted[c] = true;
						}
						else{
							GCnt++;
							Have[c] = true;
							Lighted[c] = true;
						}
					}
				}
			}
		}
	}

	printf("%d\n",GCnt);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}