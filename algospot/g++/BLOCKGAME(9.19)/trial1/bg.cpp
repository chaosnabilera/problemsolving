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

int C;
bool iBoard[5][5];

const int p3_1 = (1<<24) | (1<<23) | (1<<19);
const int p3_2 = (1<<24) | (1<<23) | (1<<18);
const int p3_3 = (1<<24) | (1<<19) | (1<<18);
const int p3_4 = (1<<23) | (1<<19) | (1<<18);
const int p2_1 = (1<<24) | (1<<23);
const int p2_2 = (1<<24) | (1<<19);

char dp[1<<25];
vector<int> patterns;

void precompute_patterns(){
	int s3[4] = { p3_1, p3_2, p3_3, p3_4};
	for(int r=0; r<4; ++r){
		for(int c=0; c<4; ++c){
			for(int p=0; p<4; ++p){
				int curpat = s3[p];
				curpat >>= ((r*5)+c);
				patterns.push_back(curpat);
			}
		}
	}
	for(int r=0; r<5; ++r){
		for(int c=0; c<4; ++c){
			int curpat = p2_1;
			curpat >>= ((r*5)+c);
			patterns.push_back(curpat);
		}
	}
	for(int r=0; r<4; ++r){
		for(int c=0; c<5; ++c){
			int curpat = p2_2;
			curpat >>= ((r*5)+c);
			patterns.push_back(curpat);
		}
	}
}

void get_input(){
	char col[6];

	for(int r=0; r<5; ++r){
		scanf("%s",col);
		for(int c=0; c<5; ++c){
			iBoard[r][c] = (col[c] == '.') ? true : false;
		}
	}
}

int board_to_state(bool board[][5]){
	int state = 0;
	for(int r=0; r<5; ++r){
		for(int c=0; c<5; ++c){
			if(board[r][c])
				state |= 1;
			state <<= 1;
		}
	}
	state >>= 1; // should cancel last shift

	return state;
}

void state_to_board(int state, bool board[][5]){
	for(int r=4; r>=0; --r){
		for(int c=4; c>=0; --c){
			board[r][c] = (state & 1);
			state >>= 1;
		}
	}
}

void print_board(bool board[][5]){
	for(int r=0; r<5; ++r){
		for(int c=0; c<5; ++c){
			if(board[r][c])
				printf(".");
			else
				printf("#");
		}
		printf("\n");
	}
	printf("\n");
}

int rotate(int state){
	int res = 0;
	for(int r=0; r<5; ++r){
		for(int c=0; c<5; ++c){
			res |= (1 << ((20+r)-(5*c))& state);
			res <<= 0;
		}
	}
	return res;
}

void add_state(int state, bool res){
	int rot;

	dp[state] = res;

	rot = rotate(state);
	dp[rot] = res;
	rot = rotate(rot);
	dp[rot] = res;
	rot = rotate(rot);
	dp[rot] = res;
}

char rec_solve(int state){
	if(dp[state] != -1)
		return dp[state];

	char res = 0;

	for(int pat:patterns){
		if((state & pat) == pat){
			if(!rec_solve(state^pat)){
				res = 1;
				break;
			}
		}
	}
	
	dp[state] = res;

	return res;
}

int main(int argc, char** argv){
	int istate;

	for(int i=0; i<(1<<25); ++i){
		dp[i] = -1;
	}
	precompute_patterns();

	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();

		// printf("!\n");
		// print_board(iBoard);
		// printf("!\n");

		istate = board_to_state(iBoard);
		if(rec_solve(istate))
			printf("WINNING\n");
		else
			printf("LOSING\n");
	}

	// printf("%d\n",dp.size());
	return 0;
}