#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

int C, N;
char word[100][11];
int wordlen[100];
std::vector<int> edge[26][26];
int indeg[26];
int outdeg[26];
std::vector<int> order;

void dfs(int c){
	for(int n=0; n<26; ++n){
		if(!edge[c][n].empty()){
			int w = edge[c][n].back(); edge[c][n].pop_back();
			dfs(n);
			order.push_back(w);
		}
	}
}

void solve(){
	for(int i=0; i<N; ++i){
		wordlen[i] = strlen(word[i]);
	}
	for(int i=0; i<26; ++i){
		for(int j=0; j<26; ++j){
			edge[i][j].clear();
		}
	}
	memset(indeg,0,sizeof(indeg));
	memset(outdeg,0,sizeof(outdeg));
	order.clear();

	for(int i=0; i<N; ++i){
		int from = word[i][0]-'a';
		int to = word[i][wordlen[i]-1]-'a';
		edge[from][to].push_back(i);
		++indeg[to];
		++outdeg[from];
	}

	int iosame = 0;
	int i1more = 0;
	int last_i1more = -1;
	int o1more = 0;
	int last_o1more = -1;

	for(int c=0; c<26; ++c){
		if(indeg[c] == outdeg[c]){
			++iosame;
		}
		else if(indeg[c] == outdeg[c]+1){
			++i1more;
			last_i1more = c;
		}
		else if(indeg[c]+1 == outdeg[c]){
			++o1more;
			last_o1more = c;
		}
		else{
			return;
		}
	}

	if(!(i1more == 0 && o1more == 0) && !(i1more == 1 && o1more == 1)){
		return;
	}

	if(i1more == 1 && o1more == 1){
		edge[last_i1more][last_o1more].push_back(999);
	}

	for(int c=0; c<26; ++c){
		if(outdeg[c] > 0){
			dfs(c);
			break;
		}
	}

	std::reverse(order.begin(), order.end());

	if(i1more == 1 && o1more == 1){
		int e999 = -1;
		for(int i=0; i<order.size(); ++i){
			if(order[i] == 999){
				e999 = i;
				break;
			}
		}

		std::vector<int> neworder;
		for(int i=e999+1; i<order.size(); ++i){
			neworder.push_back(order[i]);
		}
		for(int i=0; i<e999; ++i){
			neworder.push_back(order[i]);
		}
		order = neworder;
	}

	if(order.size() != N){
		order.clear();
	}
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d", &N);
		for(int i=0; i<N; ++i){
			scanf("%s", word[i]);
		}
		solve();

		if(order.empty()){
			printf("IMPOSSIBLE\n");
		}
		else{
			for(auto i:order){
				if(i < N){
					printf("%s ",word[i]);
				}
			}
			printf("\n");
		}
	}
}