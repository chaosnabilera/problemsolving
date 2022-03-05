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

int N, Q;
int F[100000];
int L[100000];
bool Mem[100000];

void get_input(){
	scanf("%d %d", &N, &Q);
	F[0] = 0;
	for(int i=1; i<N; ++i)
		scanf("%d", &F[i]);
}

int closest_ancestor(int a, int b){
	unordered_set<int> visited;
	int res = 0;

	if(a == b)
		return a;

	Mem[a] = true;
	Mem[b] = true;
	visited.insert(a);
	visited.insert(b);

	while(a != 0 || b != 0){
		a = F[a];
		b = F[b];

		if(a == b){
			res = a;
			break;
		}
		if(a != F[a] && Mem[a]){
			res = a;
			break;
		}
		if(b != F[b] && Mem[b]){
			res = b;
			break;
		}

		// mark visited
		Mem[a] = true; 	
		Mem[b] = true;
		visited.insert(a);
		visited.insert(b);
	}

	// printf("Mem: ");
	// for(int i=0; i<N; ++i)
	// 	printf("%d ", Mem[i]);
	// printf("\n");

	for(int v:visited)
		Mem[v] = false;

	return res;
}

void solve(){
	int a,b,p;

	for(int i=0; i<N; ++i)
		L[i] = -1;
	L[0] = 0;

	// precompute length to root
	vector<pair<int,int>> stack;
	for(int i=1; i<N; ++i){
		if(L[i] != -1)
			continue;
		stack.push_back(make_pair(i,F[i]));
		while(!stack.empty()){
			int cur = stack.back().first;
			int parent = stack.back().second;
			if(L[cur] != -1){
				stack.pop_back();
				continue;
			}
			if(L[parent] == -1){
				stack.push_back(make_pair(parent,F[parent]));
			}
			else{
				L[cur] = L[parent]+1;
				stack.pop_back();
			}
		}
	}

	// printf("L: ");
	// for(int i=0; i<N; ++i)
	// 	printf("%d ", L[i]);
	// printf("\n");

	for(int i=0; i<Q; ++i){
		scanf("%d %d", &a, &b);
		p = closest_ancestor(a,b);

		// printf("Mem: ");
		// for(int i=0; i<N; ++i)
		// 	printf("%d ", Mem[i]);
		// printf("\n");

		// printf("a:%d b:%d p:%d\n",a,b,p);
		printf("%d\n",(L[a]-L[p])+(L[b]-L[p]));

		
	}
}

int main(int argc, char** argv){
	int T;
	memset(Mem,0,sizeof(Mem));

	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}