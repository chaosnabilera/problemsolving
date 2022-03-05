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

const int MAXINT = numeric_limits<int>::max();

int N,K;

int iNum[500];

int DP[500][501]; // DP[i][l] : number of increasing sequence with length l start from iNum[i]
int MaxLen;

void get_input(){
	scanf("%d %d", &N, &K);
	for(int i=0; i<N; ++i)
		scanf("%d",&iNum[i]);
}

void print_dp(){
	for(int s=0; s<N; ++s){
		for(int l=0; l<=N; ++l){
			printf("%3d ",DP[s][l]);
		}
		printf("\n");
	}
	printf("\n");
}

void solve_dp(){
	memset(DP,0,sizeof(DP));
	for(int i=0; i<N; ++i)
		DP[i][1] = 1;
	MaxLen = 1;

	for(int l=2; l<=N; ++l){
		bool exists = false;
		int ilim = N-l+1;
		int jlim = ilim+1;
		// printf("l:%d ilim:%d jlim:%d\n",l,ilim,jlim);
		for(int i=0; i<ilim; ++i){
			long long dp_il = 0;

			for(int j=i+1; j<jlim; ++j){
				if((iNum[i] < iNum[j]) && DP[j][l-1]){
					// printf("%d?\n",l);
					exists = true;
					dp_il += DP[j][l-1];

					if(dp_il > MAXINT)
						dp_il = MAXINT;
				}
			}

			DP[i][l] = dp_il;
		}
		// print_dp();
		if(!exists){
			break;
		}
		MaxLen = l;
	}
}

void rec_print(int pch, int s, int l, int k){
	if(l == 0)
		return;

	vector<pair<int,int>> iseq;
	int ilim = N-l+1;

	for(int i=s; i<ilim; ++i){
		if(pch < iNum[i] && DP[i][l]){
			iseq.push_back(make_pair(iNum[i],i));
		}
	}
	sort(iseq.begin(),iseq.end());

	int kk = k;
	for(auto p:iseq){
		int ss = p.second;
		if(DP[ss][l] < kk){
			kk -= DP[ss][l];
		}
		else{
			printf("%d ",iNum[ss]);
			return rec_print(iNum[ss], ss+1, l-1, kk);
		}
	}
}

void solve(){
	solve_dp();
	printf("%d\n",MaxLen);
	rec_print(-1,0,MaxLen,K);
	printf("\n");
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}