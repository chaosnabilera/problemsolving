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

int C, N;
double iy[100];
double ix[100];
double ir[100];

double c1dx[100];
double cr[100];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%lf %lf %lf", &iy[i], &ix[i], &ir[i]);
	}
}

double convert_to_1d(double x, double y){
	double rad = atan2(y,x);
	return (rad >= 0) ? R*rad : R*((2*M_PI)+rad);
}

double convert_to_cone(double r){
	double rad = (0.5*M_PI) - acos((0.5*r)/R);
	return R*rad*2;
}

int greedy_cnt(int s){
	int cnt = 1;
	bool added;

	double s_e1 = c1dx[s]-cr[s];
	double s_e2 = c1dx[s]+cr[s]; 
	double delta;

	double beg, end;

	if(s_e1 <= 0){
		beg = s_e2;
		end = CIRCUM+s_e1;
	}
	else{
		beg = s_e2 - CIRCUM;
		end = s_e1;
	}

	// printf("s:%d beg:%lf end:%lf\n", s, beg, end);
	
	while(beg < end){
		// printf("\tbeg:%lf end:%lf\n", beg, end);
		added = false;
		delta = 0;
		for(int i=0; i<N; ++i){
			double curbeg = c1dx[i]-cr[i];
			double curend = c1dx[i]+cr[i];
			if(curbeg > beg || curend <= beg)
				continue;
			added = true;
			delta = max(delta, curend-beg);
		}

		if(!added)
			return -1;

		beg += delta;
		cnt++;
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

	// x=R, y=0 is the origin
	for(int i=0; i<N; ++i){
		c1dx[i] = convert_to_1d(ix[i], iy[i]);
		cr[i] = convert_to_cone(ir[i]);
	}

	// for(int i=0; i<N; ++i){
	// 	printf("point %d: x:%lf y:%lf ir:%lf c1dx:%lf cr:%lf\n",
	// 		i, ix[i], iy[i], ir[i], c1dx[i], cr[i]);
	// }

	int min_cnt = 987654321;
	int cur_cnt;

	for(int i=0; i<N; ++i){
		double e1 = c1dx[i]-cr[i];
		double e2 = c1dx[i]+cr[i];

		if(e1 <= 0 || e2 >= CIRCUM){
			if((cur_cnt = greedy_cnt(i)) < 0){
				break;
			}
			min_cnt = min(min_cnt, cur_cnt);
		}
	}

	if(min_cnt == 987654321){
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