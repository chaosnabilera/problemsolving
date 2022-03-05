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

int G, H;
vector<int> Adj[1000];
bool Visited[1000];
bool Observable[1000];
int TotalCount;

void get_input(){
	int a,b;

	scanf("%d %d", &G, &H);
	for(int i=0; i<G; ++i)
		Adj[i].clear();

	for(int i=0; i<H; ++i){
		scanf("%d %d", &a, &b);
		Adj[a].push_back(b);
		Adj[b].push_back(a);
	}
}

void dfs(int i, int root){
	vector<int> child;
	bool has_unobserved_child = false;

	Visited[i] = true;

	for(int j:Adj[i]){
		if(!Visited[j]){
			dfs(j,root);
			child.push_back(j);
		}
	}

	for(int c:child){
		if(!Observable[c]){
			has_unobserved_child = true;
			break;
		}
	}

	if(has_unobserved_child){
		Observable[i] = true;
		for(int j:Adj[i])
			Observable[j] = true;
		TotalCount++;
	}

	if(!Observable[i] && i == root){
		Observable[i] = true;
		TotalCount++;
	}
}

void solve(){
	memset(Visited,0,sizeof(Visited));
	memset(Observable,0,sizeof(Observable));
	TotalCount = 0;

	for(int i=0; i<G; ++i)
		if(!Visited[i]){
			dfs(i,i);
		}

	printf("%d\n", TotalCount);
}

int main(int argc, char** argv){
	int T;

	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}