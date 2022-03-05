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

int N;
int R[200];
int P[200];

int gcd(int a, int b){
	while(b!=0){
		int r = a%b;
		a= b;
		b= r;
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

bool all_le(){
	for(int i=0; i<N; ++i){
		if(P[i] > R[i])
			return false;
	}
	return true;
}

void solve(){
	int rr[200];
	int rgcd;

	if(all_le()){
		for(int i=0; i<N; ++i)
			printf("%d ", R[i]-P[i]);
		printf("\n");
		return;
	}

	rgcd = gcd(R[0],R[1]);
	for(int i=2; i<N; ++i)
		rgcd = gcd(rgcd,R[i]);

	for(int i=0; i<N; ++i)
		rr[i] = R[i]/rgcd;

	int maxmul = -INF;
	for(int i=0; i<N; ++i){
		int curmul = P[i]/rr[i];
		if(P[i]%rr[i])
			++curmul;
		maxmul = max(maxmul,curmul);
	}

	for(int i=0; i<N; ++i)
		printf("%d ",(rr[i]*maxmul)-P[i]);
	printf("\n");
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}