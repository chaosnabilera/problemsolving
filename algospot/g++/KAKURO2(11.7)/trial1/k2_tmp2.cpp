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
int Board[21][21];
int H; // Hint size
int Hint[400][4];

int RelCnt[21][21];
int CalcCnt[21][21];
vector<pair<int,int>> VisitOrder;

void get_input(){
	int tc;

	memset(Board,0,sizeof(Board));
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
					RelCnt[r][cc] = col_list.size();
				col_list.clear();
			}
		}
		for(int cc:col_list){
			RelCnt[r][cc] = col_list.size();
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
					RelCnt[rr][c] += row_list.size();
				row_list.clear();
			}
		}
		for(int rr:row_list){
			RelCnt[rr][c] += row_list.size();
		}
		row_list.clear();
	}

	vector<pair<int,int>> space;
	int min_score = 987654321;
	int min_r, min_c;
	for(int r=0; r<N; ++r)
		for(int c=0; c<N; ++c)
			if(Board[r][c]){
				space.push_back(make_pair(r,c));
				if(RelCnt[r][c] < min_score){
					min_r = r;
					min_c = c;
				}
			}

	memcpy(CalcCnt,RelCnt,sizeof(RelCnt));
	VisitOrder.clear();
	VisitOrder.push_back(make_pair(min_r,min_c));
	for(int i=1; i<space.size(); ++i){
		int pr = VisitOrder[i-1].first;
		int pc = VisitOrder[i-1].second;

		if(Board[pr-1][pc])
			CalcCnt[pr-1][pc]--;
		if(Board[pr+1][pc])
			CalcCnt[pr+1][]
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
	print_board(RelCnt, N);

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