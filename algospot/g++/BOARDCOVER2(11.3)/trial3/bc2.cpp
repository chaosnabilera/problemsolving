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

int R,C,bR,bC;
bool iBoard[10][10];
bool iBlock[10][10];
vector<vector<pair<int,int>>> Block;

int BlockSize;
int GMaxCnt;

void get_input(){
	char line[0x10];

	memset(iBoard,0,sizeof(iBoard));
	memset(iBlock,0,sizeof(iBlock));
	Block.clear();

	scanf("%d %d %d %d",&R, &C, &bR, &bC);
	for(int r=0; r<R; ++r){
		scanf("%s", line);
		for(int c=0; c<C; ++c)
			iBoard[r][c] = (line[c] == '.');
	}

	for(int r=0; r<bR; ++r){
		scanf("%s",line);
		for(int c=0; c<bC; ++c)
			iBlock[r][c] = (line[c] == '#');
	}
}

void rotate_block(bool src[][10], bool dst[][10], int sr, int sc){
	int dr = sc;
	int dc = sr;
	for(int r=0; r<dr; ++r)
		for(int c=0; c<dc; ++c)
			dst[r][c] = src[sr-1-c][r];
}

void convert_block_to_sequence(bool block[][10], int br, int bc, vector<pair<int,int>>& seq){
	int o_r = -1; int o_c = -1;

	for(int r=0; r<br && o_r == -1; ++r){
		for(int c=0; c<bc; ++c)
			if(block[r][c]){
				o_r = r;
				o_c = c;
				break;
			}
	}

	seq.clear();
	for(int r=0; r<br; ++r){
		for(int c=0; c<bc; ++c){
			if(block[r][c]){
				seq.push_back(make_pair(r-o_r,c-o_c));
			}
		}
	}
}

void print_block(bool block[][10], int br, int bc){
	for(int r=0; r<br; ++r){
		for(int c=0; c<bc; ++c){
			if(block[r][c])
				printf("#");
			else
				printf(".");
		}
		printf("\n");
	}
	printf("\n");
}

void create_blocks(){
	bool block_src[10][10];
	bool block_dst[10][10];
	vector<pair<int,int>> block_seq;
	int sr,sc,dr,dc;

	// initial block
	sr = bR;
	sc = bC;
	memcpy(block_src, iBlock, sizeof(iBlock));
	convert_block_to_sequence(block_src, sr, sc, block_seq);
	Block.push_back(block_seq);
	BlockSize = block_seq.size();

	// print_block(block_src,sr,sc);

	for(int i=0; i<3; ++i){
		dr = sc; dc = sr;
		memset(block_dst, 0, sizeof(block_dst));
		rotate_block(block_src, block_dst, sr, sc);

		// print_block(block_dst,dr,dc);

		convert_block_to_sequence(block_dst, dr, dc, block_seq);

		bool same_exist = false;
		for(int j=0; j<Block.size(); ++j){
			if(block_seq == Block[j]){
				same_exist = true;
				break;
			}
		}

		if(!same_exist){
			Block.push_back(block_seq);
		}

		if(i<2){
			memcpy(block_src,block_dst,sizeof(block_dst));
			sr = dr; sc = dc;
		}
	}
	// printf("%u\n", Block.size());
}

bool can_place(bool board[][10], int r, int c, vector<pair<int,int>>& b){
	for(pair<int,int>& p:b){
		int rr = r+p.first;
		int cc = c+p.second;
		if(rr < 0 || rr >= R || cc < 0 || cc >= C || (!board[rr][cc]))
			return false;
	}
	return true;
}

void place_at(bool board[][10], int r, int c, vector<pair<int,int>>& b){
	for(pair<int,int>& p:b){
		board[r+p.first][c+p.second] = false;
	}
}

void remove_at(bool board[][10], int r, int c, vector<pair<int,int>>& b){
	for(pair<int,int>& p:b){
		board[r+p.first][c+p.second] = true;
	}
}

int rec_solve(bool input_board[][10], int prev_cnt, int prev_empty_cnt){
	bool board[10][10];
	int empty_cnt = prev_empty_cnt;
	bool do_search = true;

	memcpy(board, input_board, sizeof(board));

	if((empty_cnt < BlockSize) || (prev_cnt + (empty_cnt/BlockSize) <= GMaxCnt)){
		return 0;
	}

	int cnt = 0;

	for(int r=0; r<R && do_search; ++r){
		for(int c=0; c<C && do_search; ++c){
			if((empty_cnt < BlockSize) || (prev_cnt + (empty_cnt/BlockSize) <= GMaxCnt)){
				do_search = false;
				break;
			}

			if(board[r][c]){
				for(vector<pair<int,int>>& b:Block){
					if(can_place(board,r,c,b)){
						place_at(board,r,c,b);
						cnt = max(cnt, 1+rec_solve(board, prev_cnt+1, empty_cnt-BlockSize));
						GMaxCnt = max(GMaxCnt, prev_cnt+cnt);
						remove_at(board,r,c,b);
					}
				}
				board[r][c] = false;
				--empty_cnt;
			}
		}
	}

	return cnt;
}

void solve(){
	create_blocks();
	GMaxCnt = 0;

	int empty_cnt = 0;
	for(int r=0; r<R; ++r)
		for(int c=0; c<C; ++c)
			if(iBoard[r][c])
				empty_cnt++;

	rec_solve(iBoard, 0, empty_cnt);
	printf("%d\n", GMaxCnt);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}