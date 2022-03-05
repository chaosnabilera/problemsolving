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

int N; // Board size
int Board[20][20];
int H; // Hint size
int Hint[400][4];

int HCnt[20][20];
int VCnt[20][20];

int RelCnt[20][20];
vector<pair<int,int>> VisitOrder;

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
	// horizontal scan
	vector<int> col_list;
	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			if(Board[r][c]){
				col_list.push_back(c);
			}
			else{
				for(int cc:col_list)
					HCnt[r][cc] = col_list.size();
				col_list.clear();
			}
		}
		for(int cc:col_list){
			HCnt[r][cc] = col_list.size();
		}
		col_list.clear();
	}

	// vertical scan
	vector<int> row_list;
	for(int c=0; c<N; ++c){
		for(int r=0; r<N; ++r){
			if(Board[r][c]){
				row_list.push_back(r);
			}
			else{
				for(int rr:row_list)
					VCnt[rr][c] = row_list.size();
				row_list.clear();
			}
		}
		for(int rr:row_list){
			VCnt[rr][c] = row_list.size();
		}
		row_list.clear();
	}

	vector<pair<int,pair<int,int>>> hint_score;
	for(int i=0; i<H; ++i){
		int r = Hint[i][0];
		int c = Hint[i][1];
		int dir = Hint[i][2];
		int hsum = Hint[i][3];

		if(dir == 0){ // horizontal
			hint_score.push_back(make_pair(HCnt[r][c+1], make_pair(r,c)));
		}
		else{ // vertical
			hint_score.push_back(make_pair(VCnt[r+1][c], make_pair(0x100+r, 0x100+c)));
		}
	}
	sort(hint_score.begin(), hint_score.end());

	bool taken[20][20] = {0};
	VisitOrder.clear();
	for(auto p:hint_score){
		int score = p.first;
		int r = (p.second.first & 0xFF);
		int c = (p.second.second & 0xFF);

		if(p.second.first < 0x100){ // horizontal
			int cc = c+1;
			while(cc < N && Board[r][cc]){
				if(!taken[r][cc]){
					VisitOrder.push_back(make_pair(r,cc));
					taken[r][cc] = true;
				}
				++cc;
			}
		}
		else{ // vertical
			int rr = r+1;
			while(rr < N && Board[rr][c]){
				if(!taken[rr][c]){
					VisitOrder.push_back(make_pair(rr,c));
					taken[rr][c] = true;	
				}
				++rr;
			}
		}
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

void solve(){
	print_board(Board, N);
	print_board(HCnt, N);
	print_board(VCnt, N);

	for(auto p:VisitOrder){
		printf("(%3d,%3d)\n",p.first,p.second);
	}
	printf("\n");
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