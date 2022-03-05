#include <iostream>
#include <vector>

using namespace std;

int N, P, L;

unsigned long long CntXY[51];
unsigned long long CntConst[51];

void precompute(){
	CntXY[0] = 1;
	CntConst[0] = 1;

	for(int g=1; g<=50; ++g){
		CntXY[g] = 2*CntXY[g-1];
		CntConst[g] = CntConst[g-1] + 2*CntXY[g-1];
	}
}

void rec_solve(unsigned long long beg, unsigned long long end, char mode, int lv, long long pos){
	// printf("%llu %llu\n",beg,end);
	long long mid = (beg+end) >> 1;

	if(pos == beg || pos == end){
		printf("F");
	}
	else if(pos == mid){
		if(mode == 'x')
			printf("+");
		else
			printf("-");
	}
	else if(pos < mid){
		if(lv == N)
			printf("X");
		else
			rec_solve(beg,mid-1,'x',lv+1,pos);
	}
	else{
		if(lv ==N)
			printf("Y");
		else
			rec_solve(mid+1,end,'y',lv+1,pos);
	}
}

void solve(){
	if(N == 0){
		for(int x=P; x<P+L; ++x){
			// printf("x:%d\n",x);
			if(x == 0)
				printf("F");
			else
				printf("X");
		}
	}
	else{
		unsigned long long gend = CntXY[N]+CntConst[N]-1;
		for(int x=P; x<P+L; ++x){
			rec_solve(0,gend,'x',1,x);
		}
	}
	printf("\n");
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	precompute();
	for(int i=0; i<c; ++i){
		scanf("%d %d %d", &N, &P, &L);
		--P;
		solve();
	}
} 