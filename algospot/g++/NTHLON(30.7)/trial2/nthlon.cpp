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

const int BIGNUM = 987654321;

int M;
int T[500][2];

void get_input(){
	scanf("%d", &M);
	for(int i=0; i<M; ++i){
		scanf("%d %d",&T[i][0], &T[i][1]);
	}
}

void solve(){
	int p1win = 0;
	int p2win = 0;
	int ans = BIGNUM;
	int MinTime[400];
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

	for(int i=0; i<M; ++i){
		if(T[i][0] < T[i][1])
			p1win++;
		else if(T[i][0] > T[i][1])
			p2win++;
	}

	// 0 always wins or vice versa
	if(p1win == M || p2win == M){
		printf("IMPOSSIBLE\n");
		return;
	}

	// only way is to play 1 draw
	if(p1win == 0 || p2win == 0){
		for(int i=0; i<M; ++i){
			if(T[i][0] == T[i][1])
				ans = min(ans,T[i][0]);
		}
		printf("%d\n",ans);
		return;
	}

	// Compute MinTime in terms of Player 0
	for(int i=0; i<400; ++i){
		MinTime[i] = -1;
	}
	MinTime[200] = 0;
	MinTime[0] = 0;

	for(int i=0; i<M; ++i)
		pq.push(make_pair(T[i][0],T[i][0]-T[i][1]));

	while(!pq.empty()){
		auto p = pq.top(); pq.pop();

		int cost = p.first;
		int delta= p.second;

		if(MinTime[200+delta] != -1)
			continue;

		MinTime[200+delta] = cost;
		// printf("%d = %d\n",delta,cost);

		for(int i=0; i<M; ++i){
			int next_cost = cost + T[i][0];
			int next_delta= delta + (T[i][0]-T[i][1]);

			if(next_delta < -199 || next_delta > 199)
				continue;

			pq.push(make_pair(next_cost,next_delta));
		}
	}

	for(int i=0; i<M; ++i){
		ans = min(ans, T[i][0] + MinTime[200 + T[i][1]-T[i][0]]);
	}

	printf("%d\n",ans);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}