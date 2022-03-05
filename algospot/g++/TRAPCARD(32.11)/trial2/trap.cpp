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

int R,C;
bool Board[20][20];
vector<int> Adj[400];
vector<int> W;
vector<int> B;
int Match[400];
bool Visited[400];
bool Select[400];

int BOARD_NO(int r, int c) {return (r*C)+c;}

void get_input(){
	char iline[32];
	scanf("%d %d", &R, &C);
	for(int r=0; r<R; ++r){
		scanf("%s", iline);
		for(int c=0; c<C; ++c){
			Board[r][c] = (iline[c] == '.');
		}
	}
}

void build_adj(){
	for(int r=0; r<R; ++r){
		for(int c=0; c<C; ++c){
			int bno = BOARD_NO(r,c);
			Adj[bno].clear();

			if(r > 0   && Board[r-1][c]) Adj[bno].push_back(BOARD_NO(r-1,c)); // up
			if(r < R-1 && Board[r+1][c]) Adj[bno].push_back(BOARD_NO(r+1,c)); // down
			if(c > 0   && Board[r][c-1]) Adj[bno].push_back(BOARD_NO(r,c-1)); // left
			if(c < C-1 && Board[r][c+1]) Adj[bno].push_back(BOARD_NO(r,c+1)); // right
		}
	}
}

bool dfs(int w){
	if(Visited[w])
		return false;
	Visited[w] = true;
	for(int b:Adj[w]){
		if(Match[b] == -1 || dfs(Match[b])){
			Match[w] = b;
			Match[b] = w;
			return true;
		}
	}
	return false;
}

void bipartite_match(){
	for(int i=0; i<400; ++i)
		Match[i] = -1;

	for(int w:W){
		if(Match[w] == -1){
			memset(Visited,0,sizeof(Visited));
			dfs(w);
		}
	}
}

void solve(){
	W.clear(); W.reserve((R*C)>>1);
	B.clear(); B.reserve((R*C)>>1);
	for(int r=0; r<R; ++r){
		for(int c=0; c<C; ++c){
			if(!Board[r][c])
				continue;
			if((r+c)&1)
				W.push_back(BOARD_NO(r,c));
			else
				B.push_back(BOARD_NO(r,c));
		}
	}

	// printf("W:");
	// for(int w:W)
	// 	printf("%3d",w);
	// printf("\n");

	// printf("B:");
	// for(int b:B)
	// 	printf("%3d",b);
	// printf("\n");

	build_adj();

	// for(int w:W){
	// 	printf("Adj[%d]:",w);
	// 	for(int b:Adj[w])
	// 		printf("%3d",b);
	// 	printf("\n");
	// }

	bipartite_match();

	memset(Select,0,sizeof(Select));
	for(int w:W)
		Select[w] = true;
	for(int b:B)
		if(Match[b] == -1)
			Select[b] = true;

	bool changed;

	// for(int w:W)
	// 	if(Match[w] != -1)
	// 		printf("%d - %d\n",w,Match[w]);

	while(true){
		changed = false;
		for(int w:W){
			if(Match[w] == -1)
				continue;
			for(int b:Adj[w]){
				if(Select[w] && Select[b]){
					Select[w] = false;
					Select[Match[w]] = true;
					changed = true;
				}
			}
		}
		if(!changed)
			break;
	}

	int cnt = 0;
	for(int i=0; i<R*C; ++i)
		if(Select[i])
			cnt++;

	printf("%d\n",cnt);

	for(int r=0; r<R; ++r){
		for(int c=0; c<C; ++c){
			if(Board[r][c]){
				if(Select[BOARD_NO(r,c)])
					printf("^");
				else
					printf(".");
			}
			else{
				printf("#");
			}
		}
		printf("\n");
	}
}

int main(int argc, char** argv){
	int num_case;
	scanf("%d", &num_case);
	for(int i=0; i<num_case; ++i){
		get_input();
		solve();
	}
}