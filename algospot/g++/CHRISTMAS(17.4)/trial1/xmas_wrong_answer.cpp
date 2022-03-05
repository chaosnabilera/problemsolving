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

const int BIGNUM = 987654321;

long long N,K;
long long D[100000];
long long CumSum[100000];
long long Cnt[100000];
int FirstEnd[100000];

vector<int>* WithMod[100000];

long long gaussian_sum(long long cnt){
	return (cnt*(cnt+1))/2LL;
}

void clear_WithMod(){
	for(int i=0; i<N; ++i){
		if(WithMod[i] != nullptr){
			delete WithMod[i];
			WithMod[i] = nullptr;
		}
	}
}

void append_WithMod(long long mod, int idx){
	if(WithMod[mod] == nullptr){
		WithMod[mod] = new vector<int>();
	}
	WithMod[mod]->push_back(idx);
}

void get_input(){
	scanf("%lld %lld", &N, &K);
	int num;
	for(int i=0; i<N; ++i){
		scanf("%lld", &D[i]);
	}
}

void print_arr(long long* arr, int n){
	for(int i=0; i<n; ++i){
		printf("%4lld ", arr[i]);
	}
	printf("\n");
}

void print_arr(int* arr, int n){
	for(int i=0; i<n; ++i){
		printf("%4d ", arr[i]);
	}
	printf("\n");
}


void solve(){
	CumSum[N-1] = D[N-1];
	for(int i=N-2; i>=0; --i)
		CumSum[i] = D[i] + CumSum[i+1];

	clear_WithMod();
	for(int i=0; i<N; ++i){
		append_WithMod(CumSum[i] % K, i);
	}

	// for(int i=0; i<N; ++i){
	// 	printf("%lld ", CumSum[i]);
	// }
	// printf("\n");
	for(int i=0; i<N; ++i){
		Cnt[i] = -1;
		FirstEnd[i] = -1;
	}

	vector<int> kend;

	for(int i=0; i<N; ++i){
		if(Cnt[i] != -1)
			continue;

		long long base = CumSum[i];
		kend.clear();

		for(int e:*WithMod[base % K]){
			if(e > i)
				kend.push_back(e-1);
		}
		if(base % K == 0)
			kend.push_back(N-1);

		// printf("%d :", i);
		// for(auto p:kend){
		// 	printf("%d ", p);
		// }
		// printf("\n");

		Cnt[i] = kend.size();

		if(Cnt[i] > 0){
			FirstEnd[i] = kend[0];
			for(int j=0; j<kend.size()-1; ++j){
				Cnt[kend[j]+1] = Cnt[i]-j-1;
				FirstEnd[kend[j]+1] = kend[j+1];
			}
		}
	}

	// print_arr(CumSum,N);
	// print_arr(Cnt,N);
	// print_arr(FirstEnd,N);

	long long ans1 = 0;
	int ans2 = 0;
	int curend = -1;

	for(int i=0; i<N; ++i){
		ans1 += Cnt[i];
	}

	for(int i=0; i<N; ++i){
		if(Cnt[i]){
			if(i > curend){
				// printf("%d\n",i);
				++ans2;
				curend = FirstEnd[i];
			}
			else{
				curend = min(curend, FirstEnd[i]);
			}
		}
	}

	printf("%lld %d\n", ans1 % 20091101LL, ans2);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		// printf("input!\n");
		solve();
	}
}