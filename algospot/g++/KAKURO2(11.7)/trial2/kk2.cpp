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

using namespace std;

int N,Q;
int IsBlank[20][20];
int hR[400];
int hC[400];
int hD[400];
int hSum[400];
int HintNo[20][20][2];
int HintStat[400];
int HintCnt[400];

int BitCount[(1<<10)];
int MaskToSum[(1<<10)];
// [x][n][bm] : Candidates for blank where we need make sum x and there are n space left and elements in bm are already taken
int SumToMask[46][10][(1<<10)];
int Board[20][20];

string bit10(int b10){
	string res;
	for(int i=9; i>=0; --i){
		if(b10&(1<<i))
			res += "1";
		else
			res += "0";
	}
	return res;
}

void precompute(){
	int lim = 1<<10;

	// compute MaskToSum, BitCount
	for(int bm = 0; bm < lim; bm += 2){
		int bsum = 0;
		int bitcnt = 0;

		for(int i=1; i<=9; ++i)
			if(bm & (1<<i)){
				bsum += i;
				bitcnt++;
			}
		BitCount[bm] = bitcnt;
		MaskToSum[bm] = bsum;
	}

	for(int bm = 0; bm < lim; bm += 2){
		int fullset = bm;
		int subset = (fullset - 1) & fullset;

		int fullsum = MaskToSum[fullset];
		int fullcnt = BitCount[fullset];

		SumToMask[fullsum][fullcnt][0] |= fullset;
		while(subset){
			int subsum = MaskToSum[subset];
			int subcnt = BitCount[subset];

			SumToMask[fullsum][fullcnt-subcnt][subset] |= ((fullset ^ subset) & SumToMask[fullsum-subsum][fullcnt-subcnt][0]);

			// if(fullsum == 30){
			// 	printf("SumToMask[%d][%d][%s] = %s\n",fullsum,fullcnt-subcnt,bit10(subset).c_str(),bit10(SumToMask[fullsum][fullcnt-subcnt][subset]).c_str());
			// }
			subset = (subset-1) & fullset;
		}
	}


}

void get_input(){
	scanf("%d", &N);
	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			scanf("%d", &IsBlank[r][c]);
			HintNo[r][c][0] = -1;
			HintNo[r][c][1] = -1;
		}
	}
	scanf("%d", &Q);
	for(int i=0; i<Q; ++i){
		scanf("%d %d %d %d", &hR[i], &hC[i], &hD[i], &hSum[i]);
		hR[i]--;
		hC[i]--;
		HintStat[i] = 0;
		HintCnt[i] = 0;
	}
}

int get_candidate(int r, int c){
	int h0i = HintNo[r][c][0];
	int h1i = HintNo[r][c][1];

	int h0mask = SumToMask[hSum[h0i]][HintCnt[h0i]][HintStat[h0i]];
	int h1mask = SumToMask[hSum[h1i]][HintCnt[h1i]][HintStat[h1i]];

	// printf("r:%d c:%d h0:%d h1:%d\n",r,c,h0i,h1i);
	// printf("SumToMask[%d][%d][%s]:%s SumToMask[%d][%d][%s]:%s\n",
	// 	hSum[h0i],HintCnt[h0i],bit10(HintStat[h0i]).c_str(),bit10(h0mask).c_str(),
	// 	hSum[h1i],HintCnt[h1i],bit10(HintStat[h1i]).c_str(),bit10(h1mask).c_str());

	return (h0mask & h1mask);
}

bool rec_solve() {
	int cand, bc;
	int mr, mc, mcand;
	int min_bc = 99;
	for(int r=1; r<N; ++r){
		for(int c=1; c<N; ++c){
			if(IsBlank[r][c]){
				cand = get_candidate(r,c);
				bc = BitCount[cand];
				if(bc < min_bc){
					mr = r;
					mc = c;
					mcand = cand;
					min_bc = bc;
				}
			}
		}
	}

	int h0i = HintNo[mr][mc][0];
	int h1i = HintNo[mr][mc][1];

	// printf("\nmr:%d mc:%d h0i:%d h1i:%d mcand:%s\n\n",mr,mc,h0i,h1i,bit10(mcand).c_str());

	if(min_bc == 99){
		return true;
	}

	

	for(int b=1; b<=9; ++b){
		int bm = 1<<b;
		if(!(bm & mcand))
			continue;

		HintStat[h0i] |= bm;
		HintCnt[h0i]--;
		HintStat[h1i] |= bm;
		HintCnt[h1i]--;

		// printf("HintCnt[%d]:%d HintCnt:[%d]:%d\n",h0i,HintCnt[h0i],h1i,HintCnt[h1i]);

		IsBlank[mr][mc] = false;
		Board[mr][mc] = b;

		// printf("b:%d\n",b);

		if(rec_solve())
			return true;

		Board[mr][mc] = 0;
		IsBlank[mr][mc] = true;

		HintStat[h0i] ^= bm;
		HintCnt[h0i]++;
		HintStat[h1i] ^= bm;
		HintCnt[h1i]++;
	}

	return false;
}

void solve(){
	// assign hints
	for(int i=0; i<Q; ++i){
		if(hD[i] == 0){ // horizontal
			int c = hC[i]+1;
			while(c < N && IsBlank[hR[i]][c]){
				HintNo[hR[i]][c++][0] = i;
				HintCnt[i]++;
			}
		}
		else{ // vertical
			int r = hR[i]+1;
			while(r < N && IsBlank[r][hC[i]]){
				HintNo[r++][hC[i]][1] = i;
				HintCnt[i]++;
			}
		}
	}

	// for(int r=0; r<N; ++r){
	// 	for(int c=0; c<N; ++c)
	// 		printf("%3d ",HintNo[r][c][0]);
	// 	printf("\n");
	// }
	// printf("\n");
	// for(int r=0; r<N; ++r){
	// 	for(int c=0; c<N; ++c)
	// 		printf("%3d ",HintNo[r][c][1]);
	// 	printf("\n");
	// }
	// printf("\n");

	memset(Board,0,sizeof(Board));

	rec_solve();

	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			printf("%d ", Board[r][c]);
		}
		printf("\n");
	}
}

int main(int argc, char** argv){
	int T;
	precompute();

	// for(int i=0; i<(1<<10); i+=2){
	// 	if(SumToMask[7][i]){
	// 		printf("%s %s\n",bit10(i).c_str(), bit10(SumToMask[7][i]).c_str());
	// 	}
	// }
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}