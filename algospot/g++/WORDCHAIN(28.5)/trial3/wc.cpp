#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int N;
vector<string> iWord;

vector<string> Graph[26];
vector<string> Stack;
vector<string> Answer;

void get_input(){
	int i,g;
	char line[0x10];

	for(int i=0; i<26; ++i)
		Graph[i].clear();

	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%s", line);
		string w = line;
		Graph[w[0]-'a'].push_back(w);
	}
}

void dfs(int s){
	int n = -1;

	// printf("%c %lu %lu %lu\n",s+'a',Graph[s].size(),Stack.size(),Answer.size());

	if(Graph[s].empty()){
		if(!Stack.empty()){
			Answer.push_back(Stack.back());
			n = Stack.back()[0] - 'a';
			// printf("A %s\n",Stack.back().c_str());
			Stack.pop_back();
		}
	}
	else{
		Stack.push_back(Graph[s].back());
		n = Graph[s].back()[Graph[s].back().size()-1] - 'a';
		// printf("S %s\n",Graph[s].back().c_str());
		Graph[s].pop_back();
	}

	if(n != -1)
		dfs(n);
}

bool solve(){
	int outcnt[26] = {0};
	int incnt[26] = {0};
	int same_cnt = 0;
	int in1_cnt = 0;
	int in1_i = -1;
	int out1_cnt = 0;
	int out1_i = -1;
	int other_cnt = 0;

	Stack.clear();
	Answer.clear();

	for(int i=0; i<26; ++i){
		outcnt[i] = Graph[i].size();
		for(string& s:Graph[i]){
			incnt[s[s.size()-1]-'a']++;
		}
	}

	for(int i=0; i<26; ++i){
		if(incnt[i] == outcnt[i])
			same_cnt++;
		else if(incnt[i] == outcnt[i]+1){
			in1_cnt++;
			in1_i = i;
		}
		else if(outcnt[i] == incnt[i]+1){
			out1_cnt++;
			out1_i = i;
		}
		else
			other_cnt++;
	}

	if(same_cnt == 26){
		for(int i=0; i<26; ++i){
			if(!Graph[i].empty()){
				dfs(i);
				break;
			}
		}
	}
	else if(in1_cnt == 1 && out1_cnt == 1 && same_cnt == 24){
		dfs(out1_i);
	}
	else{
		return false;
	}

	if(Answer.size() != N)
		return false;

	reverse(Answer.begin(), Answer.end());
	return true;
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		if(solve()){
			for(auto& s:Answer){
				printf("%s ", s.c_str());
			}
			printf("\n");
		}
		else{
			printf("IMPOSSIBLE\n");
		}
	}
}