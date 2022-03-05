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

int N, K;
int L[5000];
int M[5000];
int G[5000];
int MaxL;

void get_input(){
	scanf("%d %d", &N, &K);
	MaxL = 0;
	for(int i=0; i<N; ++i){
		scanf("%d %d %d",&L[i],&M[i],&G[i]);
		MaxL = max(MaxL,L[i]);
	}
}

void solve(){
	int ll = 0;
	int rr = MaxL;
	int mm;
	int before, spot, range;

	while(ll < rr){
		mm = (ll+rr) >> 1;
		before = 0;
		spot = 0;

		for(int i=0; i<N; ++i){
			if(L[i] < mm){
				before += (M[i]/G[i])+1;
			}
			else if(L[i]-M[i] <= mm){
				range = mm-(L[i]-M[i]);
				if(range % G[i] == 0){
					before += (range/G[i]);
					spot += 1;
				}
				else{
					before += (range/G[i])+1;
				}
			}
		}

		if(before+spot < K){
			ll = mm+1;
		}
		else if(before >= K){
			rr = mm-1;
		}
		else{
			break;
		}
	}

	printf("%d\n",(ll+rr)>>1);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}