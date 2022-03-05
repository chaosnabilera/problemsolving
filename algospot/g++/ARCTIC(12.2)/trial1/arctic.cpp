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

int N;
double Loc[100][2];
double Distance[100][100];
double MaxD;

void get_input(){
	scanf("%d",&N);
	for(int i=0; i<N; ++i){
		scanf("%lf %lf", &Loc[i][0], &Loc[i][1]);
	}

	MaxD = 0;
	for(int i=0; i<N; ++i){
		Distance[i][i] = 0;
		for(int j=i+1; j<N; ++j){
			double x = Loc[i][0]-Loc[j][0];
			double y = Loc[i][1]-Loc[j][1];
			Distance[i][j] = sqrt(x*x + y*y);
			Distance[j][i] = Distance[i][j];
			MaxD = max(MaxD,Distance[i][j]);
		}
	}
}

void solve(){
	double minD = 0;
	double maxD = MaxD;
	bool visited[100];
	int visit_cnt = 0;
	queue<int> to_visit;

	while(maxD-minD > 0.0001){
		double D = (minD+maxD)/2.0;

		memset(visited, 0, N);
		visit_cnt = 0;
		to_visit.push(0);

		while(!to_visit.empty()){
			int cur = to_visit.front(); to_visit.pop();
			if(visited[cur])
				continue;

			visited[cur] = true;
			visit_cnt++;
			for(int i=0; i<N; ++i){
				if(Distance[cur][i] <= D && !visited[i])
					to_visit.push(i);
			}
		}

		if(visit_cnt == N)
			maxD = D;
		else
			minD = D;
	}

	printf("%.2lf\n", (minD+maxD)/2.0);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}