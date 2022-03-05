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
#include <cmath>

using namespace std;

template <typename T>
class SquareMatrix{
public:
	SquareMatrix<T>(const int n) : N(n){
		allocate();
	}

	SquareMatrix<T>(const int n, T** imat) : N(n){
		allocate();
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				matrix[i][j] = imat[i][j];
	}

	SquareMatrix<T>(const SquareMatrix<T>& rhs) : N(rhs.size()){
		allocate();
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				matrix[i][j] = rhs[i][j];
	}

	SquareMatrix<T>(const SquareMatrix<T>&& rhs) : N(rhs.size()){
		matrix = rhs.matrix;
		N = rhs.N;
	}

	~SquareMatrix<T>(){
		deallocate();
	}

	int size() const{
		return N;
	}

	T* operator[](int idx) const{
		return matrix[idx];
	}

	SquareMatrix<T>&& operator*(SquareMatrix<T>& rhs){
		SquareMatrix<T>& res = *(new SquareMatrix<T>(N));
		for(int r=0; r<N; ++r){
			for(int c=0; c<N; ++c){
				res[r][c] = 0;
				for(int cr=0; cr<N; ++cr){
					res[r][c] += matrix[r][cr] * rhs[cr][c];
				}
			}
		}
		return std::move(res);
	}

	void print(const char* format){
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				printf(format, matrix[i][j]);
				printf(" ");
			}
			printf("\n");
		}
		printf("\n");
	}

	void zero(){
		for(int i=0; i<N; ++i)
			memset(matrix[i],0,sizeof(T)*N);
	}

private:
	void allocate(){
		matrix = new T*[N];	
		for(int i=0; i<N; ++i)
			matrix[i] = new T[N];
	}

	void deallocate(){
		for(int i=0; i<N; ++i)
			delete[] matrix[i];
		delete[] matrix;
	}

	T** matrix;
	int N;
};

template <typename T>
SquareMatrix<T> sqm_pow(SquareMatrix<T>& A, int k){
	if(k == 1)
		return A;
	if(k & 1)
		return sqm_pow<T>(A,k-1)*A;

	SquareMatrix<T> half = sqm_pow<T>(A, k >> 1);
	return half*half;
}

int C, N, K, M;
int sLen[50];
double prob[50][50];
int sLike[10];

void get_input(){
	scanf("%d %d %d", &N, &K, &M);
	for(int i=0; i<N; ++i)
		scanf("%d", &sLen[i]);

	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			scanf("%lf", &prob[i][j]);
		}
	}

	for(int i=0; i<M; ++i){
		scanf("%d", &sLike[i]);
	}
}

void solve(){
	SquareMatrix<double> W(N*4);
	W.zero();

	for(int s=0; s<N; ++s){
		for(int t=0; t<4; ++t){
			for(int p=0; p<N; ++p){
				W[(t*N)+p][s] = (sLen[p] == t+1) ? prob[p][s] : 0;
			}
		}
	}

	for(int c=N; c<4*N; ++c){
		W[c-N][c] = 1;
	}

	SquareMatrix<double> Wp = sqm_pow(W,K);
	//Wp.print("%lf");

	for(int l=0; l<M; ++l){
		int cur = sLike[l];
		// printf("cur:%d N:%d\n",cur, N);
		double p = 0;
		for(int t=0; t<sLen[cur]; ++t)
			p += Wp[0][(t*N)+cur];
		printf("%.8lf ", p);
	}
	printf("\n");
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		solve();
	}
}