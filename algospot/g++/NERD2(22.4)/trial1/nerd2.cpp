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

int N;
int P[50000];
int Q[50000];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%d %d", &P[i], &Q[i]);
	}
}

void solve(){
	map<int,int> btree;
	vector<int> to_del;
	int cnt = 0;

	for(int i=0; i<N; ++i){
		auto itlow = btree.lower_bound(P[i]);
		if(itlow != btree.end()){
			if(itlow->second < Q[i]){
				to_del.clear();
				reverse_iterator<map<int,int>::iterator> rit(itlow);
				while(rit != btree.rend() && rit->second < Q[i]){
					to_del.push_back(rit->first);
					++rit;
				}
				for(int p:to_del)
					btree.erase(p);
				btree[P[i]] = Q[i];
			}
		}
		else{
			to_del.clear();
			auto rit = btree.rbegin();
			while(rit != btree.rend() && rit->second < Q[i]){
				to_del.push_back(rit->first);
				++rit;
			}
			for(int p:to_del)
				btree.erase(p);
			btree[P[i]] = Q[i];
		}

		cnt += btree.size();
	}

	printf("%d\n", cnt);
}


int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}