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

int N,M;
vector<pair<int,int>> Edge;

int P[2000];
int S[2000];

void get_input(){
	int a,b,c;
	scanf("%d %d", &N, &M);

	Edge.clear();
	Edge.reserve(M);

	for(int i=0; i<M; ++i){
		scanf("%d %d %d", &a, &b, &c);
		Edge.push_back(make_pair(c,(a<<16)|b));
	}
}

int get_parent(int c){
	if(P[P[c]] != P[c]){
		P[c] = get_parent(P[c]);
	}
	return P[c];
}

int merge(int a, int b){
	a = get_parent(a);
	b = get_parent(b);

	if(a == b)
		return a;

	if(S[a] > S[b]){
		P[b] = a;
		S[a] += S[b];
		return a;
	}
	else{
		P[a] = b;
		S[b] += S[a];
		return b;
	}
}

void solve(){
	vector<int> start_pos;

	sort(Edge.begin(),Edge.end(),greater<pair<int,int>>());

	start_pos.push_back(0);
	for(int i=1; i<M; ++i){
		if(Edge[start_pos.back()].first != Edge[i].first){
			start_pos.push_back(i);
		}
	}

	int mindiff = INF;

	for(int start:start_pos){
		for(int i=0; i<N; ++i){
			P[i] = i;
			S[i] = 1;
		}

		int maxspeed = Edge[start].first;
		bool visited_src = false;
		bool visited_dst = false;

		for(int i=start; i<Edge.size(); ++i){
			int curspeed = Edge[i].first;
			int a = Edge[i].second >> 16;
			int b = Edge[i].second & 0xFFFF;

			if(a == 0 || b == 0)
				visited_src = true;

			if(a == N-1 || b == N-1)
				visited_dst = true;

			merge(a,b);

			if(visited_src && visited_dst && get_parent(0) == get_parent(N-1)){
				mindiff = min(mindiff, maxspeed-curspeed);
				break;
			}
		}
	}

	printf("%d\n", mindiff);
}

int main(int argc, char** argv){
	int C;
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		solve();
	}
}