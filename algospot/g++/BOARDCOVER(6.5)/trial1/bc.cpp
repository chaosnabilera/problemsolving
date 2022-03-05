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

int C, H, W;

vector<string> iboard;
const char mask[4][2][2] = {
	{{1,0},{1,1}},
	{{0,1},{1,0}},
	{{0,1},{1,1}},
	{{1,-1},{1,0}},
};

void print_board(bool board[22][22]){
	for(int r=0; r<22; ++r){
		for(int c=0; c<22; ++c){
			if(board[r][c]){
				printf(".");
			}
			else{
				printf("#");
			}
		}
		printf("\n");
	}
	printf("\n");
}

int rec_solve(bool board[22][22]){
	int cnt = 0;
	// print_board(board);
	for(int r=1; r<=H; ++r){
		for(int c=1; c<=W; ++c){
			if(board[r][c]){
				for(int m=0; m<4; ++m){
					// printf("m:%d\n",m);
					int r1 = r+mask[m][0][0];
					int c1 = c+mask[m][0][1];
					int r2 = r+mask[m][1][0];
					int c2 = c+mask[m][1][1];
					//printf("%d %d / %d %d / %d %d\n",r,c,r1,c1,r2,c2);
					if(board[r1][c1] && board[r2][c2]){
						board[r][c] = false;
						board[r1][c1] = false;
						board[r2][c2] = false;
						cnt += rec_solve(board);
						board[r][c] = true;
						board[r1][c1] = true;
						board[r2][c2] = true;
					}
				}

				return cnt;
			}
		}
	}
	// printf("?\n");
	return 1;
}

void get_input(){
	string il;
	scanf("%d %d", &H, &W);
	iboard.clear();

	for(int i=0; i<H; ++i){
		cin >> il;
		iboard.push_back(il);
	}
}

int main(int argc, char** argv){
	bool board[22][22];

	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		memset(board,0,sizeof(board));
		for(int r=0; r<H; ++r){
			for(int c=0; c<W; ++c){
				if(iboard[r][c] == '.'){
					board[r+1][c+1] = true;
				}
			}
		}
		printf("%d\n", rec_solve(board));
	}
}