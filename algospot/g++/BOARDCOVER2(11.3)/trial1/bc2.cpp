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
	vector<pair<int,int>> check;
};

bool iBoard[10][10];
Block iBlock;
Block cand[4];
int cand_cnt = 1;
int block_cnt;
int global_max_cnt = 0;

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

void print_board(bool board[][10]){
	for(int r=0; r<H; ++r){
		for(int c=0; c<W; ++c){
			if(board[r][c])
				printf("#");
			else
				printf(".");
		}
		printf("\n");
	}
	printf("\n");
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

	for(auto p:b.check){
		printf("(%d,%d) ", p.first,p.second);
	}
	printf("\n\n");
}

void compute_blocks(){
	memset(cand, 0, sizeof(cand));

	cand[0] = iBlock;
	cand_cnt = 1;

	for(int i=0; i<3; ++i){
		bool is_new = true;

		cand[cand_cnt] = rotate_clockwise(cand[cand_cnt-1]);
		for(int j=0; j<cand_cnt; ++j){
			if(is_equal(cand[j],cand[cand_cnt])){
				is_new = false;
				break;
			}
		}
		if(is_new)
			cand_cnt++;
	}

	block_cnt = 0;
	for(int r=0; r<cand[0].R; ++r)
		for(int c=0; c<cand[0].C; ++c)
			if(cand[0].m[r][c])
				block_cnt++;

	for(int i=0; i<cand_cnt; ++i){
		int zr = -1;
		int zc = -1;
		for(int r=0; r<cand[i].R && zr < 0; ++r){
			for(int c=0; c<cand[i].C && zc < 0; ++c){
				if(cand[i].m[r][c]){
					zr = r;
					zc = c;
					break;
				}
			}
		}
		cand[i].check.clear();
		for(int r=0; r<cand[i].R; ++r)
			for(int c=0; c<cand[i].C; ++c)
				if(cand[i].m[r][c])
					cand[i].check.push_back(make_pair(r-zr,c-zc));
	}
}

bool can_fit(bool board[][10], int r, int c, Block& b){
	for(auto p:b.check){
		int dr = p.first;
		int dc = p.second;
		if(r+dr < 0 || c+dc < 0 || r+dr >= H || c+dc >= W)
			return false;
		if(board[r+dr][c+dc])
			return false;
	}
	return true;
}

void place_at(bool board[][10], int r, int c, Block& b){
	for(auto p:b.check)
		board[r+p.first][c+p.second] = true;
}

void remove_at(bool board[][10], int r, int c, Block& b){
	for(auto p:b.check)
		board[r+p.first][c+p.second] = false;
}

int rec_solve(bool _iboard[10][10], int already_cnt){
	bool board[10][10];

	memcpy(board,_iboard,sizeof(board));

	// printf("already_cnt: %d\n", already_cnt);
	// print_board(board);

	int space = 0;
	int max_cnt = 0;

	for(int r=0; r<H; ++r)
		for(int c=0; c<W; ++c)
			if(!board[r][c])
				++space;

	if(space < block_cnt)
		return 0;

	if(already_cnt + (space/block_cnt) <= global_max_cnt)
		return 0;

	for(int r=0; r<H; ++r){
		for(int c=0; c<W; ++c){
			if(!board[r][c]){
				if(already_cnt+(space/block_cnt) <= global_max_cnt){
					// printf("hmm? space:%d block_cnt:%d max_cnt:%d\n",space,block_cnt,max_cnt);
					// print_board(board);
					r = H; c = W;
					break;
				}
				for(int b=0; b<cand_cnt; ++b){
					if(can_fit(board,r,c,cand[b])){
						// printf("can_fit %d %d %d\n",r,c,b);
						// print_block(cand[b]);

						place_at(board,r,c,cand[b]);
						max_cnt = max(max_cnt, 1 + rec_solve(board, already_cnt+1));
						global_max_cnt = max(global_max_cnt, already_cnt+max_cnt);
						remove_at(board,r,c,cand[b]);
					}
				}
				board[r][c] = true;
				--space;
			}
		}
	}

	return max_cnt;
}


void solve(){
	compute_blocks();

	// for(int i=0; i<cand_cnt; ++i)
	// 	print_block(cand[i]);

	global_max_cnt = 0;
	printf("%d\n", rec_solve(iBoard, 0));
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}