// took 0:32:49 to write

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
vector<string> W;
vector<vector<char>> A;
unordered_set<int> Graph[26];
bool Visited[26];
vector<int> Topology;

void get_input(){
	char line[0x20];
	scanf("%d", &N);
	W.clear();
	for(int i=0; i<N; ++i){
		scanf("%s", line);
		W.push_back(line);
	}

	// make alphabet to 0-25
	A.clear();
	for(string& s:W){
		vector<char> a(s.size());
		for(int i=0; i<s.size(); ++i)
			a[i] = s[i]-'a';
		A.push_back(a);
	}

	// Clear Graph
	for(int i=0; i<26; ++i)
		Graph[i].clear();
}

void rec_build_graph(vector<int>& aidxs, int si){
	vector<int> curlv;

	curlv.push_back(A[aidxs[0]][si]);
	for(int i=1; i<aidxs.size(); ++i){
		int ai = aidxs[i];
		if(curlv.back() != A[ai][si])
			curlv.push_back(A[ai][si]);
	}

	for(int i=0; i<curlv.size()-1; ++i){
		int lc = curlv[i];
		int hc = curlv[i+1];
		Graph[lc].insert(hc);
	}

	int i = 0;
	while(i < aidxs.size()-1){
		vector<int> next_aidxs;
		int j = i+1;

		if(A[aidxs[i]].size() > si+1)
			next_aidxs.push_back(aidxs[i]);
		
		while(j < aidxs.size() && A[aidxs[i]][si] == A[aidxs[j]][si]){
			if(A[aidxs[j]].size() > si+1)
				next_aidxs.push_back(aidxs[j]);
			++j;
		}

		if(next_aidxs.size() > 1){
			rec_build_graph(next_aidxs, si+1);
		}

		i = j;
	}
}

void dfs(int cur){
	if(Visited[cur])
		return;
	Visited[cur] = true;
	for(auto nxt:Graph[cur])
		dfs(nxt);
	Topology.push_back(cur);
}

bool solve(){
	// find shorter coming later than longer
	for(int i=0; i<W.size()-1; ++i){
		if(W[i].size() > W[i+1].size() && W[i].substr(0,W[i+1].size()) == W[i+1]){
			return false;
		}
	}

	// build graph
	vector<int> aidxs(A.size());
	for(int i=0; i<A.size(); ++i)
		aidxs[i] = i;
	rec_build_graph(aidxs, 0);

	// dfs
	memset(Visited, 0, sizeof(Visited));
	Topology.clear();
	for(int i=25; i>=0; --i)
		dfs(i);
	reverse(Topology.begin(),Topology.end());

	for(int i=1; i<26; ++i){
		int ah = Topology[i];
		for(int j=0; j<i; ++j){
			int al = Topology[j];
			// printf("%d %d\n",ah, al);
			if(Graph[ah].find(al) != Graph[ah].end())
				return false;
		}
	}

	return true;
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		if(solve()){
			for(int v:Topology){
				printf("%c",v+'a');
			}
			printf("\n");
		}
		else{
			printf("INVALID HYPOTHESIS\n");
		}
	}
}