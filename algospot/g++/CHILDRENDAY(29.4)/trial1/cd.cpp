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
#include <string>

bool mod_found[10000];
int mod_parent[10000];
int mod_val[10000];
std::vector<int> plist;

void rec_populate(int cur){
	plist.push_back(mod_val[cur]);
	if(mod_parent[cur] != cur){
		rec_populate(mod_parent[cur]);
	}
}

void print_answer(int start){
	plist.clear();
	rec_populate(start);
	std::reverse(plist.begin(),plist.end());
	for(auto p:plist){
		printf("%d",p);
	}
	printf("\n");
}

void solve(char D[11], int N, int M){
	for(int i=0; i<N; ++i){
		mod_found[i] = false;
		mod_parent[i] = -1;
		mod_val[i] = 0;
	}

	int dlen = strlen(D);
	for(int i=0; i<dlen; ++i){
		D[i] -= '0';
	}
	std::sort(&D[0], &D[dlen]);
	std::queue<int> bfs;

	//look for trivial case
	for(int i=0; i<dlen; ++i){
		if((D[i]/N > 0) && (D[i]%N == M)){
			printf("%d\n", D[i]);
			return;
		}
	}

	//solve for non-trivial case
	for(int i=0; i<dlen; ++i){
		if(D[i] == 0){
			continue;
		}
		if(D[i]/N > 0){
			int nextmod = D[i]%N;
			mod_found[nextmod] = true;
			mod_parent[nextmod] = nextmod;
			mod_val[nextmod] = D[i];
			bfs.push(nextmod);
		}
		else{
			bfs.push(-D[i]);
		}
	}

	while(!bfs.empty()){
		int curmod = bfs.front(); bfs.pop();
		int nextnum, nextmod;

		if(curmod >= 0){
			for(int i=0; i<dlen; ++i){
				nextnum = (curmod*10) + D[i];
				nextmod = nextnum % N;
				if(!mod_found[nextmod]){
					mod_found[nextmod] = true;
					mod_parent[nextmod] = curmod;
					mod_val[nextmod] = D[i];
					if(nextmod == M){
						print_answer(M);
						return;
					}
					else{
						bfs.push(nextmod);
					}
				}
			}
		}
		else{
			curmod = -curmod;
			for(int i=0; i<dlen; ++i){
				nextnum = (curmod*10) + D[i];
				nextmod = nextnum % N;
				if(nextnum >= N && !mod_found[nextmod]){
					mod_found[nextmod] = true;
					mod_parent[nextmod] = nextmod;
					mod_val[nextmod] = nextnum;
					if(nextmod == M){
						print_answer(M);
						return;
					}
					else{
						bfs.push(nextmod);
					}
				}
				else if(nextnum < N){
					bfs.push(-nextnum);
				}
			}
		}
	}

	printf("IMPOSSIBLE\n");
}

int main(int argc, char** argv){
	int C, N, M;
	char D[11];
	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%s %d %d", D, &N, &M);
		solve(D, N, M);
	}
}