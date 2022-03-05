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
bool TakenToVisit[20][20];

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

void rec_add(int r, int c){
	if(r >= N || c >= N || Board[r][c] == 0 || TakenToVisit[r][c])
		return;

	if(HCnt[r][c] <= VCnt[r][c]){
		int cc = c;
		while(cc < N && Board[r][cc] == 1){
			if(!TakenToVisit[r][cc]){
				VisitOrder.push_back(make_pair(r,cc));
				TakenToVisit[r][cc] = true;
			}
			++cc;
		}
		rec_add(r+1,c);
	}
	else{
		int rr = r;
		while(rr < N && Board[rr][c] == 1){
			if(!TakenToVisit[rr][c]){
				VisitOrder.push_back(make_pair(rr,c));
				TakenToVisit[rr][c] = true;
			}
			++rr;
		}
		rec_add(r,c+1);
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

	memset(TakenToVisit, 0, sizeof(TakenToVisit));
	VisitOrder.clear();
	for(int r=0; r<N; ++r)
		for(int c=0; c<N; ++c)
			rec_add(r,c);
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

	int order_board[20][20] = {0};

	for(int i=0; i<VisitOrder.size(); ++i){
		int r = VisitOrder[i].first;
		int c = VisitOrder[i].second;
		order_board[r][c] = i+1;
	}

	print_board(order_board,N);

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