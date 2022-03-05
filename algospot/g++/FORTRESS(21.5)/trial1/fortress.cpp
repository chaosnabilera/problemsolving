#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int X[100];
int Y[100];
int R[100];

int GlobalMax;

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%d %d %d", &X[i], &Y[i], &R[i]);
	}
}

bool custom_cmp(int a, int b){
	return R[a] < R[b];
}

bool is_inside(int s, int l){
	int x = X[s]-X[l];
	int y = Y[s]-Y[l];
	int r = R[l];
	return (x*x)+(y*y) < (r*r);
}

int rec_traverse(vector<int>* Castle, int cur){
	int l[2] = {0};

	for(int c:Castle[cur]){
		int cl = 1+rec_traverse(Castle,c);
		if(cl > l[0]){
			l[1] = l[0];
			l[0] = cl;
		}
		else if(cl > l[1]){
			l[1] = cl;
		}
	}

	GlobalMax = max(GlobalMax, l[0]+l[1]);

	return l[0];
}

void solve(){
	int idx[100];
	// int parent[100];
	vector<int> Castle[101];

	for(int i=0; i<N; ++i){
		idx[i] = i;
		// parent[i] = -1;
	}

	sort(&idx[0], &idx[N], custom_cmp);

	for(int i=0; i<N-1; ++i){
		for(int j=i+1; j<N; ++j){
			if(is_inside(idx[i],idx[j])){
				//parent[i] = j;
				Castle[idx[j]].push_back(idx[i]);
				break;
			}
		}
	}
	// for(int i=0; i<N; ++i){
	// 	if(parent[i] == -1)
	// 		Castle[N].push_back(i);
	// }

	GlobalMax = 0;
	rec_traverse(Castle, 0);

	printf("%d\n", GlobalMax);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}