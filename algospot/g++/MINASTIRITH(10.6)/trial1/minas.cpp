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
#include <cmath>

using namespace std;

const double R = 8.0;
const double CIRCUM = 2*8*M_PI;
const int INF = 987654321;

int C, N;
double iy[100];
double ix[100];
double ir[100];

pair<double, double> ranges[100];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%lf %lf %lf", &iy[i], &ix[i], &ir[i]);
	}
}

int greedy_solve(double beg, double end){
	int cnt = 0;

	while(beg < end){
		double nbeg = beg;

		for(int i=0; i<N; ++i){
			if(ranges[i].first <= beg)
				nbeg = max(nbeg, ranges[i].second);
		}
		if(nbeg == beg)
			return INF;
		cnt++;
		beg = nbeg;
	}

	return cnt;
}

void solve(){
	// check for obvious
	for(int i=0; i<N; ++i){
		if(ir[i] >= 16.0){
			printf("1\n");
			return;
		}
	}

	for(int i=0; i<N; ++i){
		double x1d = fmod((2*M_PI) + atan2(iy[i],ix[i]),2*M_PI);
		double delta = 2*asin(ir[i]/16.0);
		ranges[i].first  = x1d - delta;
		ranges[i].second = x1d + delta;
	}
	sort(&ranges[0],&ranges[N]);

	int min_cnt = INF;

	for(int i=0; i<N; ++i){
		if(ranges[i].first <= 0 || ranges[i].second >= 2*M_PI){
			double beg = fmod((2*M_PI)+ranges[i].second,2*M_PI);
			double end = fmod((2*M_PI)+ranges[i].first, 2*M_PI);
			min_cnt = min(min_cnt, 1+greedy_solve(beg,end));
		}
	}

	if(min_cnt > N){
		printf("IMPOSSIBLE\n");
	}
	else{
		printf("%d\n", min_cnt);
	}
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		solve();
	}
}