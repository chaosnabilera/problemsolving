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
int M[10000];
int E[10000];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i)
		scanf("%d", &M[i]);
	for(int i=0; i<N; ++i)
		scanf("%d", &E[i]);
}

bool longer_eat(pair<int,int>& a, pair<int,int>& b){
	return a.first > b.first;
}

void solve(){
	vector<pair<int,int>> arr;
	arr.reserve(N);
	for(int i=0; i<N; ++i){
		arr.push_back(make_pair(E[i],M[i]));
	}

	sort(arr.begin(),arr.end(),longer_eat);
	int maxtime = 0;
	int cum_m = 0;

	for(int i=0; i<N; ++i){
		int e = arr[i].first;
		int m = arr[i].second;

		cum_m += m;
		maxtime = max(maxtime, cum_m+e);
	}

	printf("%d\n", maxtime);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}