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
#include <cmath>

using namespace std;

const int INF = 987654321;
const double PHI = 2*M_PI;

int N;
double X[100];
double Y[100];
double R[100];

double LX[100];
double LD[100];
double LRng[100][2];

bool Chosen[100];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i)
		scanf("%lf %lf %lf", &X[i], &Y[i], &R[i]);
}

void convert_to_linear(){
	for(int i=0; i<N; ++i){
		LX[i] = fmod(PHI+atan2(Y[i],X[i]),PHI);
		LD[i] = asin((R[i]/2.0)/8.0) * 2;
		if(LX[i]-LD[i] == 0)
			LRng[i][0] = 0;
		else
			LRng[i][0] = fmod(PHI+(LX[i]-LD[i]),PHI);

		if(LX[i]+LD[i] == PHI)
			LRng[i][1] = PHI;
		else
			LRng[i][1] = fmod(LX[i]+LD[i],PHI);
	}
}

void solve(){
	for(int i=0; i<N; ++i){
		if(R[i] >= 16){
			printf("1\n");
			return;
		}
	}

	convert_to_linear();
	int mincnt = INF;

	for(int i=0; i<N; ++i){
		if(LRng[i][0] == 0 || LRng[i][1] == PHI || LRng[i][0] > LRng[i][1]){
			double rbeg, rend;

			memset(Chosen,0,sizeof(Chosen));
			Chosen[i] = true;

			if(LRng[i][0] == 0){
				rbeg = LRng[i][1];
				rend = PHI;
			}
			else if(LRng[i][1] == PHI){
				rbeg = 0;
				rend = LRng[i][0];
			}
			else{
				rbeg = LRng[i][1];
				rend = LRng[i][0];
			}

			// printf("i:%d rbeg:%lf rend:%lf\n",i,rbeg,rend);

			int cnt = 1;
			bool found = false;

			while(true){
				double max_beg = rbeg;
				int max_j = -1;

				for(int j=0; j<N; ++j){
					if(Chosen[j])
						continue;

					if(LX[j]-LD[j] <= rbeg && LX[j]+LD[j] > max_beg){
						max_beg = LX[j]+LD[j];
						max_j = j;
					}
				}

				if(max_j == -1)
					break;

				// printf("max_j:%d LX[%d]:%lf LD[%d]:%lf\n",max_j,max_j,LX[max_j],max_j,LD[max_j]);

				Chosen[max_j] = true;
				rbeg = max_beg;
				++cnt;

				if(rbeg >= rend){
					found = true;
					break;
				}
			}

			if(found)
				mincnt = min(mincnt, cnt);
		}
	}

	if(mincnt == INF){
		printf("IMPOSSIBLE\n");
	}
	else{
		printf("%d\n",mincnt);
	}
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}