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
#include <cmath>

using namespace std;

int K,N;

void solve(){
	deque<long long> dq;
	long long dqsum = 0LL;

	long long a = 1983;
	int cnt = 0;

	for(int i=0; i<N; ++i){
		long long v = (a % 10000) + 1;

		dq.push_back(v);
		dqsum += v;

		while(dqsum >= K){
			if(dqsum == K)
				++cnt;
			dqsum -= dq.front();
			dq.pop_front();
		}

		a = ((a*214013) + 2531011) & 0xFFFFFFFF;
	}

	printf("%d\n", cnt);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		scanf("%d%d", &K, &N);
		solve();
	}
}