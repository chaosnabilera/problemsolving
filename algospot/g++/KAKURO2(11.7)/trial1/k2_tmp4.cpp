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

const int INF = 987654321;

int N; // Board size
int Board[20][20];
int H; // Hint size
int Hint[400][4];

int HHint[20][20];
int VHint[20][20];

int HSpaceLeft[400];
int HValLeft[400];
int HNumLeft[400];
bool Visited[20][20];

int AnsBoard[20][20];

void print_board(int b[][20], int n);

void get_input(){
	int tc;
	scanf("%d", &N);
	for(int r=0; r<N; ++r)
		for(int c=0; c<N; ++c)
			scanf("%d", &Board[r][c]);
	scanf("%d", &H);
	for(int i=0; i<H; ++i){
		scanf("%d %d %d %d", &Hint[i][0], &Hint[i][1], &Hint[i][2], &Hint[i][3]);
		// change 1-based to 0-based
		--Hint[i][0];
		--Hint[i][1];
	}
}

void process_input(){
	for(int r=0; r<N; ++r)
		for(int c=0; c<N; ++c){
			HHint[r][c] = -1;
			VHint[r][c] = -1;
		}

	for(int i=0; i<H; ++i){
		int r   = Hint[i][0];
		int c   = Hint[i][1];
		int dir = Hint[i][2];
		int hsum= Hint[i][3];

		if(dir == 0){
			int cc = c+1;
			while(cc < N && Board[r][cc] == 1){
				HHint[r][cc] = i;
				++cc;
			}
			HSpaceLeft[i] = cc-c-1;
		}
		else{
			int rr = r+1;
			while(rr < N && Board[rr][c] == 1){
				VHint[rr][c] = i;
				++rr;
			}
			HSpaceLeft[i] = rr-r-1;
		}
		HValLeft[i] = hsum;
		HNumLeft[i] = ((1<<9)-1)<<1;
	}
}

void print_board(int b[][20], int n){
	for(int r=0; r<n; ++r){
		for(int c=0; c<n; ++c)
			printf("%3d", b[r][c]);
		printf("\n");
	}
	printf("\n");
}

bool rec_solve(int r, int c){
	if(r < 0 || r >= N || c < 0 || c >= N || Board[r][c] == 0 || Visited[r][c])
		return true;

	Visited[r][c] = true;
	if(HSpaceLeft[HHint[r][c]] == 1 && HSpaceLeft[VHint[r][c]] == 1){
		int hval = HValLeft[HHint[r][c]];
		int vval = HValLeft[VHint[r][c]];
		int hnum = HNumLeft[HHint[r][c]];
		int vnum = HNumLeft[VHint[r][c]];
		if(hval == vval && hval < 10 && hval > 0 && (hnum & (1<<hval)) && (vnum & (1<<hval))){
			return true;
		}
		else{
			Visited[r][c] = false;
			return false;
		}
	}
	else{
		
	}

}

void solve(){
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		process_input();
		solve();
	}
}