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

const int INF = 987654321;

int N,K,M,L;

int Prereq[12];
int Sem[12];

int DP[12][(1<<12)];

int BitCnt[(1<<12)];
vector<int> BitSubset[(1<<12)][11];
bool BitSubsetVisited[(1<<12)][11];

void rec_precompute(int bitset, int cnt){
	// printf("%d %d\n",bitset, cnt);
	if(BitSubsetVisited[bitset][cnt])
		return;

	BitSubsetVisited[bitset][cnt] = true;

	// trivial cases
	if(BitCnt[bitset] < cnt)
		return;
	if(BitCnt[bitset] == cnt){
		BitSubset[bitset][cnt].push_back(bitset);
		return;
	}

	if(cnt == 1){
		for(int b=0; b<12; ++b){
			if(bitset & (1<<b))
				BitSubset[bitset][cnt].push_back(1<<b);
		}
	}
	else{
		int subset = bitset;
		for(int b=0; b<12; ++b){
			if(subset & (1<<b)){
				subset ^= (1<<b);
				rec_precompute(subset, cnt-1);
				for(int ss:BitSubset[subset][cnt-1]){
					BitSubset[bitset][cnt].push_back(ss | (1<<b));
				}
			}
		}
	}
}

void precompute(){
	for(int i=0; i<(1<<12); ++i){
		BitCnt[i] = 0;
		for(int b=0; b<12; ++b){
			if(i & (1<<b))
				BitCnt[i]++;
		}
	}

	for(int i=0; i<(1<<12); ++i)
		for(int j=1; j<=10; ++j)
			BitSubset[i][j].clear();

	memset(BitSubsetVisited,0,sizeof(BitSubsetVisited));

	for(int i=0; i<(1<<12); ++i)
		for(int j=1; j<=10; ++j)
			rec_precompute(i,j);
}



void get_input(){
	int r,c,v;

	memset(Prereq,0,sizeof(Prereq));
	memset(Sem,0,sizeof(Sem));
	scanf("%d%d%d%d",&N,&K,&M,&L);
	for(int i=0; i<N; ++i){
		scanf("%d", &r);
		for(int j=0; j<r; ++j){
			scanf("%d", &v);
			Prereq[i] |= (1<<v);
		}
	}
	for(int i=0; i<M; ++i){
		scanf("%d", &c);
		for(int j=0; j<c; ++j){
			scanf("%d", &v);
			Sem[i] |= (1<<v);
		}
	}
}

int rec_solve(int si, int taken){
	if(BitCnt[taken] >= K)
		return 0;
	if(si >= N)
		return INF;
	if(DP[si][taken] != -1)
		return DP[si][taken];

	int res = rec_solve(si+1,taken);

	int may_take = 0;
	for(int s=0; s<12; ++s){
		int sb = 1<<s;
		if((sb & Sem[si]) && (!(sb & taken)) && ((Prereq[s] & taken) == Prereq[s])){
			may_take |= sb;
		}
	}

	int max_take_cnt = min(L,BitCnt[may_take]);

	for(int take:BitSubset[may_take][max_take_cnt]){
		res = min(res, 1+rec_solve(si+1, taken ^ take));
	}

	return min(INF,res);
}

void solve(){
	memset(DP,0xFF,sizeof(DP));
	int res = rec_solve(0,0);

	if(res < INF){
		printf("%d\n",res);
	}
	else{
		printf("IMPOSSIBLE\n");
	}
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	precompute();
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
	return 0;
}