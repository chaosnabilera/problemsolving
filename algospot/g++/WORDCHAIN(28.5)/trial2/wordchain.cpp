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

int N,V;
vector<string> Dict;
int InCnt[26];
int OutCnt[26];
int Graph[26][26];
vector<int> Edge[26][26];
vector<pair<int,int>> DFSRes;

void get_input(){
	char word[0x10];

	scanf("%d", &N);
	Dict.reserve(N);

	for(int i=0; i<N; ++i){
		scanf("%s", word);
		Dict.push_back(word);
	}
}

void init_global(){
	N = 0;
	V = 0;
	Dict.clear();
	memset(InCnt,0,sizeof(InCnt));
	memset(OutCnt,0,sizeof(OutCnt));
	memset(Graph,0,sizeof(Graph));
	for(int i=0; i<26; ++i)
		for(int j=0; j<26; ++j)
			Edge[i][j].clear();
	DFSRes.clear();
}

void dfs(int beg){
	if(OutCnt[beg] == 0)
		return;
	for(int end=0; end<26; ++end){
		while(Graph[beg][end]){
			OutCnt[beg]--;
			InCnt[end]--;
			Graph[beg][end]--;
			dfs(end);
			// printf("%c %c\n",'a'+beg,'a'+end);
			DFSRes.push_back(make_pair(beg,end));
		}
	}
}

void solve(){
	int same = 0;
	int last_same = -1;
	int out_1more = 0;
	int last_out_1more = -1;
	int in_1more = 0;
	int last_in_1more = -1;
	int dfs_beg;

	for(int i=0; i<N; ++i){
		string& word = Dict[i];
		// printf("%s\n",word.c_str());
		int beg = word[0]-'a';
		int end = word[word.size()-1]-'a';
		OutCnt[beg]++;
		InCnt[end]++;
		Graph[beg][end]++;
		Edge[beg][end].push_back(i);
	}

	V = 0;
	for(int i=0; i<26; ++i){
		if(InCnt[i] == 0 && OutCnt[i] == 0)
			continue;
		++V;
		if(InCnt[i] == OutCnt[i]){
			++same;
			last_same = i;
		}
		else if(OutCnt[i] == InCnt[i]+1){
			++out_1more;
			last_out_1more = i;
		}
		else if(InCnt[i] == OutCnt[i]+1){
			++in_1more;
			last_in_1more = i;
		}
	}

	// printf("?\n");

	if(same == V){
		dfs_beg = last_same;
	}
	else if((same == V-1 && out_1more == 1) || (same == V-2 && out_1more == 1 && in_1more == 1)){
		dfs_beg = last_out_1more;
	}
	else{
		printf("IMPOSSIBLE\n");
		return;
	}

	dfs(dfs_beg);
	if(DFSRes.size() != N){
		printf("IMPOSSIBLE\n");
		return;
	}

	reverse(DFSRes.begin(),DFSRes.end());
	for(auto p:DFSRes){
		int beg = p.first;
		int end = p.second;
		int di = Edge[beg][end].back(); Edge[beg][end].pop_back();
		printf("%s ", Dict[di].c_str());
	}
	printf("\n");
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		init_global();
		get_input();
		solve();
	}
}