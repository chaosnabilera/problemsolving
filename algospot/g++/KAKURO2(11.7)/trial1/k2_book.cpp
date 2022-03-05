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

const int INF = 987654321;

// To precompute
// candidate[scnt][ssum][already]
// if we have scnt blanks, and their sum is supposed to be ssum, and we have already,
// return all possible elements that can fit in the rest of the blank
int Candidate[10][46][1024];
int SetSum[1024];
int SetCnt[1024];

// To reset every time
int N, H;
int IsBlank[20][20];
int Board[20][20];
int Hint[20][20][2];

int HintRCD[400][3];
int HintCnt[400];
int HintSum[400];
int HintAlready[400];

void precompute_set(){
	for(int s=2; s<1024; s+=2){
		SetSum[s] = 0;
		SetCnt[s] = 0;
		for(int b=1; b<10; ++b)
			if(s & (1<<b)){
				SetSum[s] += b;
				SetCnt[s] += 1;
			}
	}
}

void precompute_candidate(){
	for(int set=2; set<1024; set+=2){
		int scnt = SetCnt[set];
		int ssum = SetSum[set];
		int already = (set-1) & set;
		while(already){
			Candidate[scnt][ssum][already] |= (set & (~already));
			already = (already-1) & set;
		}
		Candidate[scnt][ssum][0] |= set;
	}
}

void place_at(int r, int c, int val){
	Board[r][c] = val;
	for(int h=0; h<2; ++h){
		int hi = Hint[r][c][h];
		HintAlready[hi] |= (1<<val);
	}
}

void remove_at(int r, int c, int val){
	Board[r][c] = 0;
	for(int h=0; h<2; ++h){
		int hi = Hint[r][c][h];
		HintAlready[hi] &= ~(1<<val);
	}
}

int candidate_at(int r, int c){
	int hi = Hint[r][c][0];
	int vi = Hint[r][c][1];

	return ( Candidate[HintCnt[hi]][HintSum[hi]][HintAlready[hi]] &
		     Candidate[HintCnt[vi]][HintSum[vi]][HintAlready[vi]] );
}

void precompute(){
	precompute_set();
	precompute_candidate();
}

void get_input(){
	scanf("%d", &N);
	for(int r=0; r<N; ++r)
		for(int c=0; c<N; ++c)
			scanf("%d", &IsBlank[r][c]);

	scanf("%d", &H);
	for(int i=0; i<H; ++i){
		scanf("%d %d %d %d", &HintRCD[i][0], &HintRCD[i][1], &HintRCD[i][2], &HintSum[i]);
		HintAlready[i] = 0;
	}

	for(int i=0; i<H; ++i){
		int r = HintRCD[i][0]-1; //1-based to 0-based
		int c = HintRCD[i][1]-1;

		if(HintRCD[i][2] == 0){ // horizontal
			int cc = c+1;
			while(cc < N && IsBlank[r][cc]){
				Hint[r][cc][0] = i;
				++cc;
			}
			HintCnt[i] = cc-c-1;
		}
		else{
			int rr = r+1;
			while(rr < N && IsBlank[rr][c]){
				Hint[rr][c][1] = i;
				++rr;
			}
			HintCnt[i] = rr-r-1;
		}
	}

	memset(Board,0,sizeof(Board));
}

bool rec_solve(){
	int min_cand_cnt = INF;
	int min_cand_mask = 0;
	int min_r, min_c;

	for(int r=0; r<N; ++r)
		for(int c=0; c<N; ++c)
			if(IsBlank[r][c] && Board[r][c] == 0){
				int cur_cand_mask = candidate_at(r,c);
				int cur_cand_cnt = SetCnt[cur_cand_mask];
				if(cur_cand_cnt < min_cand_cnt){
					min_cand_mask = cur_cand_mask;
					min_cand_cnt = cur_cand_cnt; 
					min_r = r; 	min_c = c;	
				}
			}


	if(min_cand_cnt == 0)
		return false;

	if(min_cand_cnt == INF){
		for(int r=0; r<N; ++r){
			for(int c=0; c<N; ++c)
				printf("%d ",Board[r][c]);
			printf("\n");
		}
		return true;
	}

	for(int b=1; b<10; ++b){
		if(min_cand_mask & (1<<b)){
			place_at(min_r,min_c,b);
			if(rec_solve())
				return true;
			remove_at(min_r,min_c,b);
		}
	}

	return false;
}

int main(int argc, char** argv){
	int T;
	precompute();
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		rec_solve();
	}
}