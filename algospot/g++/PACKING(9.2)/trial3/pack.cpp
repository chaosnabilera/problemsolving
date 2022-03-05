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

int N,W;
char Name[100][21];
int Weight[100];
int Need[100];

int DP[100][1001];
vector<int> Ans;

void get_input(){
	scanf("%d %d", &N, &W);
	for(int i=0; i<N; ++i)
		scanf("%s %d %d", Name[i], &Weight[i], &Need[i]);
}

int rec_solve(int f, int w){
	if(DP[f][w] != -1)
		return DP[f][w];

	if(Weight[f] > w){
		DP[f][w] = 0;
		return 0;
	}

	int base = Need[f];
	int alpha= 0;
	int nw = w-Weight[f];
	for(int nf=f+1; nf<N; ++nf){
		alpha = max(alpha, rec_solve(nf, nw));
	}

	DP[f][w] = base+alpha;
	return DP[f][w];
}

void rec_get(int s, int w, int n){
	if(n == 0)
		return;

	for(int i=s; i<N; ++i){
		if(DP[i][w] == n){
			Ans.push_back(i);
			rec_get(i+1, w-Weight[i], n-Need[i]);
			break;
		}
	}
}

void solve(){
	memset(DP,0xFF,sizeof(DP));

	int maxneed = 0;
	for(int f=0; f<N; ++f){
		maxneed = max(maxneed, rec_solve(f,W));
	}

	Ans.clear();
	rec_get(0, W, maxneed);

	printf("%d %lu\n", maxneed, Ans.size());
	for(int a:Ans){
		printf("%s\n", Name[a]);
	}
}

int main(int argc, char** argv){
	int c;
	scanf("%d",&c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}