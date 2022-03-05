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

int N,K,M;
int iLen[50];
double P[50][50];
int Q[10];

struct SqMat{
	SqMat(int _n=0) : n(_n) { memset(m,0,sizeof(m)); }

	SqMat operator*(SqMat& rhs){
		SqMat res(n);
		for(int r=0; r<n; ++r){
			for(int c=0; c<n; ++c){
				for(int i=0; i<n; ++i){
					res.m[r][c] += m[r][i] * rhs.m[i][c];
				}
			}
		}
		return res;
	}

	void print(){
		for(int r=0; r<n; ++r){
			for(int c=0; c<n; ++c){
				printf("%.5lf ", m[r][c]);
			}
			printf("\n");
		}
	}
	int n;
	double m[200][200];
};

void get_input(){
	scanf("%d %d %d",&N,&K,&M);
	for(int i=0; i<N; ++i)
		scanf("%d", &iLen[i]);

	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j)
			scanf("%lf", &P[i][j]);

	for(int i=0; i<M; ++i)
		scanf("%d", &Q[i]);
}



void solve(){
	SqMat imat(4*N);
	SqMat powmat[20];
	SqMat res;
	bool init_acquired = false;

	// make matrix
	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j){
			// printf("%d:%d %d\n",j,iLen[j],iLen[j]-1 * N);
			imat.m[((iLen[j]-1)*N) + j][i] = P[j][i];
		}
	for(int i=0; i<(3*N); ++i)
		imat.m[i][N+i] = 1.0;

	// make power matrix
	powmat[0] = imat;
	for(int i=1; K >= (1<<i); ++i){
		powmat[i] = powmat[i-1]*powmat[i-1];
	}

	for(int i=19; i >= 0; --i){
		if(!(K & (1<<i)))
			continue;
		if(!init_acquired){
			res = powmat[i];
			init_acquired = true;
		}
		else{
			res = res*powmat[i];
		}
	}

	// imat.print();

	for(int i=0; i<M; ++i){
		double qsum = 0;
		for(int j=0; j<iLen[Q[i]]; ++j)
			qsum += res.m[0][(j*N)+Q[i]];
		printf("%.8lf ", qsum);
	}
	printf("\n");
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}