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

//#define DEBUG_PRINT
#ifdef DEBUG_PRINT
#define DPRINT(...) printf(__VA_ARGS__)
#else
#define DPRINT(...)
#endif


using namespace std;

int C,N;
vector<string> board;

vector<vector<int>> ID[2];
int MAXID[2];
vector<vector<bool>> ADJ;
vector<int> MATCH[2];
vector<bool> VISITED;

void get_input(){
	string line;
	scanf("%d", &N);
	board.clear();
	for(int i=0; i<N; ++i){
		cin >> line;
		board.push_back(line);
	}
}

bool is_valid(int r, int c){
	return (r >= 0) && (r < N) && (c >= 0) && (c < N) && board[r][c] == '.';
}

void assign_id(){
	int dir[2][2] = {{1,1},{1,-1}};
	int curid[2] = {0,0};

	ID[0] = vector<vector<int>>(N, vector<int>(N,-1));
	ID[1] = vector<vector<int>>(N, vector<int>(N,-1));

	for(int i=0; i<2; ++i){
		for(int r=0; r<N; ++r){
			for(int c=0; c<N; ++c){
				if(ID[i][r][c] == -1 && board[r][c] == '.'){
					int rr = r;
					int cc = c;
					while(is_valid(rr,cc)){
						ID[i][rr][cc] = curid[i];
						rr += dir[i][0];
						cc += dir[i][1];
					}
					curid[i]++;
				}
			}
		}
	}

	MAXID[0] = curid[0];
	MAXID[1] = curid[1];
}

void print_graph(){
#ifdef DEBUG_PRINT
	for(int i=0; i<2; ++i){
		for(int r=0; r<N; ++r){
			for(int c=0; c<N; ++c){
				printf("%4d", ID[i][r][c]);
			}
			printf("\n");
		}
		printf("\n");
	}
#endif
}

void build_graph(){
	ADJ = vector<vector<bool>>(MAXID[0], vector<bool>(MAXID[1],false));
	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			if(board[r][c] == '.'){
				ADJ[ID[0][r][c]][ID[1][r][c]] = true;
			}
		}
	}
}

bool dfs(int v0){
	if(VISITED[v0]){
		return false;
	}
	VISITED[v0] = true;
	for(int v1=0; v1<MAXID[1]; ++v1){
		if(ADJ[v0][v1] && (MATCH[1][v1] == -1 || dfs(MATCH[1][v1]))){
			MATCH[0][v0] = v1;
			MATCH[1][v1] = v0;
			return true;
		}
	}
	return false;
}

int bipartite_match(){
	int res = 0;

	MATCH[0] = vector<int>(MAXID[0],-1);
	MATCH[1] = vector<int>(MAXID[1],-1);

	for(int v0=0; v0<MAXID[0]; ++v0){
		VISITED = vector<bool>(MAXID[0],false);
		if(dfs(v0))
			++res;
	}

	return res;
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		DPRINT("after get_input\n");
		assign_id();
		DPRINT("after assign_id (%d/%d)\n", MAXID[0], MAXID[1]);
		build_graph();
		DPRINT("after build_graph\n");
		print_graph();
		printf("%d\n", bipartite_match());
	}
}