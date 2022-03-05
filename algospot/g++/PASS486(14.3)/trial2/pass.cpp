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

const int MAX_RANGE = 10000000;

int* Cnt;

void precompute(){
	Cnt = (int*)malloc(sizeof(int)*(MAX_RANGE+1));
	memset(Cnt, 0, sizeof(int)*(MAX_RANGE+1));

	for(int a=1; a<=MAX_RANGE; ++a){
		for(int b=a; b<=MAX_RANGE; b+=a)
			++Cnt[b];
	}
}

void solve(int n, int lo, int hi){
	int cnt = 0;
	for(int i=lo; i<=hi; ++i)
		if(Cnt[i] == n)
			++cnt;
	printf("%d\n",cnt);
}

int main(int argc, char** argv){
	int c;
	int n,lo,hi;
	precompute();

	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		scanf("%d %d %d", &n, &lo, &hi);
		solve(n,lo,hi);
	}

	free(Cnt);
}