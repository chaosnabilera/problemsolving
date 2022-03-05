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

int MaskToSum[1<<10];
int MaskToBitCnt[1<<10];
int SumToMask[46][10];   // SumToMask[s][c] = Return candidates that can add up to s using c numbers
int Candidate[1<<10][45][10];

int N, Q;
char Board[20][20];

int Hhint[20][20];
int Vhint[20][20];

int HintSum[400];
int HintState[400];
int HintSize[400];

int Answer[20][20];

void precompute(){
	int mlim = 1<<10;

	memset(MaskToSum,0,sizeof(MaskToSum));
	memset(MaskToBitCnt,0,sizeof(MaskToBitCnt));
	memset(SumToMask,0,sizeof(SumToMask));
	memset(Candidate,0,sizeof(Candidate));

	for(int m=0; m<mlim; m+=2){
		for(int b=1; b<10; ++b){
			if(m & (1<<b)){
				MaskToSum[m] += b;
				MaskToBitCnt[m]++;
			}
		}
		SumToMask[MaskToSum[m]][MaskToBitCnt[m]] |= m;
	}

	for(int m=0; m<mlim; m+=2){
		int sum_m = MaskToSum[m];
		int bitcnt_m = MaskToBitCnt[m];
		for(int cm = (m & (m-1)); cm > 0; cm = (m & (cm-1))){
			Candidate[cm][sum_m][bitcnt_m-MaskToBitCnt[cm]] |= (m ^ cm);
		}
		Candidate[0][sum_m][bitcnt_m] |= m;
	}
}

int get_candidate(int r, int c){
	int hh = Hhint[r][c];
	int hhsum = HintSum[hh];
	int hhstate = HintState[hh];

	int vh = Vhint[r][c];
	int vhsum = HintSum[vh];
	int vhstate = HintState[vh];

	int cand_h = Candidate[hhstate][hhsum][HintSize[hh]-MaskToBitCnt[hhstate]];
	int cand_v = Candidate[vhstate][vhsum][HintSize[vh]-MaskToBitCnt[vhstate]];

	// if(r == 1 && c == 2){
	// 	printf("Candidate[%d][%d][%d] : %d   Candidate[%d][%d][%d]: %d\n",
	// 		hhstate, hhsum, HintSize[hh]-MaskToBitCnt[hhstate], cand_h, 
	// 		vhstate, vhsum, HintSize[vh]-MaskToBitCnt[vhstate], cand_v);
	// }

	return (cand_h & cand_v);
}

void set_candidate(int r, int c, int i){
	int hh = Hhint[r][c];
	int vh = Vhint[r][c];

	HintState[hh] |= (1<<i);
	HintState[vh] |= (1<<i);
	Answer[r][c] = i;
}

void unset_candidate(int r, int c, int i){
	int hh = Hhint[r][c];
	int vh = Vhint[r][c];

	HintState[hh] &= ~(1<<i);
	HintState[vh] &= ~(1<<i);
	Answer[r][c] = 0;	
}

void get_input(){
	int v, y, x, d, s;

	memset(Board,0,sizeof(Board));
	memset(Hhint,0xFF,sizeof(Hhint));
	memset(Vhint,0xFF,sizeof(Vhint));
	memset(HintSum,0,sizeof(HintSum));
	memset(HintState,0,sizeof(HintState));
	memset(HintSize,0,sizeof(HintSize));
	memset(Answer,0,sizeof(Answer));

	scanf("%d", &N);
	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			scanf("%d", &v);
			Board[r][c] = v;
		}
	}

	scanf("%d", &Q);
	for(int i=0; i<Q; ++i){
		scanf("%d %d %d %d", &y, &x, &d, &s);
		--y; --x;
		HintSum[i] = s;
		if(d == 0){
			for(int c=x+1; c<N && Board[y][c]; ++c){
				Hhint[y][c] = i;
				HintSize[i]++;
			}
		}
		else{
			for(int r=y+1; y<N && Board[r][x]; ++r){
				Vhint[r][x] = i;
				HintSize[i]++;
			}
		}
	}
}

void print_states(){
	printf("horizontal\n");
	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			printf("%3d", Hhint[r][c]);
		}
		printf("\n");
	}
	printf("\n");

	printf("vertical\n");
	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			printf("%3d", Vhint[r][c]);
		}
		printf("\n");
	}
	printf("\n");

	printf("size:\n");
	for(int i=0; i<Q; ++i){
		printf("%d: %d\n", i, HintSize[i]);
	}
}

void print_answer(){
	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			printf("%d ", Answer[r][c]);
		}
		printf("\n");
	}
}

bool rec_solve(){
	int minr = -1;
	int minc = -1;
	int mincnt = INF;
	int mincand = -1;

	// print_answer();
	// printf("\n");

	for(int r=0; r<N; ++r){
		for(int c=0; c<N; ++c){
			if(Board[r][c] == 1 && Answer[r][c] == 0){
				int curcand = get_candidate(r,c);
				int curcand_bitcnt = MaskToBitCnt[curcand];
				// printf("%d %d %d\n",r,c,curcand_bitcnt);
				if(curcand_bitcnt < mincnt){
					minr = r;
					minc = c;
					mincnt = curcand_bitcnt;
					mincand = curcand;
				}
			}
		}
	}

	// printf("mincnt: %d\n", mincnt);

	if(mincnt == INF){
		// printf("found\n");
		print_answer();
		return true;
	}

	for(int b=1; b<10; ++b){
		if(mincand & (1<<b)){
			set_candidate(minr,minc,b);
			if(rec_solve())
				return true;
			unset_candidate(minr,minc,b);
		}
	}

	// this should not happen!
	return false;
}

// void solve(){
// 	print_states();
// }

int main(int argc, char** argv){
	int t;

	precompute();
	scanf("%d", &t);
	for(int i=0; i<t; ++i){
		get_input();
		// print_states();
		rec_solve();
	}
}