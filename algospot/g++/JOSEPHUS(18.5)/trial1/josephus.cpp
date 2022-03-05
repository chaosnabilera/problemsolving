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

int N,K;

int rec_solve(int n, int pos){
	// printf("\t%d %d\n",n,pos);
	if(n == N)
		return pos;

	int next_kpos = 2 + ((K-1) % n);
	int next_pos = next_kpos + (pos-1);

	if(next_pos > n+1)
		next_pos = 1 + (next_pos - (n+1));

	// printf("\t%d %d nk:%d np:%d\n",n,pos,next_kpos,next_pos);

	return rec_solve(n+1, next_pos);
}

void solve(){
	scanf("%d %d", &N, &K);
	int a1 = rec_solve(2,1);
	int a2 = rec_solve(2,2);
	printf("%d %d\n",min(a1,a2),max(a1,a2));
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		solve();
	}
}