#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int N;
vector<int> PreOrd;
unordered_map<int,int> PreNumToIdx;
vector<int> InOrd;
unordered_map<int,int> InNumToIdx;

vector<int> Ans;

void get_input(){
	int v;
	scanf("%d", &N);

	PreOrd.resize(N);
	InOrd.resize(N);
	PreNumToIdx.clear();
	InNumToIdx.clear();
	Ans.clear();

	for(int i=0; i<N; ++i){
		scanf("%d", &PreOrd[i]);
		PreNumToIdx[PreOrd[i]] = i;
	}

	for(int i=0; i<N; ++i){
		scanf("%d", &InOrd[i]);
		InNumToIdx[InOrd[i]] = i;
	}
}

void rec_solve(int pbeg, int pend, int ibeg, int iend){
	int c = PreOrd[pbeg];

	int lcnt = InNumToIdx[c] - ibeg;
	int rcnt = iend - ibeg - lcnt;

	if(lcnt > 0){
		rec_solve(pbeg + 1, pbeg + lcnt, ibeg, ibeg + lcnt - 1);
	}
	if(rcnt > 0){
		rec_solve(pbeg + lcnt + 1, pend, ibeg + lcnt + 1, iend);
	}
	Ans.push_back(c);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		rec_solve(0, N-1, 0, N-1);
		for(auto a:Ans){
			printf("%d ",a);
		}
		printf("\n");
	}
}