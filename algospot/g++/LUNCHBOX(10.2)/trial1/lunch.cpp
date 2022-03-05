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

using namespace std;

int T, N;
pair<int,int> iDat[10000];

void get_input(){
	scanf("%d", &N);
	int time, eat;
	for(int i=0; i<N; ++i){
		scanf("%d", &time);
		iDat[i].second = time;
	}
	for(int i=0; i<N; ++i){
		scanf("%d", &eat);
		iDat[i].first = eat;
	}
	// for(int i=0; i<N; ++i){
	// 	printf("iDat[%d].first: %d  iDat[%d].second:%d\n",
	// 		i, iDat[i].first, i, iDat[i].second);
	// }
}

bool custom_compare(pair<int,int> a, pair<int,int> b){
	return a.first > b.first;
}

void solve(){
	sort(&iDat[0],&iDat[N],custom_compare);
	// for(int i=0; i<N; ++i){
	// 	printf("iDat[%d].first: %d  iDat[%d].second:%d\n",
	// 		i, iDat[i].first, i, iDat[i].second);
	// }
	int tsum = 0;
	int res = 0;
	for(int i=0; i<N; ++i){
		res = max(res, tsum+iDat[i].second+iDat[i].first);
		tsum += iDat[i].second;
	}
	printf("%d\n", res);
}

int main(int argc, char** argv){
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}