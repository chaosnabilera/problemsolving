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

int N;
int A[100];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i)
		scanf("%d", &A[i]);
}

void solve(){
	priority_queue<int,vector<int>,greater<int>> minq;
	for(int i=0; i<N; ++i)
		minq.push(A[i]);

	int ans = 0;
	while(minq.size() > 1){
		int a = minq.top(); minq.pop();
		int b = minq.top(); minq.pop();

		// printf("%d %d\n",a,b);

		int ab = a+b;
		ans += ab;
		minq.push(ab);
	}

	printf("%d\n",ans);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}