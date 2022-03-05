#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

int C,N;
char word[100][11];
int wordlen[100];
std::vector<int> adj[26][26];
int indeg[26];
int outdeg[26];
std::vector<int> order;

void dfs(int c){
	for(int n=0; n<26; ++n){
		if(!adj[c][n].empty()){
			int w = adj[c][n].back(); adj[c][n].pop_back();
			dfs(n);
			order.push_back(w);
		}
	}
}

void solve(){
	for(int i=0; i<N; ++i){
		wordlen[i] = strlen(word[i]);
	}
	for(int from=0; from<26; ++from){
		for(int to=0; to<26; ++to){
			adj[from][to].clear();
		}
	}
	memset(indeg,0,sizeof(indeg));
	memset(outdeg,0,sizeof(outdeg));
	order.clear();

	for(int i=0; i<N; ++i){
		int from = word[i][0] - 'a';
		int to = word[i][wordlen[i]-1] - 'a';
		adj[from][to].push_back(i);
		++outdeg[from];
		++indeg[to];
	}

	int i1cnt = 0;
	int i1last = -1;
	int o1cnt= 0;
	int o1last = -1;

	for(int c=0; c<26; ++c){
		int delta = indeg[c]-outdeg[c];
		if(delta == 1){
			++i1cnt;
			i1last = c;
		}
		if(delta == -1){
			++o1cnt;
			o1last = c;
		}
		if(delta > 1 || delta < -1)
			return;
	}

	if(!(i1cnt == 0 && o1cnt == 0) && !(i1cnt == 1 && o1cnt == 1)){
		return;
	}

	if(i1cnt == 1 && o1cnt == 1){
		dfs(o1last);
	}
	else{
		for(int c=0; c<26; ++c){
			if(outdeg[c] > 0){
				dfs(c);
				break;
			}
		}
	}

	std::reverse(order.begin(), order.end());
	if(order.size() != N){
		order.clear();
	}
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d", &N);
		for(int i=0; i<N; ++i){
			scanf("%s",word[i]);
		}
		solve();
		if(order.empty()){
			printf("IMPOSSIBLE\n");
		}
		else{
			for(auto i:order){
				printf("%s ", word[i]);
			}
			printf("\n");
		}
	}
}