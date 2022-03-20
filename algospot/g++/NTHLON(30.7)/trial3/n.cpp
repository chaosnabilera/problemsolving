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

int M;
vector<pair<int,int>> G;

void get_input(){
	int a,b;
	scanf("%d", &M);
	G.clear();
	G.resize(M);
	for(int i=0; i<M; ++i){
		scanf("%d%d",&a,&b);
		G[i] = make_pair(a,b);
	}
}

bool is_possible(){
	int a_wins = 0;
	int b_wins = 0;
	int draw = 0;
	for(auto p:G){
		if(p.first < p.second)
			++a_wins;
		else if (p.first == p.second)
			++draw;
		else
			++b_wins;
	}

	if((draw > 0) || (a_wins > 0 && b_wins > 0))
		return true;
	else
		return false;
}

int solve(){
	const int INF = numeric_limits<int>::max();
	vector<int> dist(400,INF);
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> minq;

	for(auto p:G){
		int delta = p.first - p.second;
		int cost = p.first;
		minq.push(make_pair(cost, 200+delta));
	}

	while(!minq.empty()){
		auto p = minq.top(); minq.pop();
		int cost = p.first;
		int cur = p.second;

		if(dist[cur] <= cost)
			continue;

		dist[cur] = cost;
		if(cur == 200)
			return dist[cur];

		for(auto p:G){
			int d = p.first - p.second;
			int nxt = cur + d;
			if(nxt < 0 || nxt >= 400)
				continue;
			int nxt_dist = dist[cur] + p.first;
			if(nxt_dist < dist[nxt])
				minq.push(make_pair(nxt_dist, nxt));
		}
	}
	return -1;
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		if(!is_possible()){
			printf("IMPOSSIBLE\n");
			continue;
		}
		printf("%d\n",solve());
	}
}