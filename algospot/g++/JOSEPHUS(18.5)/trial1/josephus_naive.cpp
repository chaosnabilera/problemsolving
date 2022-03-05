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

int N,K;

void rec_solve(int n, vector<int> nums){
	if(n == 1)
		return;

	printf("%d: ", n);
	for(int num:nums)
		printf("%d ", num);
	printf("\n");

	vector<int> next;
	int kpos = 1 + ((K-1) % (n-1));
	for(int i=kpos; i<nums.size(); ++i)
		next.push_back(nums[i]);
	for(int i=1; i<kpos; ++i)
		next.push_back(nums[i]);

	rec_solve(n-1, next);
}

void solve(){
	scanf("%d %d", &N, &K);
	vector<int> nums;
	for(int i=1; i<=N; ++i)
		nums.push_back(i);
	rec_solve(nums.size(),nums);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		solve();
	}
}