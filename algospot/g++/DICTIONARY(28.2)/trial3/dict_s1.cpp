// took 1:39:07 to write

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
vector<string> iDict;
unordered_set<int> Graph[26];
bool Visited[26];
vector<int> AOrder;

#define IDX(c) (c-'a')

void get_input(){
	char line[0x20];

	iDict.clear();
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%s", line);
		iDict.push_back(line);
	}

	for(int i=0; i<26; ++i)
		Graph[i].clear();
}

void print_vec_int(vector<int>& vec){
	for(int v:vec)
		printf("%d ",v);
	printf("\n");
}

void print_vec_int_char(vector<int>& vec){
	for(int v:vec)
		printf("%c ",v+'a');
	printf("\n");
}

void print_graph(){
	for(int i=0; i<26; ++i){
		printf("%c: ", i+'a');
		for(int v:Graph[i])
			printf("%c ", v+'a');
		printf("\n");
	}
}

void rec_build_graph(vector<int> ord, int si){
	vector<int> curlv;

	curlv.push_back(IDX(iDict[ord[0]][si]));
	for(int i=1; i<ord.size(); ++i){
		if(IDX(iDict[ord[i]][si]) != curlv.back())
			curlv.push_back(IDX(iDict[ord[i]][si]));
	}
	for(int i=0; i<curlv.size()-1; ++i){
		Graph[curlv[i]].insert(curlv[i+1]);
	}

	int i = 0;
	while(i < ord.size()-1){
		int j = i+1;
		vector<int> nxtord;
		if(iDict[ord[i]].size() > si+1)
			nxtord.push_back(ord[i]);
		while(j < ord.size() && iDict[ord[i]][si] == iDict[ord[j]][si]){
			if(iDict[ord[j]].size() > si+1)
				nxtord.push_back(ord[j]);
			++j;
		}

		// printf("i: %d\n",i);
		// print_vec_int(nxtord);
		if(nxtord.size() > 1)
			rec_build_graph(nxtord, si+1);
		i = j;
	}
}

void dfs(int cur){
	if(Visited[cur])
		return;

	Visited[cur] = true;
	for(int nxt:Graph[cur])
		dfs(nxt);

	AOrder.push_back(cur);
}

void solve(){
	vector<int> ord;

	// check contradiction
	for(int i=0; i<iDict.size()-1; ++i){
		if(iDict[i].size() > iDict[i+1].size() && 
			iDict[i].substr(0,iDict[i+1].size()) == iDict[i+1]){
			// printf("%s %s\n",iDict[i].c_str(),iDict[i+1].c_str());
			printf("INVALID HYPOTHESIS\n");
			return;
		}
	}

	// build graph
	for(int i=0; i<iDict.size(); ++i)
		ord.push_back(i);
	rec_build_graph(ord, 0);

	// do DFS
	AOrder.clear();
	memset(Visited,0,sizeof(Visited));

	// print_graph();

	for(int i=25; i>=0; --i)
		dfs(i);

	reverse(AOrder.begin(),AOrder.end());

	// print_vec_int_char(AOrder);

	// check for contradiction
	for(int i=1; i<AOrder.size(); ++i){
		for(int j=0; j<i; ++j){
			if(Graph[AOrder[i]].find(AOrder[j]) != Graph[AOrder[i]].end()){
				// printf("%c<->%c\n",i+'a',j+'a');
				printf("INVALID HYPOTHESIS\n");
				return;
			}
		}
	}

	for(int c:AOrder){
		printf("%c",'a'+c);
	}
	printf("\n");
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}