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

struct Node{
	int parent_mod;
	int in_digit;
};

char D[0x10];
int N,M;
Node ModState[20000];

bool solve(){
	int dlen = strlen(D);
	queue<pair<int,int>> bfsq;

	for(int i=0; i<(2*N); ++i){
		ModState[i].parent_mod = -1;
		ModState[i].in_digit = -1;
	}

	sort(&D[0],&D[dlen]);
	for(int i=0; i<dlen; ++i)
		D[i] -= '0';

	for(int i=0; i<dlen; ++i){
		int d = D[i];
		if(d < N){
			ModState[d%N].parent_mod = -1;
			ModState[d%N].in_digit = d;
		}
		else{
			ModState[N+(d%N)].parent_mod = -1;
			ModState[N+(d%N)].in_digit = d;
		}
		if(d > 0){
			for(int j=0; j<dlen; ++j){
				bfsq.push(make_pair(d%N,D[j]));
			}
		}
	}

	if(ModState[N+M].in_digit != -1)
		return true;

	while(!bfsq.empty()){
		int cur = bfsq.front().first;
		int d   = bfsq.front().second;
		bfsq.pop();

		int nxt;
		if(cur < N){
			nxt = (cur*10)+d;
			if(nxt >= N)
				nxt = N + (nxt % N);
		}
		else{
			nxt = N + ( (((cur-N)*10)+d) % N );
		}

		if(ModState[nxt].parent_mod != -1)
			continue;

		ModState[nxt].parent_mod = cur;
		ModState[nxt].in_digit = d;

		if(nxt == (N+M)){
			return true;
		}

		for(int i=0; i<dlen; ++i){
			bfsq.push(make_pair(nxt,D[i]));
		}
	}

	return false;
}

void print_answer(){
	vector<int> ans;
	ans.push_back(ModState[N+M].in_digit);

	int cur = N+M;
	while(ModState[cur].parent_mod != -1){
		cur = ModState[cur].parent_mod;
		// printf("%d %d\n",cur,ModState[cur].in_digit);
		ans.push_back(ModState[cur].in_digit);
	}

	reverse(ans.begin(),ans.end());
	for(int v:ans)
		printf("%d",v);
	printf("\n");
}

int main(int argc, char** argv){
	int t = 0;

	scanf("%d", &t);
	for(int i=0; i<t; ++i){
		scanf("%s %d %d", D, &N, &M);
		if(solve())
			print_answer();
		else
			printf("IMPOSSIBLE\n");
	}
}