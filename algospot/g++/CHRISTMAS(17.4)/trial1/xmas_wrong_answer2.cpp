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

const int BIGNUM = 987654321;

const int MODNUM = 20091101;

int N,K;
vector<int> D;

void get_input(){
	scanf("%d %d", &N, &K);
	D = vector<int>(N,0);
	for(int i=0; i<N; ++i){
		scanf("%d", &D[i]);
	}
}

void print_arr(long long* arr, int n){
	for(int i=0; i<n; ++i){
		printf("%4lld ", arr[i]);
	}
	printf("\n");
}

void print_arr(int* arr, int n){
	for(int i=0; i<n; ++i){
		printf("%4d ", arr[i]);
	}
	printf("\n");
}


void solve(){
	vector<int> CumSumMod(N,0);
	vector<int> ModCnt(K,0);
	vector<int> RngCnt(N,0);
	vector<int> Prev(K,-1);

	int psum = 0;
	for(int i=0; i<N; ++i){
		psum = (psum + D[i]) % K;
		CumSumMod[i] = psum;
		++ModCnt[psum];
	}

	// print_arr(CumSumMod,N);
	// print_arr(ModCnt,N);

	// first question
	int ans1 = 0;
	long long x,y;
	if(ModCnt[0]){
		x = ModCnt[0];  y = ans1;
		y += (x*(x+1))/2;
		ans1 = y % MODNUM;
	}
	for(int i=1; i<K; ++i){
		if(!ModCnt[i])
			continue;
		x = ModCnt[i]; y = ans1;
		y += (x*(x-1))/2;
		ans1 = y % MODNUM;
	}

	// second question
	// initial condition
	RngCnt[0] = (CumSumMod[0] == 0) ? 1 : 0;
	Prev[CumSumMod[0]] = 0;
	for(int i=1; i<N; ++i){
		int curmod = CumSumMod[i];
		RngCnt[i] = RngCnt[i-1];
		if(Prev[curmod] != -1){
			RngCnt[i] = max(RngCnt[i], RngCnt[Prev[curmod]] + 1);
		}
		Prev[curmod] = i;
	}

	printf("%d %d\n", ans1, RngCnt[N-1]);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		// printf("input!\n");
		solve();
	}
}