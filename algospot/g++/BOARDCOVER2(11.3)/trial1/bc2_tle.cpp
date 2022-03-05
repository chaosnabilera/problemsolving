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

int H,W,R,C;

struct Block{
	bool m[10][10];
	int R;
	int C;
};

bool iBoard[10][10];
Block iBlock;
Block cand[4];
int cand_cnt = 1;

void get_input(){
	char iline[100];
	scanf("%d %d %d %d", &H,&W,&R,&C);
	for(int r=0; r<H; ++r){
		scanf("%s", iline);
		for(int c=0; c<W; ++c)
			iBoard[r][c] = (iline[c] == '#');
	}

	iBlock.R = R;	iBlock.C = C;
	for(int r=0; r<R; ++r){
		scanf("%s", iline);
		for(int c=0; c<C; ++c)
			iBlock.m[r][c] = (iline[c] == '#');
	}
}

Block rotate_clockwise(Block& iblock){
	Block oBlock;
	oBlock.R = iblock.C; oBlock.C = iblock.R;

	for(int r=0; r<oBlock.R; ++r)
		for(int c=0; c<oBlock.C; ++c)
			oBlock.m[r][c] = iblock.m[iblock.R-1-c][r];

	return oBlock;
}

bool is_equal(Block& a, Block& b){
	if(a.R == b.R && a.C == b.C){
		for(int r=0; r<a.R; ++r)
			for(int c=0; c<a.C; ++c)
				if(a.m[r][c] != b.m[r][c])
					return false;
		return true;
	}
	return false;
}

void print_block(Block& b){
	for(int r=0; r<b.R; ++r){
		for(int c=0; c<b.C; ++c){
			if(b.m[r][c])
				printf("#");
			else
				printf(".");
		}
		printf("\n");
	}
	printf("\n");
}

bool can_place(int r, int c, Block& block, bool board[][10]){
	// printf("%d %d %d %d\n",r,c,block.R, block.C);
	if(c < 0 || r+block.R > H || c+block.C > W)
		return false;
	for(int br=0; br<block.R; ++br)
		for(int bc=0; bc<block.C; ++bc)
			if(block.m[br][bc] & board[r+br][c+bc]){
				// printf("%d %d failed at %d %d\n",r,c,r+br,c+bc);
				return false;
			}
	return true;
}

void place_at(int r, int c, Block& block, bool board[][10]){
	for(int br=0; br<block.R; ++br)
		for(int bc=0; bc<block.C; ++bc)
			board[r+br][c+bc] = (board[r+br][c+bc] | block.m[br][bc]);
}

void remove_at(int r, int c, Block& block, bool board[][10]){
	for(int br=0; br<block.R; ++br)
		for(int bc=0; bc<block.C; ++bc)
			if(board[r+br][c+bc] & block.m[br][bc])
				board[r+br][c+bc] = false;
}

void print_board(){
	for(int r=0; r<H; ++r){
		for(int c=0; c<W; ++c){
			if(iBoard[r][c])
				printf("#");
			else
				printf(".");
		}
		printf("\n");
	}
	printf("\n");
}

int rec_solve(bool _iboard[10][10]){
	int max_cnt = 0;

	bool board[10][10];
	memcpy(board,_iboard,sizeof(board));
	
	for(int r=0; r<H; ++r){
		for(int c=0; c<W; ++c){
			if(!board[r][c]){
				for(int b=0; b<cand_cnt; ++b){
					for(int cd=0; cd<cand[b].C; ++cd){
						if(can_place(r,c-cd,cand[b],board)){
							place_at(r,c-cd,cand[b],board);
							if(board[r][c]){
								max_cnt = max(max_cnt, 1+rec_solve(board));
							}
							remove_at(r,c-cd,cand[b],board);
						}
					}
				}
				board[r][c] = true;
			}
		}
	}

	return max_cnt;
}

void solve(){
	cand[0] = iBlock;
	cand_cnt = 1;
	bool is_new;

	for(int i=0; i<3; ++i){
		cand[cand_cnt] = rotate_clockwise(cand[cand_cnt-1]);
		is_new = true;
		for(int j=0; j<cand_cnt; ++j){
			if(is_equal(cand[j],cand[cand_cnt])){
				is_new = false;
				break;
			}
		}
		if(is_new)
			cand_cnt++;
	}

	// for(int i=0; i<cand_cnt; ++i)
	// 	print_block(cand[i]);

	printf("%d\n", rec_solve(iBoard));
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}