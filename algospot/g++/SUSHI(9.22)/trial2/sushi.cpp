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

int N, M;
int P[20];
int L[20];

int DP[400];

void get_input(){
	long long m;
	scanf("%d %lld", &N, &m);
	M = m/100;
	for(int i=0; i<N; ++i){
		scanf("%d %d", &P[i], &L[i]);
		P[i] /= 100;
	}
}

int rec_solve(int c){
	if(DP[c] != -1)
		return DP[c];

	int val = 0;
	for(int i=0; i<N; ++i){
		if(c < P[i])
			continue;
		val = max(val, L[i]+rec_solve(c-P[i]));
	}

	DP[c] = val;
	return DP[c];
}

void solve(){
	memset(DP,0xFF,sizeof(DP));
	DP[0] = 0;

	if(M < 399){
		printf("%d\n", rec_solve(M));
		return;
	}

	int curbase = 400;
	for(int c=0; c<400; ++c)
		rec_solve(c);

	while(true){
		memcpy(&DP[0],&DP[200],sizeof(int)*200);
		memset(&DP[200],0xFF,sizeof(int)*200);
		for(int i=0; i<200; ++i){
			int res = rec_solve(200+i);
			if(curbase+i == M){
				printf("%d\n",res);
				return;
			}
		}
		curbase += 200;
	}
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}