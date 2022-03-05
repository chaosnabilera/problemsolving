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

#define PLIM 10000000

int num_div[PLIM+1];

void precompute(){
	for(int i=1; i<=PLIM; ++i)
		num_div[i] = 1;

	for(int d=2; d<=PLIM; ++d){
		int dd = d;
		while(dd <= PLIM){
			++num_div[dd];
			dd += d;
		}
	}
}

int main(int argc, char** argv){
	int C,N,LO,HI;
	int cnt;

	precompute();
	scanf("%d", &C);
	for(int ci=0; ci<C; ++ci){
		scanf("%d %d %d", &N, &LO, &HI);
		cnt = 0;
		for(int i=LO; i<=HI; ++i)
			if(num_div[i] == N)
				++cnt;
		printf("%d\n",cnt);
	}
}