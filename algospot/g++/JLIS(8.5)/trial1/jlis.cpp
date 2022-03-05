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

int N, M;
long long A[101];
long long B[101];

long long JLIS[101][101];

void print_jlis(){
	for(int a=0; a<=N; ++a){
		for(int b=0; b<=M; ++b){
			printf("%lld ", JLIS[a][b]);
		}
		printf("\n");
	}
	printf("\n");
}

long long rec_jlis(int a, int b){
	// printf("A[%d]:%lld B[%d]:%lld JLIS[%d][%d]:%lld\n",a,A[a],b,B[b],a,b,JLIS[a][b]);
	if(JLIS[a][b] != -1)
		return JLIS[a][b];

	long long jlis = 1;

	if(A[a] < B[b]){
		for(int aa=a+1; aa<=N; ++aa)
			if(A[a] < A[aa])
				jlis = max(jlis, 1+rec_jlis(aa,b));
		// for(int bb=b; bb<M; ++bb)
		// 	if(A[a] < B[bb])
		// 		jlis = max(jlis, 1+rec_jlis(a+1,bb));
	}
	else if(B[b] < A[a]){
		// for(int aa=a; aa<N; ++aa)
		// 	if(B[b] < A[aa])
		// 		jlis = max(jlis, 1+rec_jlis(aa,b+1));
		for(int bb=b+1; bb<=M; ++bb)
			if(B[b] < B[bb])
				jlis = max(jlis, 1+rec_jlis(a,bb));
	}
	else{
		int fa = N;
		int fb = M;
		for(int aa=a+1; aa<N; ++aa)
			if(A[a] < A[aa]){
				fa = aa;
				break;
			}
		for(int bb=b+1; bb<M; ++bb)
			if(B[b] < B[bb]){
				fb = bb;
				break;
			}

		for(int aa=a+1; aa<N; ++aa)
			if(A[a] < A[aa])
				jlis = max(jlis, 1+rec_jlis(aa,fb));
		for(int bb=b+1; bb<M; ++bb)
			if(B[b] < B[bb])
				jlis = max(jlis, 1+rec_jlis(fa,bb));
	}

	JLIS[a][b] = jlis;
	// printf("\tA[%d]:%lld B[%d]:%lld JLIS[%d][%d]:%lld\n",a,A[a],b,B[b],a,b,JLIS[a][b]);

	return JLIS[a][b];
}

void solve(){
	long long maxjlis = 0;

	A[N] = numeric_limits<long long>::max();
	B[M] = numeric_limits<long long>::max();

	for(int i=0; i<=N; ++i)
		for(int j=0; j<=M; ++j)
			JLIS[i][j] = -1;

	//base case
	JLIS[N][M] = 0;

	//calculate in reverse order
	for(int a=N; a >= 0; --a)
		for(int b=M; b >= 0; --b)
			if(JLIS[a][b] == -1)
				rec_jlis(a,b);

	// print_jlis();

	for(int i=0; i<N; ++i)
		for(int j=0; j<M; ++j)
			maxjlis = max(maxjlis, JLIS[i][j]);

	printf("%lld\n", maxjlis);
}

int main(int argc, char** argv){
	int C,a,b;
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d %d", &N, &M);
		for(int j=0; j<N; ++j){
			scanf("%lld", &A[j]);
		}
		for(int j=0; j<M; ++j){
			scanf("%lld", &B[j]);
		}
		solve();
	}
}