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

vector<int> Mask;
int iBoard;

char DP[(1<<25)];

void precompute_mask(){
	int b3[4] = {
		(1<<0) | (1<<1) | (1<<5),
		(1<<0) | (1<<1) | (1<<6),
		(1<<0) | (1<<5) | (1<<6),
		(1<<1) | (1<<5) | (1<<6),
	};
	int bv = (1<<0) | (1<<5);
	int bh = (1<<0) | (1<<1);

	for(int r=0; r<4; ++r){
		for(int bi=0; bi<4; ++bi){
			int cur = b3[bi];
			cur = cur << (r*5);
			for(int c=0; c<4; ++c){
				Mask.push_back(cur << c);
			}
		}
	}

	for(int r=0; r<4; ++r){
		int cur = bv << (r*5);
		for(int c=0; c<5; ++c){
			Mask.push_back(cur << c);
		}
	}

	for(int r=0; r<5; ++r){
		int cur = bh << (r*5);
		for(int c=0; c<4; ++c){
			Mask.push_back(cur << c);
		}
	}
}

void get_input(){
	char line[6];
	int bi = 24;

	iBoard = 0;
	for(int r=0; r<5; ++r){
		scanf("%s", line);
		for(int c=0; c<5; ++c){
			if(line[c] == '#')
				iBoard |= (1<<bi);
			--bi;
		}
	}
}

char rec_solve(int board){
	if(DP[board] != -1)
		return DP[board];

	DP[board] = 0;

	for(int block:Mask){
		if((block & board) != 0)
			continue;

		int next_board = (block | board);
		if(rec_solve(next_board) == 0){
			DP[board] = 1;
			break;
		}
	}

	return DP[board];
}

void solve(){
	if(rec_solve(iBoard) == 1){
		printf("WINNING\n");
	}
	else{
		printf("LOSING\n");
	}
}

int main(int argc, char** argv){
	int c = 0;

	precompute_mask();
	memset(DP,0xFF,sizeof(DP));
	
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}