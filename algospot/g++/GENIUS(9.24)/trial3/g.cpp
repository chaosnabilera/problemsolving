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

int N,K,M;
int L[50];
double T[50][50];
int Q[10];

struct Matrix{
	Matrix(){
		memset(m,0,sizeof(m));
	}
	Matrix(const Matrix& rhs){
		memcpy(m,rhs.m,sizeof(m));
	}
	Matrix operator*(Matrix& rhs){
		Matrix res;
		int n4 = 4*N;
		for(int r=0; r<n4; ++r)
			for(int c=0; c<n4; ++c)
				for(int k=0; k<n4; ++k){
					res.m[r][c] += m[r][k] * rhs.m[k][c];
				}

		return res;
	}
	void clear(){
		memset(m,0,sizeof(m));
	}
	double m[200][200];
};

void print_matrix(Matrix& mat){
	for(int r=0; r<N*4; ++r){
		for(int c=0; c<N*4; ++c){
			printf("%.3f ", mat.m[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}

void get_input(){
	scanf("%d %d %d", &N, &K, &M);

	// memset(L,0,sizeof(L));
	// memset(T,0,sizeof(T));
	// memset(Q,0,sizeof(Q));

	for(int i=0; i<N; ++i)
		scanf("%d", &L[i]);

	// printf("L: ");
	// for(int i=0; i<N; ++i)
	// 	printf("%d ", L[i]);
	// printf("\n");

	for(int r=0; r<N; ++r)
		for(int c=0; c<N; ++c)
			scanf("%lf", &T[r][c]);

	for(int i=0; i<M; ++i)
		scanf("%d", &Q[i]);
}

Matrix construct_base_matrix(){
	Matrix res;

	// printf("%d %d %d\n",N,K,M);

	for(int c=0; c<N; ++c){
		for(int l=0; l<N; ++l){
			int r = ((L[l]-1)*N)+l;
			res.m[r][c] = T[l][c];
		}
	}

	for(int r=0; r<N*3; ++r){
		int c = r+N;
		res.m[r][c] = 1;
	}

	// print_matrix(res);

	return res;
}



void solve(){
	Matrix base[20];
	base[0] = construct_base_matrix();

	// printf("%d %d %d\n",N,K,M);

	int last_i = 0;
	for(int i=1; i<20; ++i){
		base[i] = base[i-1]*base[i-1];
		last_i = i;
	}

	// for(int i=0; i<=last_i; ++i){
	// 	print_matrix(base[i]);
	// }

	bool first = true;
	Matrix res;
	for(int i=19; i>=0; --i){
		if((1<<i) & K){
			if(first){
				res = base[i];
				first = false;
			}
			else{
				res = res*base[i];
			}
		}
	}

	// printf("M(%d): ",M);
	// for(int i=0; i<M; ++i)
	// 	printf("%d ",Q[i]);
	// printf("\n");
	// print_matrix(res);

	for(int i=0; i<M; ++i){
		int q = Q[i];
		double cur = 0;
		for(int l=0; l<L[q]; ++l){
			cur += res.m[0][(l*N)+q];
		}
		printf("%.8lf ",cur);
	}
	printf("\n");
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}