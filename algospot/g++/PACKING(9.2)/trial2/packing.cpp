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

int N,W;
int DP[101][1001];
bool Taken[101][1001];
// int Next[101][1001];
char Name[100][30];
int Cost[100];
int Score[100];

int rec_solve(int ci, int space_left){
	if(DP[ci][space_left] != -1)
		return DP[ci][space_left];

	// base case
	if(ci == N || space_left == 0){
		DP[ci][space_left] = 0;
		// printf("DP[%d][%d] = %d\n",ci,space_left,DP[ci][space_left]);
		return 0;
	}

	int cand1 = (space_left >= Cost[ci]) ? Score[ci] + rec_solve(ci+1,space_left-Cost[ci]) : 0;
	int cand2 = rec_solve(ci+1, space_left);

	if(cand1 > cand2){
		DP[ci][space_left] = cand1;
		Taken[ci][space_left] = true;
	}
	else{
		DP[ci][space_left] = cand2;
		Taken[ci][space_left] = false;
	}

	return DP[ci][space_left];
}

void print_answer(){
	int space = W;
	vector<string> ans;

	for(int i=0; i<N; ++i){
		if(Taken[i][space]){
			ans.push_back(Name[i]);
			space -= Cost[i];
		}
	}
	
	printf("%d %lu\n", DP[0][W], ans.size());
	for(auto s:ans){
		cout << s << endl;
	}
}

void get_input(){
	scanf("%d %d",&N,&W);
	for(int i=0; i<N; ++i)
		scanf("%s %d %d", Name[i], &Cost[i], &Score[i]);
}

void solve(){
	for(int i=0; i<=N; ++i){
		for(int j=0; j<=W; ++j){
			Taken[i][j] = false;
			DP[i][j] = -1;
		}
	}

	rec_solve(0,W);
	print_answer();
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}