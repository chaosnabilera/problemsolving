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

int main(int argc, char** argv){
	double m1[2][2] = {
		{ 0.1, 0.2},
		{ 0.3, 0.4}
	};

	double m2[2][2] = {
		{ 0.5, 0.6},
		{ 0.7, 0.8}
	};

	SquareMatrix<double> s1(2);
	SquareMatrix<double> s2(2);

	for(int i=0; i<2; ++i)
		for(int j=0; j<2; ++j){
			s1[i][j] = m1[i][j];
			s2[i][j] = m2[i][j];
		}

	s1.print("%lf");
	s2.print("%lf");

	SquareMatrix<double> s3 = s1*s2;
	s3.print("%lf");

	sqm_pow<double>(s1,1).print("%lf");
	s1.print("%lf");

	sqm_pow<double>(s1,2).print("%lf");
	SquareMatrix<double> aa = s1*s1;
	aa.print("%lf");

	sqm_pow<double>(s1,3).print("%lf");
	SquareMatrix<double> aaa = aa*s1;
	aaa.print("%lf");

	sqm_pow<double>(s1,4).print("%lf");
	SquareMatrix<double> aaaa = aaa*s1;
	aaaa.print("%lf");

	return 0;
}