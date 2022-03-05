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

int N, K;
int R[1000];
int C[1000];

void get_input(){
	scanf("%d %d", &N, &K);
	for(int i=0; i<N; ++i){
		scanf("%d %d", &R[i], &C[i]);
	}
}

void solve(){
	bool removed[1000] = {0};
	int rsum = 0;
	int csum = 0;
	double ratio = 0;

	for(int i=0; i<N; ++i){
		rsum += R[i];
		csum += C[i];
	}
	double min_ratio = ((double)rsum)/((double)csum);

	for(int cnt=N; cnt>K; --cnt){
		int min_i = -1;

		for(int i=0; i<N; ++i){
			if(removed[i])
				continue;

			int cur_rsum = rsum - R[i];
			int cur_csum = csum - C[i];
			double cur_ratio = ((double)cur_rsum)/((double)cur_csum);

			if(cur_ratio < min_ratio){
				min_ratio = cur_ratio;
				min_i = i;
			}
		}
		
		if(min_i != -1){
			rsum -= R[min_i];
			csum -= C[min_i];
			removed[min_i] = true;
		}
		else{
			break;
		}
	}

	printf("%.10lf\n", min_ratio);
}

int main(int argc, char** argv){
	int t;
	scanf("%d", &t);
	for(int i=0; i<t; ++i){
		get_input();
		solve();
	}
}