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

pair<double,double> ranges[100];

void convert_to_range(){
	for(int i=0; i<N; ++i){
		double loc = fmod(2*M_PI + atan2(iy[i],ix[i]), 2*M_PI);
		double range = 2.0*asin(ir[i]/16.0);
		ranges[i] = make_pair(loc-range, loc+range);
	}
	// sort(ranges,ranges+n);
}

int solveLinear(double begin, double end){
	int used = 0, idx = 0;
	while(begin < end){
		double maxCover = -1;
		while(idx < N && ranges[idx].first <= begin){
			maxCover = max(maxCover, ranges[idx].second);
			++idx;
		}

		if(maxCover <= begin)
			return INF;

		begin = maxCover;
		++used;
	}
	return used;
}

int solveCircular(){
	int ret = INF;

	for(int i=0; i<N; ++i)
		if(ir[i] >= 16.0){
			return 1;
		}

	convert_to_range();
	sort(ranges, ranges+N);
	for(int i=0; i<N; ++i){
		if(ranges[i].first <= 0 || ranges[i].second >= 2*M_PI){
			double begin = fmod(ranges[i].second, 2*M_PI);
			double end = fmod(ranges[i].first+2*M_PI, 2*M_PI);
			ret = min(ret, 1+solveLinear(begin, end));
		}
	}
	return ret;
}

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%lf %lf %lf", &iy[i], &ix[i], &ir[i]);
	}
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		int res = solveCircular();
		if(res <= N){
			printf("%d\n", res);
		}
		else{
			printf("IMPOSSIBLE\n");
		}
	}
}