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

const int BIGNUM =  987654321;
const int NEGLIM = -987654321;

int C, N;

int iNum[50];
int dp_val[50][50];

int rec_solve(int beg, int end){
	if(dp_val[beg][end] != BIGNUM)
		return dp_val[beg][end];

	int best_diff;
	int my_val;
	int op_val;
	int left_range;
	int lbeg, lend;

	if(end-beg > 1){
		// 0. get 1 from left
		best_diff = iNum[beg] - rec_solve(beg+1,end);
		// 1. get 1 from right
		best_diff = max(best_diff, iNum[end] - rec_solve(beg,end-1));
		// 2. remove 2 from left
		best_diff = max(best_diff, -rec_solve(beg+2,end));
		// 3. remove 2 from right
		best_diff = max(best_diff, -rec_solve(beg,end-2));
	}
	else{
		// 0. remove all two
		best_diff = 0;
		// 1. get 1 from left
		best_diff = max(best_diff, iNum[beg]-iNum[end]);
		// 2. get 1 from right
		best_diff = max(best_diff, iNum[end]-iNum[beg]);
	}

	dp_val[beg][end] = best_diff;
	return best_diff;
}

void solve(){
	for(int beg=0; beg<N; ++beg){
		for(int end=0; end<N; ++end){
			if(beg <= end)
				dp_val[beg][end] = BIGNUM;
			else
				dp_val[beg][end] = 0;
		}
	}

	for(int i=0; i<N; ++i)
		dp_val[i][i] = iNum[i];

	printf("%d\n",rec_solve(0,N-1));
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d", &N);
		for(int j=0; j<N; ++j)
			scanf("%d", &iNum[j]);
		solve();
	}
}