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

int M, Q, N;

char word[500][11];
map<string, int> word_to_idx;

double pfirst[500];
double pnext[500][500];
double pocr[500][500];

char iLine[100][11];
int W[100];

double prob[100][500];
int fidx[100][500];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%s", iLine[i]);
		W[i] = word_to_idx[iLine[i]];
	}
}

double rec_solve(int x, int w){
	if(prob[x][w] >= 0){
		return prob[x][w];
	}
	
	double best = -1;
	int best_idx = -1;

	for(int p=0; p<M; ++p){
		double cur = rec_solve(x-1,p) * pnext[p][w] * pocr[w][W[x]];
		if(cur > best){
			best = cur;
			best_idx = p;
		}
	}

	prob[x][w] = best;
	fidx[x][w] = best_idx;

	return prob[x][w];
}

void solve(){
	vector<int> ans;

	// solve prob for pfirst
	for(int i=0; i<M; ++i){
		prob[0][i] = pfirst[i] * pocr[i][W[0]];
	}
	// initialize to negative
	for(int i=1; i<N; ++i)
		for(int j=0; j<M; ++j)
			prob[i][j] = -1;

	// solve prob for rest
	double best = -1;
	int best_idx = -1;
	for(int w=0; w<M; ++w){
		if(rec_solve(N-1,w) > best){
			best = prob[N-1][w];
			best_idx = w;
		}
	}

	int cur = best_idx;
	for(int i=N-1; i >= 0; --i){
		ans.push_back(cur);
		cur = fidx[i][cur];
	}

	while(!ans.empty()){
		printf("%s ", word[ans.back()]);
		ans.pop_back();
	}
	printf("\n");
}

int main(int argc, char** argv){
	scanf("%d %d", &M, &Q);
	for(int i=0; i<M; ++i){
		scanf("%s", word[i]);
		word_to_idx[word[i]] = i;
	}
	for(int i=0; i<M; ++i)
		scanf("%lf", &pfirst[i]);
	for(int i=0; i<M; ++i)
		for(int j=0; j<M; ++j)
			scanf("%lf", &pnext[i][j]);
	for(int i=0; i<M; ++i)
		for(int j=0; j<M; ++j)
			scanf("%lf", &pocr[i][j]);

	for(int i=0; i<Q; ++i){
		get_input();
		solve();
	}
}