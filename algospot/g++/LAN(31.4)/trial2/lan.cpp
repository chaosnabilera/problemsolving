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

int N,M;
double X[500];
double Y[500];

int P[500];
int SSize[500];

int GPBuf[500];

int get_parent(int cur){
	if(P[P[cur]] != P[cur]){
		P[cur] = get_parent(P[cur]);
	}
	return P[cur];
}

int merge(int a, int b){
	a = get_parent(a);
	b = get_parent(b);

	if(SSize[a] > SSize[b]){
		P[b] = a;
		SSize[a] += SSize[b];
		return a;
	}
	else{
		P[a] = b;
		SSize[b] += SSize[a];
		return b;
	}
}

void get_input(){
	int a,b;

	scanf("%d %d", &N, &M);
	for(int i=0; i<N; ++i)
		scanf("%lf", &X[i]);
	for(int i=0; i<N; ++i)
		scanf("%lf", &Y[i]);

	for(int i=0; i<N; ++i){
		P[i] = i;
		SSize[i] = 1;
	}

	for(int i=0; i<M; ++i){
		scanf("%d %d", &a, &b);
		merge(a,b);
	}
}

void solve(){
	vector<pair<double,int>> edge;

	edge.reserve(N*N);

	for(int i=0; i<N; ++i)
		for(int j=i+1; j<N; ++j){
			int x = X[i]-X[j];
			int y = Y[i]-Y[j];
			edge.push_back(make_pair((x*x) + (y*y), (i<<16) | j));
		}

	sort(edge.begin(),edge.end());

	double dsum = 0;
	for(pair<double,int>& p:edge){
		double dist = p.first;
		int a = p.second >> 16;
		int b = p.second & 0xFFFF;

		if(get_parent(a) == get_parent(b))
			continue;

		merge(a,b);
		dsum += sqrt(dist);
	}

	printf("%.10lf\n", dsum);
}

int main(int argc, char** argv){
	int C;
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		solve();
	}
}