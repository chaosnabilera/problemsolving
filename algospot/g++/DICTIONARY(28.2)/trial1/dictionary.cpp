#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

void dfs(int cur, bool* visited, bool adj[][26], std::vector<int>& order){
	visited[cur] = true;
	for(int nxt=0; nxt<26; ++nxt){
		if(!visited[nxt] && adj[cur][nxt]){
			dfs(nxt, visited, adj, order);
		}
	}
	order.push_back(cur);
}

std::vector<int> solve(int N, char word[][21]){
	int wordlen[1000];
	bool visited[26] = {false};
	bool adj[26][26] = {false};
	std::vector<int> order;

	for(int i=0; i<N; ++i){
		wordlen[i] = strlen(word[i]);
	}

	for(int i=0; i<N-1; ++i){
		int minlen = std::min(wordlen[i],wordlen[i+1]);
		for(int j=0; j<minlen; ++j){
			if(word[i][j] != word[i+1][j]){
				adj[word[i][j] - 'a'][word[i+1][j] - 'a'] = true;
				break;
			}
		}
	}

	for(int c=0; c<26; ++c){
		if(!visited[c])
			dfs(c, visited, adj, order);
	}

	std::reverse(order.begin(), order.end());

	for(int i=0; i<26; ++i){
		for(int j=i+1; j<26; ++j){
			if(adj[order[j]][order[i]])
				return std::vector<int>();
		}
	}

	return order;
}



int main(int argc, char** argv){
	int C, N;
	char words[1000][21] = {0};
	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d", &N);
		for(int n=0; n<N; ++n){
			scanf("%s", words[n]);
		}
		std::vector<int> ans = solve(N,words);
		if(ans.size() > 0){
			for(auto i:ans){
				printf("%c",'a'+i);
			}
			printf("\n");
		}
		else{
			printf("INVALID HYPOTHESIS\n");
		}
	}
}