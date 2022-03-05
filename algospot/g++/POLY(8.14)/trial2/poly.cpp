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

const int MODNUM = 10000000;

int DP[101][101];
int Res[101];

int rec_solve(int l, int t){
	if(DP[l][t] != -1)
		return DP[l][t];

	if(l > t){
		DP[l][t] = 0;
	}
	else if(l == t){
		DP[l][t] = 1;
	}
	else{
		int val = 0;
		for(int nl=1; nl<=t-l; ++nl){
			val = (val + (l+nl-1)*rec_solve(nl,t-l)) % MODNUM;
		}
		DP[l][t] = val;
	}
	return DP[l][t];
}

void print_dp(){
	for(int l=0; l<5; ++l){
		for(int t=0; t<10; ++t){
			printf("%3d", DP[l][t]);
		}
		printf("\n");
	}
	printf("\n");
}

void precompute(){
	memset(DP,0xFF,sizeof(DP));
	for(int t=0; t <= 100; ++t){
		Res[t] = 0;
		for(int l=1; l <= 100; ++l)
			Res[t] = (Res[t] + rec_solve(l,t)) % MODNUM;
	}
}

int main(int argc, char** argv){
	int T, n;
	precompute();
	// print_dp();
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		scanf("%d", &n);
		printf("%d\n", Res[n]);
	}
}