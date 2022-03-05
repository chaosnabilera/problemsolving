#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

int C, N;
char word[1000][21];
int wordlen[1000];
bool adj[26][26];
bool visited[26];
std::vector<int> order;

void dfs(int c){
	visited[c] = true;
	for(int n=0; n<26; ++n){
		if(!visited[n] && adj[c][n]){
			dfs(n);
		}
	}
	order.push_back(c);
}

void solve(){
	memset(adj,0,sizeof(adj));
	memset(visited,0,sizeof(visited));
	order.clear();

	for(int i=0; i<N; ++i){
		wordlen[i] = strlen(word[i]);
	}
	for(int i=0; i<N-1; ++i){
		int minlen = std::min(wordlen[i], wordlen[i+1]);
		for(int j=0; j<minlen; ++j){
			if(word[i][j] != word[i+1][j]){
				adj[word[i][j]-'a'][word[i+1][j]-'a'] = true;
				break;
			}
		}
	}

	for(int c=0; c<26; ++c){
		if(!visited[c]){
			dfs(c);
		}
	}

	std::reverse(order.begin(), order.end());

	for(int p=0; p<order.size(); ++p){
		for(int n=p+1; n<order.size(); ++n){
			if(adj[order[n]][order[p]]){
				order.clear();
				return;
			}
		}
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
			printf("INVALID HYPOTHESIS\n");
		}
		else{
			for(auto i:order){
				printf("%c",'a'+i);
			}
			printf("\n");
		}
	}
}