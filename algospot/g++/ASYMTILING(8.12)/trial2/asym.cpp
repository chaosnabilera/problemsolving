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

const unsigned int MODNUM = 1000000007;

unsigned int DP_ALL[101];
unsigned int DP_ASYM[101];

void precompute(){
	// all case first
	DP_ALL[0] = 1;
	DP_ALL[1] = 1;
	DP_ALL[2] = 2;
	DP_ALL[3] = 3;
	for(int i=4; i<=100; ++i){
		unsigned int val = DP_ALL[i-2];
		val = (val + DP_ALL[i-3]) % MODNUM;
		val = (val + DP_ALL[i-3]) % MODNUM;
		val = (val + DP_ALL[i-4]) % MODNUM;
		DP_ALL[i] = val;
	}

	// calculate asym
	DP_ASYM[0] = 0;
	DP_ASYM[1] = 0;
	DP_ASYM[2] = 0;
	DP_ASYM[3] = 2;
	for(int i=4; i<=100; ++i){
		unsigned int val = DP_ALL[i-3];
		val = (val + DP_ALL[i-3])  % MODNUM;
		val = (val + DP_ASYM[i-2]) % MODNUM;
		val = (val + DP_ASYM[i-4]) % MODNUM;
		DP_ASYM[i] = val;
	}
}

int main(int argc, char** argv){
	int T, n;
	scanf("%d", &T);
	precompute();
	for(int i=0; i<T; ++i){
		scanf("%d", &n);
		printf("%d\n", DP_ASYM[n]);
	}
}