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

int C;
int N,L;
unsigned long long P;

unsigned long long GenLen[51];

char str_X[] = "FX+YF";
char str_Y[] = "FX-YF";

void gen0(){
	char gen0_str[] = "FX";
	for(int i=0; i<L; ++i){
		printf("%c",gen0_str[P-1+i]);
	}
	printf("\n");
}

void rec_solve(unsigned long long i, int gen, bool sign, unsigned long long beg, unsigned long long end){
	unsigned long long mid;

	if(i == beg || i == end){
		printf("F");
		return;
	}

	mid = (beg+end) >> 1;
	if(i == mid){
		if(sign)
			printf("+");
		else
			printf("-");
		return;
	}

	if(gen == N){
		if(sign)
			printf("%c", str_X[i-beg]);
		else
			printf("%c", str_Y[i-beg]);
	}
	else{
		if(i<mid)
			rec_solve(i, gen+1, true, beg, mid-1);
		else
			rec_solve(i, gen+1, false, mid+1, end);
	}
}

void solve(){
	for(unsigned long long i=P; i<P+L; ++i){
		rec_solve(i,1,true,1,GenLen[N]);
	}
	printf("\n");
}

void precompute_genlen(){
	unsigned long long next_fconst, next_fxy;
	unsigned long long fconst = 1;
	unsigned long long fxy = 1;

	GenLen[0] = 2;

	for(int i=1; i<=50; ++i){
		fconst = fconst + (fxy << 1);
		fxy = fxy << 1;
		GenLen[i] = fconst+fxy;
	}
}

int main(int argc, char** argv){
	precompute_genlen();

	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d %lld %d", &N, &P, &L);
		if(N == 0)
			gen0();
		else
			solve();
	}
}