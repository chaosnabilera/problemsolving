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

typedef struct _Node{
	std::vector<char> digits;
	int mod;
	bool is_larger;
} Node;

void solve(char D[11], int N, int M){
	bool mod_found[10000] = {0};
	int dlen = strlen(D);
	std::sort(&D[0], &D[1]);
	std::queue<Node> bfs;

	//look for trivial case
	for(int i=0; i<dlen; ++i){
		int d = D[i]-'0';
		if((d/N > 0) && (d%N == M)){
			printf("%d\n", d);
			return;
		}
	}

	//solve for non-trivial case
	for(int i=0; i<dlen; ++i){
		int d = D[i]-'0';
		Node node;
		if(d == 0){
			continue;
		}
		node.digits.push_back(D[i]);
		node.mod = d%N;
		node.is_larger = (d/N > 0);
		bfs.push(node);
	}

	while(!bfs.empty()){
		Node node = bfs.front(); bfs.pop();

		if(node.is_larger){
			for(int i=0; i<dlen; ++i){
				int d = D[i] - '0';
				int nextmod = ((node.mod*10)+d) % N;
				if(nextmod == M){
					for(auto c:node.digits){
						printf("%c",c);
					}
					printf("%d\n",d);
					return;
				}
				else if(!mod_found[nextmod]){
					mod_found[nextmod] = true;
					Node newnode = node;
					newnode.digits.push_back(D[i]);
					newnode.mod = nextmod;
					newnode.is_larger = true;
					bfs.push(newnode);
				}
			}
		}
		else{
			for(int i=0; i<dlen; ++i){
				int d = D[i]-'0';
				int nextnum = (node.mod*10) + d;
				int nextmod = nextnum % N;

				if(nextnum >= N && !mod_found[nextmod]){
					mod_found[nextmod] = true;
					if(nextmod == M){
						for(auto c:node.digits){
							printf("%c",c);
						}
						printf("%d\n",d);
						return;
					}
					else{
						Node newnode = node;
						newnode.digits.push_back(D[i]);
						newnode.mod = nextmod;
						newnode.is_larger = true;
						bfs.push(newnode);
					}
				}
				else if(nextnum < N){
					Node newnode = node;
					newnode.digits.push_back(D[i]);
					newnode.mod = nextnum;
					newnode.is_larger = false;
					bfs.push(newnode);
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