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

struct Block{
	bool m[10][10];
	int R,C;

	void print(){
		for(int r=0; r<R; ++r){
			for(int c=0; c<C; ++c){
				if(m[r][c])
					printf(".");
				else
					printf("#");
			}
			printf("\n");
		}
	}
};

int H,W;
bool iBoard[10][10];
Block iBlock;

vector<pair<int,int>> Blocks[4];
int BlockTypeCnt;
int BlockSize;
int GlobalMaxCnt;

void get_input(){
	char iline[11];
	memset(iBoard, 0, sizeof(iBoard));
	memset(&iBlock, 0, sizeof(iBlock));

	scanf("%d %d %d %d", &H, &W, &(iBlock.R), &(iBlock.C));
	for(int r=0; r<H; ++r){
		scanf("%s", iline);
		for(int c=0; c<W; ++c)
			iBoard[r][c] = (iline[c] == '.');
	}
	for(int r=0; r<iBlock.R; ++r){
		scanf("%s", iline);
		for(int c=0; c<iBlock.C; ++c)
			iBlock.m[r][c] = (iline[c] == '.');
	}
}

Block rotate_block(Block& b){
	Block res = {0};
	res.R = b.C; res.C = b.R;
	for(int r=0; r<res.R; ++r)
		for(int c=0; c<res.C; ++c)
			res.m[r][c] = b.m[b.R-1-c][r];
	return res;
}

vector<pair<int,int>> block_to_vector(Block& b){
	vector<pair<int,int>> res;
	int sr = -1;
	int sc = -1;

	for(int r=0; r<b.R && sr == -1; ++r)
		for(int c=0; c<b.C; ++c)
			if(!b.m[r][c]){
				sr = r;
				sc = c;
				break;
			}

	for(int r=0; r<b.R; ++r)
		for(int c=0; c<b.C; ++c)
			if(!b.m[r][c]){
				res.push_back(make_pair(r-sr,c-sc));
			}
	return res;
}

bool can_place(bool board[][10], int r, int c, vector<pair<int,int>>& b){
	for(auto p:b){
		int rr = r+p.first;
		int cc = c+p.second;
		if(rr < 0 || rr >= H || cc < 0 || cc >= W || !board[rr][cc])
			return false;
	}
	return true;
}

void place_at(bool board[][10], int r, int c, vector<pair<int,int>>& b){
	for(auto p:b)
		board[r+p.first][c+p.second] = false;
}

void remove_at(bool board[][10], int r, int c, vector<pair<int,int>>& b){
	for(auto p:b)
		board[r+p.first][c+p.second] = true;
}

void print_board(bool board[][10]){
	printf("\n");
	for(int r=0; r<H; ++r){
		for(int c=0; c<W; ++c){
			if(board[r][c])
				printf(".");
			else
				printf("#");
		}
		printf("\n");
	}
}

int rec_solve(int already, bool _iboard[][10]){
	bool board[10][10];
	int empty_cnt = 0;
	int max_cnt = 0;

	for(int r=0; r<H; ++r){
		for(int c=0; c<W; ++c){
			board[r][c] = _iboard[r][c];
			if(board[r][c])
				++empty_cnt;
		}
	}

	for(int r=0; r<H; ++r){
		for(int c=0; c<W; ++c){
			if(already + max_cnt + (empty_cnt/BlockSize) <= GlobalMaxCnt){
				return max_cnt;
			}
			
			if(board[r][c]){
				for(int bi=0; bi<BlockTypeCnt; ++bi){
					if(can_place(board,r,c,Blocks[bi])){
						place_at(board,r,c,Blocks[bi]);
						max_cnt = max(max_cnt, 1 + rec_solve(already+1, board));
						GlobalMaxCnt = max(GlobalMaxCnt, already+max_cnt);
						remove_at(board,r,c,Blocks[bi]);
					}
				}
				board[r][c] = false;
				--empty_cnt;
			}
		}
	}

	return max_cnt;
}

void solve(){
	// create blocks
	Block b = iBlock;
	// b.print();
	Blocks[0] = block_to_vector(b);
	BlockTypeCnt = 1;
	for(int i=0; i<3; ++i){
		bool is_new = true;
		b = rotate_block(b);
		// printf("%d\n",i);
		Blocks[BlockTypeCnt] = block_to_vector(b);
		for(int j=0; j<BlockTypeCnt; ++j){
			if(Blocks[j] == Blocks[BlockTypeCnt]){
				is_new = false;
				break;
			}
		}
		if(is_new){
			// b.print();
			// printf("%d new\n",i);
			BlockTypeCnt++;
		}
	}

	BlockSize = Blocks[0].size();
	GlobalMaxCnt = 0;

	printf("%d\n", rec_solve(0,iBoard));
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}