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

long long MAXVAL = 0x100000000;

int N;
long long K;
int A[500];

long long LISCnt[501][500]; // LISCnt[l][x] : Number of LIS starting from x
int LISLen;

void get_input(){
	scanf("%d",   &N);
	scanf("%lld", &K);
	for(int i=0; i<N; ++i){
		scanf("%d", &A[i]);
	}
	// printf("%d %lld\n",N,K);
}

void rec_print(int s, int v, int l, long long k){
	// printf("<%d %d %lld>\n",s,l,k);
	if(l == 0){
		printf("\n");
		return;
	}

	vector<pair<int,int>> cand;
	for(int i=s; i<N; ++i){
		if(A[i] > v && LISCnt[l][i] > 0)
			cand.push_back(make_pair(A[i],i));
	}
	
	sort(cand.begin(),cand.end());
	for(pair<int,int>& p: cand){
		// printf("(%d %d %lld)\n",p.first,p.second,k);
		int i = p.second;
		if(LISCnt[l][i] < k){
			k -= LISCnt[l][i];
		}
		else{
			printf("%d ", A[i]);
			rec_print(i+1, A[i], l-1, k);
			break;
		}
	}
}

void print_liscnt(){
	for(int l=0; l<=N; ++l){
		for(int i=0; i<N; ++i){
			if(LISCnt[l][i] > 0xFFFF)
				printf(" INF");
			else
				printf("%4lld",LISCnt[l][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void solve(){
	int jlim;
	LISLen = 1;

	memset(LISCnt,0,sizeof(LISCnt));

	for(int i=0; i<N; ++i)
		LISCnt[1][i] = 1;

	for(int l=2; l<=N; ++l){
		bool found = false;
		LISLen = l;
		for(int i=N-l; i >= 0; --i){
			LISCnt[l][i] = 0;
			jlim = N-l+2;
			for(int j=i+1; j<jlim; ++j){
				if(A[i] < A[j] && LISCnt[l-1][j] > 0){
					found = true;
					LISCnt[l][i] += LISCnt[l-1][j];
					LISCnt[l][i] = min(LISCnt[l][i], MAXVAL);
				}
			}
		}
		if(!found){
			LISLen--;
			break;
		}
	}

	// print_liscnt();
	printf("%d\n",LISLen);
	rec_print(0, 0, LISLen, K);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}