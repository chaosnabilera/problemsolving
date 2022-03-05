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

int K,N;

void solve(){
	deque<long long> psum;
	long long a = 1983;
	long long cur_psum = 0;

	int cnt = 0;
	psum.push_back(0);
	for(int i=0; i<N; ++i){
		long long curnum = (a%10000)+1;
		cur_psum += curnum;

		while(!psum.empty() && cur_psum - psum.front() > K){
			psum.pop_front();
		}

		if(!psum.empty() && cur_psum - psum.front() == K)
			++cnt;

		psum.push_back(cur_psum);

		a = ((a*214013)+2531011) & 0xFFFFFFFF;
	}

	printf("%d\n", cnt);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		scanf("%d %d", &K, &N);
		solve();
	}
}