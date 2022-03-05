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

unordered_map<int, bool> dp;

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

bool rec_solve(int state){
	if(dp.find(state) != dp.end())
		return dp[state];

	// bool board[5][5];
	// state_to_board(state, board);

	// print_board(board);
	int s3[4] = { p3_1, p3_2, p3_3, p3_4};
	int s2[2] = { p2_1, p2_2 };

	// 3-patterns
	for(int r=0; r<4; ++r){
		for(int c=0; c<4; ++c){
			for(int p=0; p<4; ++p){
				int curpat = s3[p];
				curpat >>= ((r*5)+c);
				if((state & curpat) == curpat){
					if(rec_solve(state ^ curpat) == false){
						dp[state] = true;
						return dp[state];
					}
				}
			}
		}
	}

	// 2-patterns

	for(int r=0; r<4; ++r){
		for(int c=0; c<4; ++c){
			if(board[r][c] && board[r+1][c] && board[r+1][c+1]){
				board[r][c] = false; board[r+1][c] = false; board[r+1][c+1] = false;
				if(rec_solve(board_to_state(board)) == false){
					dp[state] = true;
					return dp[state];
				}
				board[r][c] = true;	board[r+1][c] = true; board[r+1][c+1] = true;
			}
			if(board[r][c] && board[r][c+1] && board[r+1][c]){
				board[r][c] = false; board[r][c+1] = false; board[r+1][c] = false;
				if(rec_solve(board_to_state(board)) == false){
					dp[state] = true;
					return dp[state];
				}
				board[r][c] = true; board[r][c+1] = true; board[r+1][c] = true;
			}
			if(board[r][c+1] && board[r+1][c] && board[r+1][c+1]){
				board[r][c+1] = false; board[r+1][c] = false; board[r+1][c+1] = false;
				if(rec_solve(board_to_state(board)) == false){
					dp[state] = true;
					return dp[state];
				}
				board[r][c+1] = true; board[r+1][c] = true; board[r+1][c+1] = true;
			}
			if(board[r][c] && board[r][c+1] && board[r+1][c+1]){
				board[r][c] = false; board[r][c+1] = false; board[r+1][c+1] = false;
				if(rec_solve(board_to_state(board)) == false){
					dp[state] = true;
					return dp[state];
				}
				board[r][c] = true; board[r][c+1] = true; board[r+1][c+1] = true;
			}
		}
	}

	// 2-patterns
	for(int r=0; r<5; ++r){
		for(int c=0; c<4; ++c){
			if(board[r][c] && board[r][c+1]){
				board[r][c] = false; board[r][c+1] = false;
				if(rec_solve(board_to_state(board)) == false){
					dp[state] = true;
					return dp[state];
				}
				board[r][c] = true; board[r][c+1] = true;
			}
		}
	}

	for(int r=0; r<4; ++r){
		for(int c=0; c<5; ++c){
			if(board[r][c] && board[r+1][c]){
				board[r][c] = false; board[r+1][c] = false;
				if(rec_solve(board_to_state(board)) == false){
					dp[state] = true;
					return dp[state];
				}
				board[r][c] = true; board[r+1][c] = true;
			}
		}
	}

	dp[state] = false;
	return dp[state];
}


int main(int argc, char** argv){
	int istate;
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
}