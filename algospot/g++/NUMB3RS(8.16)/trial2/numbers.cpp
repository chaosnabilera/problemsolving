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

int N, D, P;
int iAdj[50][50];
int T;
int Q[50];

vector<int> Adj[50];

void get_input(){
	scanf("%d %d %d", &N, &D, &P);
	// printf("%d %d %d\n",N,D,P);
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			scanf("%d", &iAdj[i][j]);
		}
	}
	scanf("%d", &T);
	for(int i=0; i<T; ++i)
		scanf("%d", &Q[i]);

	// printf("hmm?\n");
}

void preprocess(){
	for(int i=0; i<N; ++i)
		Adj[i].clear();

	for(int a=0; a<N; ++a){
		for(int b=a+1; b<N; ++b){
			if(iAdj[a][b]){
				Adj[a].push_back(b);
				Adj[b].push_back(a);
			}
		}
	}
}

void solve(){
	double divmul[50];
	double prob1[50];
	double prob2[50];

	for(int i=0; i<N; ++i)
		divmul[i] = 1.0/((double)(Adj[i].size()));

	double* curprob  = prob1;
	double* nextprob = prob2;

	memset(curprob,0,sizeof(prob1));
	curprob[P] = 1.0;

	for(int i=0; i<D; ++i){
		memset(nextprob,0,sizeof(prob1));
		for(int a=0; a<N; ++a){
			for(int b:Adj[a]){
				nextprob[b] += curprob[a] * divmul[a];
			}
		}
		swap(curprob,nextprob);
	}

	for(int i=0; i<T; ++i){
		printf("%.8f ", curprob[Q[i]]);
	}
	printf("\n");
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		preprocess();
		solve();
	}
}