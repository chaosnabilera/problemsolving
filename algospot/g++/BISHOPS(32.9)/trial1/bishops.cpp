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

int C,N;
char board[10][10];

int LR[10][10];
int RL[10][10];
int MAX_LR;
int MAX_RL;

std::vector<std::vector<bool>> adj;
std::vector<int> lrMatch;
std::vector<int> rlMatch;
std::vector<bool> lrVisited;

bool dfs(int lr){
	bool res = false;
	if(!lrVisited[lr]){
		lrVisited[lr] = true;
		for(int rl=0; rl<MAX_RL; ++rl){
			if(adj[lr][rl] && (rlMatch[rl] == -1 || dfs(rlMatch[rl]))){
				lrMatch[lr] = rl;
				rlMatch[rl] = lr;
				return true;
			}
		}
	}
	return res;
}

int bipartite_match(){
	int res = 0;
	lrMatch = std::vector<int>(MAX_LR, -1);
	rlMatch = std::vector<int>(MAX_RL, -1);

	for(int lr=0; lr<MAX_LR; ++lr){
		lrVisited = std::vector<bool>(MAX_LR, false);
		if(dfs(lr)){
			++res;
		}
	}
	return res;
}

void build_graph(){
	adj = std::vector<std::vector<bool>>(MAX_LR, std::vector<bool>(MAX_RL, false));
	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			if(board[r][c] == '.'){
				// printf("%d %d\n",LR[r][c],RL[r][c]);
				adj[LR[r][c]][RL[r][c]] = true;
			}
		}
	}
}

void assign_id(){
	int lr = -1;
	int rl = -1;

	// assign LR id
	for(int sr=N-1; sr>0; --sr){
		bool is_consecutive = false;
		int r = sr;
		int c = 0;
		while(r < N && c < N){
			if(board[r][c] == '.'){
				if(!is_consecutive){
					is_consecutive = true;
					++lr;
				}
				LR[r][c] = lr;
			}
			else{
				is_consecutive = false;
				LR[r][c] = -1;
			}
			++r; ++c;
		}
	}
	for(int sc=0; sc<N; ++sc){
		bool is_consecutive = false;
		int c = sc;
		int r = 0;
		while(r < N && c < N){
			if(board[r][c] == '.'){
				if(!is_consecutive){
					is_consecutive = true;
					++lr;
				}
				LR[r][c] = lr;
			}
			else{
				is_consecutive = false;
				LR[r][c] = -1;
			}
			++r; ++c;
		}
	}

	MAX_LR = lr+1;

	// assign RL id
	for(int sc=0; sc<N; ++sc){
		bool is_consecutive = false;
		int c = sc;
		int r = 0;
		while(r < N && c >= 0){
			if(board[r][c] == '.'){
				if(!is_consecutive){
					is_consecutive = true;
					++rl;
				}
				RL[r][c] = rl;
			}
			else{
				is_consecutive = false;
				RL[r][c] = -1;
			}
			++r; --c;
		}
	}
	for(int sr=1; sr<N; ++sr){
		bool is_consecutive = false;
		int r = sr;
		int c = N-1;
		while(r < N && c >= 0){
			if(board[r][c] == '.'){
				if(!is_consecutive){
					is_consecutive = true;
					++rl;
				}
				RL[r][c] = rl;
			}
			else{
				is_consecutive = false;
				RL[r][c] = -1;
			}
			++r; --c;	
		}
	}

	MAX_RL = rl+1;
}

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%s",board[i]);
	}
}

void print_board(int mode){
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			// printf("%c",board[i][j]);
			if(mode == 0){
				printf("%3d",LR[i][j]);	
			}
			else if(mode == 1){
				printf("%3d",RL[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		// printf("got input\n");
		assign_id();
		// printf("assigned id\n");
		// printf("%d %d\n",MAX_LR,MAX_RL);
		build_graph();
		// printf("built graph\n");

		// print_board(0);
		// print_board(1);

		// printf("%d %d\n",MAX_LR,MAX_RL);
		printf("%d\n", bipartite_match());
	}
}