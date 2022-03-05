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

//#define DEBUG_PRINT
#ifdef DEBUG_PRINT
#define DPRINT(...) printf(__VA_ARGS__)
#else
#define DPRINT(...)
#endif

int C, H, W;
vector<string> board;
vector<int> ADJ[400];
vector<int> V_W;
vector<int> V_B;
bool VISITED[400];
int WMATCH[400];
int BMATCH[400];

void get_input(){
	string istr;

	board.clear();
	scanf("%d %d", &H, &W);
	for(int i=0; i<H; ++i){
		cin >> istr;
		board.push_back(istr);
	}
}

void build_graph(){
	int v;

	for(int i=0; i<H*W; ++i){
		ADJ[i].clear();
	}
	V_W.clear();
	V_B.clear();

	for(int r=0; r<H; ++r){
		for(int c=0; c<W; ++c){
			if(board[r][c] != '.'){
				continue;
			}
			v = (r*W)+c;
			(((r+c) & 1) == 0) ? V_W.push_back(v) : V_B.push_back(v);

			if(r > 0 && board[r-1][c] == '.'){
				ADJ[v].push_back(v-W);
			}
			if(r < H-1 && board[r+1][c] == '.'){
				ADJ[v].push_back(v+W);
			}
			if(c > 0 && board[r][c-1] == '.'){
				ADJ[v].push_back(v-1);
			}
			if(c < W-1 && board[r][c+1] == '.'){
				ADJ[v].push_back(v+1);
			}
		}
	}
}

bool dfs(int w){
	if(VISITED[w])
		return false;

	VISITED[w] = true;
	for(int b:ADJ[w]){
		if(BMATCH[b] == -1 || dfs(BMATCH[b])){
			WMATCH[w] = b;
			BMATCH[b] = w;
			return true;
		}
	}
	return false;
}

int bipartite_match(){
	int match_cnt = 0;

	fill(&WMATCH[0],&WMATCH[H*W],-1);
	fill(&BMATCH[0],&BMATCH[H*W],-1);

	for(int w:V_W){
		memset(VISITED, 0, sizeof(VISITED));
		if(dfs(w)){
			match_cnt++;
		}
	}

	return match_cnt;
}

void solve(){
	bool IN_SET[400] = {0};
	int match_cnt = bipartite_match();
	bool changed = false;
	int trap_cnt = 0;

	// DPRINT("bipartite_match_result:\n");
	// for(int w:V_W){
	// 	DPRINT("%d : %d\n",w,WMATCH[w]);
	// }

	for(int w:V_W){
		IN_SET[w] = true;
	}
	for(int b:V_B){
		if(BMATCH[b] == -1){
			IN_SET[b] = true;
		}
	}

	for(int i=0; i<match_cnt; ++i){
		for(int w:V_W){
			if(!IN_SET[w]){
				continue;
			}
			for(int b:ADJ[w]){
				if(IN_SET[b]){
					// DPRINT("w:%d b:%d\n",w,b);
					// DPRINT("WMATCH[w]:%d\n",WMATCH[w]);
					changed = true;
					IN_SET[w] = false;
					IN_SET[WMATCH[w]] = true;
					break;
				}
			}
		}
		if(!changed){
			break;
		}
	}

	for(int v=0; v<400; ++v){
		if(IN_SET[v]){
			int r = v/W;
			int c = v%W;
			DPRINT("%d, %d %d\n",v,r,c);
			board[r][c] = '^';
			trap_cnt++;
		}
	}

	printf("%d\n",trap_cnt);
	for(auto line:board){
		cout << line << endl;
	}
}

void print_graph(){
#ifdef DEBUG_PRINT
	for(auto line:board){
		cout << line << endl;
	}
#endif
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		print_graph();
		build_graph();
		DPRINT("V_W: ");
		for(int w:V_W){
			DPRINT("%d ",w);
		}
		DPRINT("\n");
		solve();
	}
}