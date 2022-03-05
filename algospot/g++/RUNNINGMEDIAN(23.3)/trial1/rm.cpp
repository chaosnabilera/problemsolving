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

const long long MODNUM = 20090711;

void solve(){
	int N;
	long long A,B;
	priority_queue<long long> L_maxq;
	priority_queue<long long, vector<long long>, greater<long long>> R_minq;
	scanf("%d %lld %lld", &N, &A, &B);

	long long num = 1983;
	long long ans = 0;

	// i = 0
	L_maxq.push(num);
	ans = num;
	num = ((num*A)+B) % MODNUM;

	// iterate
	for(int i=1; i<N; ++i){
		if(num < L_maxq.top())
			L_maxq.push(num);
		else
			R_minq.push(num);

		while(L_maxq.size() > R_minq.size()+1){
			R_minq.push(L_maxq.top());
			L_maxq.pop();
		}
		while(R_minq.size() > L_maxq.size()){
			L_maxq.push(R_minq.top());
			R_minq.pop();
		}

		ans = (ans+L_maxq.top()) % MODNUM;
		num = ((num*A)+B) % MODNUM;
	}
	printf("%lld\n", ans);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		solve();
	}
}