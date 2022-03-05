#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int N;
int X[100];
int Y[100];
int R[100];

vector<int> Child[101];
int Parent[101];

int GlobalMax;

bool custom_cmp(int a, int b){
	return R[a] < R[b];
}

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i)
		scanf("%d%d%d", &X[i], &Y[i], &R[i]);
}

void build_graph(){
	vector<int> castle;
	castle.resize(N);
	for(int i=0; i<N; ++i)
		castle[i] = i;

	for(int i=0; i<101; ++i)
		Child[i].clear();

	memset(Parent,0xFF,sizeof(Parent));

	sort(castle.begin(),castle.end(),custom_cmp);

	// for(auto i:castle){
	// 	printf("%d X:%d Y:%d R:%d\n",i,X[i],Y[i],R[i]);
	// }

	for(int ii=0; ii<N; ++ii){
		int i = castle[ii];
		for(int jj=ii+1; jj<N; ++jj){
			int j = castle[jj];

			int x = X[j]-X[i];
			int y = Y[j]-Y[i];
			if((x*x) + (y*y) < (R[j]*R[j])){
				Parent[i] = j;
				Child[j].push_back(i);
				break;
			}
		}
	}
	for(int i=0; i<N; ++i){
		if(Parent[i] == -1){
			Parent[i] = 100;
			Child[100].push_back(i);
		}
	}
}

void print_child(){
	for(int i=0; i<N; ++i){
		printf("%d: ",i);
		for(auto c:Child[i]){
			printf("%d ", c);
		}
		printf("\n");
	}
	for(auto c:Child[100])
		printf("%d ",c);
	printf("\n");
}

int rec_solve(int cur){
	if(Child[cur].empty())
		return 0;

	int max1 = 0;
	int max2 = 0;

	for(int c:Child[cur]){
		int v = rec_solve(c)+1;
		if(v > max1){
			max2 = max1;
			max1 = v;
		}
		else if(v > max2){
			max2 = v;
		}
	}

	if(cur == 100 && max2 == 0)
		--max1;
	
	GlobalMax = max(GlobalMax, max1+max2);

	// printf("cur:%d max1:%d max2:%d\n",cur,max1,max2);
	return max1;
}

void solve(){
	build_graph();
	// print_child();
	GlobalMax = 0;
	rec_solve(100);
	printf("%d\n", GlobalMax);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}