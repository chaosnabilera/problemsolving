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

int N;
double X[100];
double Y[100];
double Dist[100][100];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%lf %lf", &X[i], &Y[i]);
	}
}

bool can_contact_everyone(double d){
	bool did_visit[100] = {0};
	double d2 = d*d;

	queue<int> q;
	q.push(0);
	int visit_cnt = 0;

	while(!q.empty()){
		int cur = q.front(); q.pop();
		if(did_visit[cur])
			continue;

		did_visit[cur] = true;
		visit_cnt++;

		if(visit_cnt == N)
			break;

		for(int nxt=0; nxt<N; ++nxt){
			if(!did_visit[nxt] && Dist[cur][nxt] <= d2)
				q.push(nxt);
		}
	}

	return (visit_cnt == N);
}

void solve(){
	for(int a=0; a<N; ++a){
		Dist[a][a] = 0;
		for(int b=a+1; b<N; ++b){
			double x = X[a]-X[b];
			double y = Y[a]-Y[b];
			Dist[a][b] = (x*x) + (y*y);
			Dist[b][a] = Dist[a][b];
		}
	}

	double left = 0;
	double right= 1000;
	double mid;

	while(right-left > 0.0001){
		mid = (left+right)*0.5;
		if(can_contact_everyone(mid))
			right = mid;
		else
			left = mid;
	}

	printf("%.2lf\n", ((left+right)*0.5));
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}