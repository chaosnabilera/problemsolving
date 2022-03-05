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

const unsigned int MASK_UPPER = (1<<25) - (1<<5); // no need actually...
const unsigned int MASK_LOWER = (1<<5) - 1;

int iBoard;
int Block[6][3];
unsigned int Visited[(1<<25)/32];
unsigned int DP[(1<<25)/32];

void get_input(){
	char iline[0x10];
	iBoard = 0;
	for(int r=0; r<5; ++r){
		scanf("%s", iline);
		for(int c=0; c<5; ++c){
			iBoard = (iline[c] == '.') ? (iBoard | 1) : iBoard;
			iBoard <<= 1;
		}
	}
	iBoard >>= 1;
}

void fill_blocks(){
	// 00011
	Block[0][0] = 3; 
	Block[0][1] = 5; // number of rows
	Block[0][2] = 4; // number of cols

	// 00001
	// 00001
	Block[1][0] = (1<<5) | 1;
	Block[1][1] = 4;
	Block[1][2] = 5;

	// 00001
	// 00011
	Block[2][0] = (1<<5) | 3;
	Block[2][1] = 4;
	Block[2][2] = 4;

	// 00010
	// 00011
	Block[3][0] = (1<<6) | 3;
	Block[3][1] = 4;
	Block[3][2] = 4;

	// 00011
	// 00001
	Block[4][0] = (1<<6) | (1<<5) | 1;
	Block[4][1] = 4;
	Block[4][2] = 4;

	// 00011
	// 00010
	Block[5][0] = (1<<6) | (1<<5) | 2;
	Block[5][1] = 4;
	Block[5][2] = 4;
}

bool rec_solve(int bitmask){
	if(Visited[bitmask >> 5] & (1 << (bitmask & MASK_LOWER)))
		return (DP[bitmask >> 5] & (1 << (bitmask & MASK_LOWER)));

	for(int b=0; b<6; ++b){
		int blk = Block[b][0];
		int rlim = Block[b][1];
		int clim = Block[b][2];

		for(int r=0; r<rlim; ++r){
			for(int c=0; c<clim; ++c){
				int curblk = blk << c;
				if((bitmask & curblk) == curblk){
					if(!rec_solve(bitmask ^ curblk)){
						Visited[bitmask >> 5] |= (1 << (bitmask & MASK_LOWER));
						DP[bitmask >> 5] |= (1 << (bitmask & MASK_LOWER));
						return true;
					}
				}
			}
			blk <<= 5;
		}
	}

	Visited[bitmask >> 5] |= (1 << (bitmask & MASK_LOWER));
	return false;
}

void solve(){
	if(rec_solve(iBoard)){
		printf("WINNING\n");
	}
	else{
		printf("LOSING\n");
	}
}

int main(int argc, char** argv){
	int T;
	fill_blocks();

	memset(Visited,0,sizeof(Visited));
	memset(DP,0,sizeof(DP));

	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}

	// printf("%lu\n",DP.size());
}