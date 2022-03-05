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

const int MAXIDX = 1000000;

int N;
int A[50000];
int F1D[1000001];

void f1d_increment(int znum){
	int num = znum+1;
	while(num <= MAXIDX){
		++F1D[num];
		num += num - (num & (num-1));
	}
}

int f1d_sum(int znum){
	int num = znum+1;
	int sum = 0;
	while(num > 0){
		sum += F1D[num];
		num = (num & (num-1));
	}
	return sum;
}

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i)
		scanf("%d", &A[i]);
}

void solve(){
	int sum = 0;
	memset(F1D,0,sizeof(F1D));
	for(int i=0; i<N; ++i){
		f1d_increment(A[i]);
		sum += f1d_sum(MAXIDX)-f1d_sum(A[i]);
	}
	printf("%d\n", sum);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}