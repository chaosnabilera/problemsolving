#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

const int MODNUM = 20090711;

void solve(){
	int N,a,b;
	long long A = 1983;

	priority_queue<int> low_maxq;
	priority_queue<int, vector<int>, greater<int>> high_minq;

	scanf("%d%d%d", &N, &a, &b);

	low_maxq.push(A);
	int cum = A;

	for(int i=1; i<N; ++i){
		A = (A*a+b) % MODNUM;

		if(A > low_maxq.top())
			high_minq.push(A);
		else
			low_maxq.push(A);

		if(low_maxq.size() > high_minq.size()+1){
			high_minq.push(low_maxq.top());
			low_maxq.pop();
		}

		if(high_minq.size() > low_maxq.size()){
			low_maxq.push(high_minq.top());
			high_minq.pop();
		}

		cum = (cum + low_maxq.top()) % MODNUM;
	}

	printf("%d\n", cum);

}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		solve();
	}
}