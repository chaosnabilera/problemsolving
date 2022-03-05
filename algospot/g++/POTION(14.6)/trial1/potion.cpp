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

const int INF = 987654321;

int N;
int R[200];
int P[200];

int gcd(int a, int b){
	int swap, n;
	if(a<b){
		swap = a;
		a = b;
		b = swap; 
	}

	while(b != 0){
		n = a%b;
		a = b;
		b = n;
	}

	return a;
}

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i)
		scanf("%d", &R[i]);
	for(int i=0; i<N; ++i)
		scanf("%d", &P[i]);
}

void solve(){
	int min_gcd = INF;
	int max_mult = 0;

	for(int i=0; i<N-1; ++i)
		min_gcd = min(min_gcd, gcd(R[i],R[i+1]));

	for(int i=0; i<N; ++i)
		R[i] /= min_gcd;

	for(int i=0; i<N; ++i){
		int cur_mult = P[i]/R[i];
		if(P[i]%R[i])
			cur_mult++;
		max_mult = max(max_mult, cur_mult);
	}

	for(int i=0; i<N; ++i){
		printf("%d ", (max_mult*R[i])-P[i]);
	}
	printf("\n");
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}