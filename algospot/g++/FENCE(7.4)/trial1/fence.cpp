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

int C,N;
int fence[20000];

int rec_solve(int beg, int end){
	if(beg == end){
		return fence[beg];
	}

	int mid = (beg+end) >> 1;
	int maxarea = 0;

	maxarea = max(maxarea, rec_solve(beg, mid));
	maxarea = max(maxarea, rec_solve(mid+1,end));

	int ml = mid;
	int mr = mid+1;
	int minheight = INF;
	int cnt = 0;
	while(ml >= beg || mr <= end){
		if(ml < beg){
			minheight = min(minheight, fence[mr]);
			++mr;
		}
		else if(mr > end){
			minheight = min(minheight, fence[ml]);
			--ml;
		}
		else{
			if(fence[ml] > fence[mr]){
				minheight = min(minheight, fence[ml]);
				--ml;
			}
			else{
				minheight = min(minheight, fence[mr]);
				++mr;
			}
		}

		++cnt;
		maxarea = max(maxarea, cnt*minheight);
	}

	return maxarea;
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d", &N);
		for(int j=0; j<N; ++j){
			scanf("%d", &fence[j]);
		}
		printf("%d\n", rec_solve(0,N-1));
	}
}