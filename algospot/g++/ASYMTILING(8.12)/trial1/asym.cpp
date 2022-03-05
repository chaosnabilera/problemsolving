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

const int MODNUM = 1000000007;

unsigned int dp_all[101];
unsigned int dp_asym[101];

void precompute(){
	dp_all[0] = 0;	dp_all[1] = 1;	dp_all[2] = 2;
	dp_asym[0] = 0; dp_asym[1] = 0; dp_asym[2] = 0; dp_asym[3] = 2;

	for(int i=3; i<=100; ++i){
		dp_all[i] = dp_all[i-1] + dp_all[i-2];
		dp_all[i] %= MODNUM;
	}
	for(int i=4; i<=100; ++i){
		dp_asym[i] = (dp_all[i-3]*2) + dp_asym[i-2] + dp_asym[i-4];
		dp_asym[i] %= MODNUM;
	}
}

int main(int argc, char** argv){
	int C, N;
	precompute();
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d", &N);
		printf("%d\n", dp_asym[N]);
	}
}