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

int N,M;
int Parent[10000];
int SSize[10000];
int Enemy[10000];
int Buf[10000];

int get_parent(int a){
	int p = a;
	int d = 0;
	while(p != Parent[p]){
		Buf[d++] = p;
		p = Parent[p];
	}
	for(int i=0; i<d; ++i)
		Parent[Buf[i]] = p;

	return p;
}

int merge(int a, int b){
	a = get_parent(a);
	b = get_parent(b);

	if(a == b)
		return a;

	if(SSize[a] > SSize[b]){
		Parent[b] = a;
		SSize[a] += SSize[b];
		return a;
	}
	else{
		Parent[a] = b;
		SSize[b] += SSize[a];
		return b;
	}
}

void print_status(){
	printf("Parent: ");
	for(int i=0; i<N; ++i){
		printf("%d:%d ", i, Parent[i]);
	}
	printf("\n");

	printf("SSize: ");
	for(int i=0; i<N; ++i){
		printf("%d:%d ", i, SSize[i]);
	}
	printf("\n");

	printf("Enemy: ");
	for(int i=0; i<N; ++i){
		printf("%d:%d ", i, Enemy[i]);
	}
	printf("\n");
}

void solve(){
	char word[4];
	int a,b,r,e;
	vector<int> root;
	bool contradiction = false;

	scanf("%d %d", &N, &M);
	for(int i=0; i<N; ++i){
		Parent[i] = i;
		SSize[i] = 1;
		Enemy[i] = -1;
	}

	for(int i=0; i<M; ++i){
		scanf("%s %d %d",word,&a,&b);
		if(contradiction)
			continue;

		int pa = get_parent(a);
		int pb = get_parent(b);

		int epa = (Enemy[pa] != -1) ? get_parent(Enemy[pa]) : -1;
		int epb = (Enemy[pb] != -1) ? get_parent(Enemy[pb]) : -1;

		if(word[0] == 'A'){
			if(epa == pb || epb == pa){
				printf("CONTRADICTION AT %d\n",i+1);
				contradiction = true;
				continue;
			}
			r = merge(pa,pb);
			if(epa != -1 && epb != -1){
				e = merge(epa, epb);
				Enemy[r] = e;
				Enemy[e] = r;
			}
			else if(epa != -1){
				Enemy[r] = epa;
				Enemy[epa] = r;
			}
			else if(epb != -1){
				Enemy[r] = epb;
				Enemy[epb] = r;
			}
			else{
				Enemy[r] = -1;
			}
		}
		else{
			if(pa == pb){
				printf("CONTRADICTION AT %d\n",i+1);
				contradiction = true;
				continue;
			}

			if(epa != -1 && epb != -1){
				int pa_epb = merge(pa,epb);
				int pb_epa = merge(pb,epa);
				Enemy[pa_epb] = pb_epa;
				Enemy[pb_epa] = pa_epb;
			}
			else if(epa != -1){
				int pb_epa = merge(pb,epa);
				Enemy[pa] = pb_epa;
				Enemy[pb_epa] = pa;
			}
			else if(epb != -1){
				int pa_epb = merge(pa,epb);
				Enemy[pb] = pa_epb;
				Enemy[pa_epb] = pb;
			}
			else{
				Enemy[pa] = pb;
				Enemy[pb] = pa;
			}
		}
	}

	if(contradiction)
		return;

	for(int i=0; i<N; ++i){
		if(get_parent(i) == i)
			root.push_back(i);
	}

	// for(int r:root){
	// 	printf("%d ", r);
	// }
	// printf("\n");

	int no_enemy = 0;
	int larger = 0;
	int same = 0;
	for(int r:root){
		if(Enemy[r] == -1){
			no_enemy += SSize[r];
			continue;
		}
		int er = get_parent(Enemy[r]);
		
		if(SSize[r] > SSize[er])
			larger += SSize[r];
		else if(SSize[r] == SSize[er])
			same += SSize[r];
	}

	// print_status();
	// printf("%d %d\n",max_size, no_enemy);

	printf("MAX PARTY SIZE IS %d\n",larger+(same/2)+no_enemy);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		solve();
	}
}