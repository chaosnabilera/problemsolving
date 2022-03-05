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

const int MODNUM = 20091101;

int N,K;
vector<int> D;

void get_input(){
	scanf("%d %d", &N, &K);
	D = vector<int>(N,0);
	for(int i=0; i<N; ++i){
		scanf("%d", &D[i]);
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

int waysToBuy(const vector<int>& psum, int k){
	const int MOD = 20091101;
	int ret = 0;
	vector<long long> count(k,0);
	for(int i=0; i<psum.size(); ++i)
		count[psum[i]]++;
	for(int i=0; i<k; ++i)
		if(count[i] >= 2)
			ret = (ret + ((count[i]*(count[i]-1))/2)) % MOD;
	return ret;
}

int maxBuys(const vector<int>& psum, int k){
	vector<int> ret(psum.size(), 0);
	vector<int> prev(k,-1);
	for(int i=0; i<psum.size(); ++i){
		if(i>0)
			ret[i] = ret[i-1];
		else
			ret[i] = 0;

		int loc = prev[psum[i]];
		if(loc != -1)
			ret[i] = max(ret[i], ret[loc]+1);
		prev[psum[i]] = i;
	}

	return ret.back();
}

void solve(){
	vector<long long> psumsum(N+1,0);
	vector<int> psum(N+1,0);
	psumsum[0] = 0;
	for(int i=0; i<N; ++i)
		psumsum[i+1] = D[i] + psumsum[i];
	for(int i=0; i<psumsum.size(); ++i)
		psum[i] = psumsum[i] % K;

	int ans1 = waysToBuy(psum, K);
	int ans2 = maxBuys(psum, K);

	printf("%d %d\n",ans1,ans2);
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