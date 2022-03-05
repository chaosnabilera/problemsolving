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

int C, N;
int iLen[100];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%d", &iLen[i]);
	}
}

void solve(){
	std::priority_queue<int, std::vector<int>, std::greater<int>> minq;
	for(int i=0; i<N; ++i)
		minq.push(iLen[i]);

	int sum = 0;
	while(minq.size() >= 2){
		int a = minq.top(); minq.pop();
		int b = minq.top(); minq.pop();
		sum += (a+b);
		minq.push(a+b);
	}

	printf("%d\n", sum);
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		solve();
	}
}