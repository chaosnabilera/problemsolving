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
#include <cmath>

using namespace std;

long long N,M;

void get_input(){
	scanf("%lld %lld", &N, &M);
}

void solve(){
	long long iz, z;
	long long up,down;

	if(100*M >= 99*N){
		printf("-1\n");
		return;
	}

	iz = (100*M)/N;
	z = iz+1;

	up = (N*z)-(100*M);
	down = 100-z;

	if(up%down == 0)
		printf("%lld\n",up/down);
	else
		printf("%lld\n",(up/down)+1);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}