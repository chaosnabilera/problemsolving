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

int R,C;
bool iBoard[20][20];

int Block[4][3][2] = {
	{{0,0},{1,-1},{1, 0}},
	{{0,0},{1, 0},{1, 1}},
	{{0,0},{0, 1},{1, 1}},
	{{0,0},{0, 1},{1, 0}}
};

void get_input(){
	char iline[21];

	scanf("%d %d", &R, &C);
	for(int r=0; r<R; ++r){
		scanf("%s", iline);
		for(int c=0; c<C; ++c)
			iBoard[r][c] = (iline[c] == '.');
	}
}

bool in_boundary(int r, int c){
	return (r >= 0 && r < R && c >= 0 && c < C);
}

int rec_solve(bool input_board[][20]){
	bool board[20][20];
	memcpy(board,input_board,sizeof(board));

	for(int r=0; r<R; ++r){
		for(int c=0; c<C; ++c){
			if(board[r][c]){
				int cnt = 0;
				for(int bi=0; bi<4; ++bi){
					bool can_fit = true;
					for(int i=0; i<3; ++i){
						if(!(in_boundary(r+Block[bi][i][0],c+Block[bi][i][1]) && board[r+Block[bi][i][0]][c+Block[bi][i][1]])){
							can_fit = false;
							break;
						}
					}

					if(can_fit){
						for(int i=0; i<3; ++i)
							board[r+Block[bi][i][0]][c+Block[bi][i][1]] = false;
						cnt += rec_solve(board);
						for(int i=0; i<3; ++i)
							board[r+Block[bi][i][0]][c+Block[bi][i][1]] = true;
					}
				}
				return cnt;
			}
		}
	}
	return 1;
}

void solve(){
	printf("%d\n",rec_solve(iBoard));
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}