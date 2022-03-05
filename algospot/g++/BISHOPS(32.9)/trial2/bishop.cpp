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

bool Board[8][8];
int RB[8][8];
int LB[8][8];

vector<int> RAdj[64];

int RMatch[64];
int LMatch[64];
bool Visited[64];

int N;

void get_input(){
	char iline[10];

	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%s", iline);
		for(int j=0; j<N; ++j)
			Board[i][j] = (iline[j] == '.');
	}
}

int fill_rb(int rb[][8]){
	int no = -1;
	bool consecutive;

	for(int rr=N-1; rr>=0; --rr){
		int r = rr;
		int c = 0;
		consecutive = false;
		while(r<N && c<N){
			if(Board[r][c]){
				if(!consecutive){
					consecutive = true;
					++no;
				}
				rb[r][c] = no;
			}
			else{
				rb[r][c] = -1;
				consecutive = false;
			}
			++r; ++c;
		}
	}
	for(int cc=1; cc<N; ++cc){
		int r = 0;
		int c = cc;
		consecutive = false;
		while(r<N && c<N){
			if(Board[r][c]){
				if(!consecutive){
					consecutive = true;
					++no;
				}
				rb[r][c] = no;
			}
			else{
				rb[r][c] = -1;
				consecutive = false;
			}
			++r; ++c;
		}
	}

	return no+1;
}

int fill_lb(int lb[][8]){
	int no = -1;
	bool consecutive = false;

	for(int cc=0; cc<N; ++cc){
		int r = 0;
		int c = cc;
		consecutive = false;

		while(r < N && c >= 0){
			if(Board[r][c]){
				if(!consecutive){
					consecutive = true;
					++no;
				}
				lb[r][c] = no;
			}
			else{
				lb[r][c] = -1;
				consecutive = false;
			}
			++r; --c;
		}
	}

	for(int rr=1; rr<N; ++rr){
		int r = rr;
		int c = N-1;
		consecutive = false;

		while(r < N && c >= 0){
			if(Board[r][c]){
				if(!consecutive){
					consecutive = true;
					++no;
				}
				lb[r][c] = no;
			}
			else{
				lb[r][c] = -1;
				consecutive = false;
			}
			++r; --c;
		}
	}

	return no+1;
}

void print_board(int b[][8]){
	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			printf("%3d",b[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}

bool dfs(int r){
	if(Visited[r])
		return false;

	Visited[r] = true;
	
	for(int l:RAdj[r]){
		if(LMatch[l] == -1 || dfs(LMatch[l])){
			RMatch[r] = l;
			LMatch[l] = r;
			return true;
		}
	}
	return false;
}

void solve(){
	bool Adj[64][64] = {0};

	int rcnt = fill_rb(RB);
	int lcnt = fill_lb(LB);

	for(int r=0; r<N; ++r)
		for(int c=0; c<N; ++c)
			if(Board[r][c]){
				Adj[RB[r][c]][LB[r][c]] = true;
			}

	for(int r=0; r<rcnt; ++r){
		RMatch[r] = -1;
		RAdj[r].clear();
		for(int l=0; l<lcnt; ++l){
			if(Adj[r][l])
				RAdj[r].push_back(l);
		}
	}

	for(int i=0; i<lcnt; ++i)
		LMatch[i] = -1;

	int cnt = 0;
	for(int ri=0; ri<rcnt; ++ri)
		if(RMatch[ri] == -1){
			memset(Visited,0,sizeof(Visited));
			if(dfs(ri))
				++cnt;
		}

	printf("%d\n",cnt);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}