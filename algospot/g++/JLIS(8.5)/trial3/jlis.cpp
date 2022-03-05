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

int DP[101][101];
int N,M;
vector<int> A;
vector<int> B;

void get_input(){
	int v;
	scanf("%d %d", &N, &M);
	A.clear();
	A.reserve(N);
	for(int i=0; i<N; ++i){
		scanf("%d", &v);
		A.push_back(v);
	}

	B.clear();
	B.reserve(M);
	for(int i=0; i<M; ++i){
		scanf("%d", &v);
		B.push_back(v);
	}
}

int rec_solve(int a, int b){
	if(DP[a][b] != -1){
		// printf("%d %d : %d\n",a,b,DP[a][b]);
		return DP[a][b];
	}

	if(a == A.size()){
		// printf("%d %d\n",a,b);
		DP[a][b] = 1;
		for(int nb = b+1; nb <= B.size(); ++nb){
			if(nb < B.size() && B[nb] <= B[b])
				continue;
			// printf("\t%d %d\n",a,nb);
			DP[a][b] = max(DP[a][b],1+rec_solve(a,nb));
		}
		// printf("%d %d %d\n",a,b,DP[a][b]);
	}
	else if(b == B.size()){
		DP[a][b] = 1;
		for(int na = a+1; na <= A.size(); ++na){
			if(na < A.size() && A[na] <= A[a])
				continue;
			DP[a][b] = max(DP[a][b],1+rec_solve(na,b));
		}
	}
	else{
		if(A[a] == B[b]){
			DP[a][b] = 1;

			for(int na = a+1; na <= A.size(); ++na){
				if(na < A.size() && A[na] <= A[a])
					continue;
				for(int nb = b+1; nb <= B.size(); ++nb){
					if(nb < B.size() && B[nb] <= B[b])
						continue;
					DP[a][b] = max(DP[a][b], 1+rec_solve(na,nb));
				}
			}
		}
		else{
			DP[a][b] = 2;
			if(A[a] < B[b]){
				for(int na = a+1; na <= A.size(); ++na){
					if(na < A.size() && A[na] <= A[a])
						continue;
					DP[a][b] = max(DP[a][b], 1+rec_solve(na,b));
				}
			}
			else{
				for(int nb = b+1; nb <= B.size(); ++nb){
					if(nb < B.size() && B[nb] <= B[b])
						continue;
					DP[a][b] = max(DP[a][b], 1+rec_solve(a,nb));
				}
			}
		}
	}

	// printf("%d %d %d\n",a,b,DP[a][b]);
	return DP[a][b];
}

void precompute_dp(){
	DP[A.size()][B.size()] = 0;
	DP[A.size()-1][B.size()] = 1;
	DP[A.size()][B.size()-1] = 1;
	DP[A.size()-1][B.size()-1] = (A[A.size()-1] == B[B.size()-1]) ? 1 : 2;
}

void print_dp(){
	for(int a=0; a<=A.size(); ++a){
		for(int b=0; b<=B.size(); ++b){
			printf("%3d",DP[a][b]);
		}
		printf("\n");
	}
	printf("\n");
}

void solve(){
	memset(DP,0xFF,sizeof(DP));
	precompute_dp();

	int maxlen = 0;
	for(int a=0; a<A.size(); ++a)
		for(int b=0; b<B.size(); ++b)
			maxlen = max(maxlen,rec_solve(a,b));

	// print_dp();

	printf("%d\n",maxlen);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}