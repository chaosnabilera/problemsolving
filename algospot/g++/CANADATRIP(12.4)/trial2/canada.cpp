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

long long N, K;
long long L[5000];
long long M[5000];
long long G[5000];

void get_input(){
	scanf("%lld %lld", &N, &K);
	for(int i=0; i<N; ++i)
		scanf("%lld %lld %lld", &L[i], &M[i], &G[i]);
}

void count_signs(long long q, long long& before, long long& exact){
	before = 0;
	exact = 0;
	// printf("\n%lld\n",q);

	for(int i=0; i<N; ++i){
		// printf("L[%d]:%lld M[%d]:%lld G[%d]:%lld\n", i, L[i], i, M[i], i, G[i]);

		if(L[i] < q){
			before += (M[i]/G[i])+1;
			// printf("1before += %lld\n", (M[i]/G[i])+1);
		}
		else if(L[i] == q){
			before += M[i]/G[i];
			exact++;
			// printf("2before += %lld\n", M[i]/G[i]);
			// printf("2exact++\n");
		}
		else{
			long long sign_start = L[i]-M[i];
			if(sign_start <= q){
				before += (q-sign_start)/G[i];
				// printf("3before += %lld\n", (q-sign_start)/G[i]);
				// printf("%lld\n", (q-sign_start) % G[i]);
				if((q-sign_start) % G[i] == 0LL){
					exact++;
					// printf("3exact++");
				}
				else
					before++;
			}
			else{
				// printf("4None\n");
			}
		}
	}
}

void solve(){
	long long left = 0;
	long long right= 8030000;
	long long before;
	long long exact;

	while(true){
		long long mid = (left+right) >> 1;
		count_signs(mid, before, exact);

		if(before+exact < K){
			left = mid;
		}
		else if(before >= K){
			right = mid;
		}
		else{
			// printf("%lld %lld\n", before, exact);
			printf("%lld\n",mid);
			break;
		}
	}
}

int main(int argc, char** argv){
	int t;
	scanf("%d", &t);
	for(int i=0; i<t; ++i){
		get_input();
		solve();
	}
}