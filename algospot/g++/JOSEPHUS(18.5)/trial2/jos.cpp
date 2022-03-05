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
#include <cmath>

using namespace std;

int N,K;

int rec_solve(int x, int n){
	// printf("x:%d k:%d n:%d\n",x,k,n);
	if(n == N)
		return x;

	int k = K % n;
	if(k == 0)
		k = n;

	if(x <= n-k){
		return rec_solve(k+x, n+1);
	}
	else{
		return rec_solve(x - (n-k), n+1);
	}
}

void solve(){
	int l = rec_solve(0,2);
	// printf("%d\n",l);
	int r = rec_solve(1,2);

	if(l<r)
		printf("%d %d\n", l+1, r+1);
	else
		printf("%d %d\n", r+1, l+1);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		scanf("%d%d",&N,&K);
		solve();
	}
}