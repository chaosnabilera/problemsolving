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

const int INF = 987654321;

int N, S;
int A[100];
int PSum[100];
int DP[11][100];
int DiffSum[100][100];

void get_input(){
	scanf("%d %d", &N, &S);
	for(int i=0; i<N; ++i)
		scanf("%d", &A[i]);

	sort(&A[0],&A[N]);

	PSum[0] = A[0];
	for(int i=1; i<N; ++i)
		PSum[i] = PSum[i-1]+A[i];
}

int get_psum(int beg, int end){
	if(beg == 0)
		return PSum[end];
	else
		return PSum[end] - PSum[beg-1];
}

void calculate_diffsum(){
	for(int beg=0; beg<N; ++beg){
		for(int end=beg; end<N; ++end){
			int psum = get_psum(beg,end);
			int avg1 = psum / (end-beg+1);
			int avg2 = avg1+1;
			
			int diffsum1 = 0;
			int diffsum2 = 0;

			for(int i=beg; i<=end; ++i){
				int x1 = avg1-A[i];
				int x2 = avg2-A[i];
				diffsum1 += x1*x1;
				diffsum2 += x2*x2;
			}

			DiffSum[beg][end] = min(diffsum1,diffsum2);
		}
	}
}

void solve(){
	calculate_diffsum();

	// base case
	for(int beg=0; beg<N; ++beg){
		DP[1][beg] = DiffSum[beg][N-1];
	}

	// the rest
	for(int left = 2; left <= S; ++left){
		for(int beg=0; beg < N; ++beg){
			DP[left][beg] = DP[left-1][beg];
			for(int mid=beg; mid < N; ++mid){
				if(mid == N-1)
					DP[left][beg] = min(DP[left][beg], DiffSum[beg][mid]);
				else
					DP[left][beg] = min(DP[left][beg], DiffSum[beg][mid] + DP[left-1][mid+1]);
			}
		}
	}

	printf("%d\n", DP[S][0]);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}