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
int R[1000];
int C[1000];

void get_input(){
	scanf("%d %d", &N, &K);
	for(int i=0; i<N; ++i){
		scanf("%d %d", &R[i], &C[i]);
	}
}

void solve(){
	int num_try = N-K;
	int sum_r = 0;
	int sum_c = 0;
	double min_ratio;
	int min_i, min_sum_r, min_sum_c;
	bool removed[1000] = {0};

	for(int i=0; i<N; ++i){
		sum_r += R[i];
		sum_c += C[i];
	}

	min_ratio = ((double)(sum_r))/((double)(sum_c));
	for(int _t=0; _t<num_try; ++_t){
		double cur_min_ratio = 999;
		for(int i=0; i<N; ++i){
			if(removed[i])
				continue;

			int cur_sum_r = sum_r - R[i];
			int cur_sum_c = sum_c - C[i];
			double cur_ratio = ((double)cur_sum_r)/((double)cur_sum_c);
			if(cur_ratio < cur_min_ratio){
				min_i         = i;
				min_sum_r     = cur_sum_r;
				min_sum_c     = cur_sum_c;
				cur_min_ratio = cur_ratio;
			}
		}

		removed[min_i] = true;
		sum_r = min_sum_r;
		sum_c = min_sum_c;
		min_ratio = min(min_ratio, cur_min_ratio);
	}

	printf("%.10f\n", min_ratio);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}