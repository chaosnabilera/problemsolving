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

const int NEGINF = -987654321;

int N;
int A[50];
int DP[50][50];
bool Visited[50][50];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%d", &A[i]);
	}
}

int rec_solve(int beg, int end){
	if(Visited[beg][end])
		return DP[beg][end];

	Visited[beg][end] = true;

	if(beg < end){
		int val = A[beg] - rec_solve(beg+1,end);
		val = max(val, A[end] - rec_solve(beg,end-1));
		if(end-beg == 1){
			val = max(val, 0);
		}
		else{
			val = max(val, -rec_solve(beg+2,end));
			val = max(val, -rec_solve(beg,end-2));
		}
		DP[beg][end] = val;
	}
	else if(beg == end){
		DP[beg][end] = A[beg];
	}
	else {
		DP[beg][end] = 0;
	}

	return DP[beg][end];
}

void solve(){
	memset(Visited,0,sizeof(Visited));
	printf("%d\n", rec_solve(0,N-1));
}

int main(int argc, char** argv){
	int c = 0;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}