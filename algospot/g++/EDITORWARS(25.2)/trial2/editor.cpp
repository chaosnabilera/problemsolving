#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int N,M;

int parent[10000];
int size[10000];
int enemy[10000];
int plist[10000];
bool visited[10000];

void get_input(){
	scanf("%d%d", &N,&M);
	for(int i=0; i<N; ++i){
		parent[i] = i;
		size[i] = 1;
	}
	memset(enemy,0xFF,N*sizeof(int));
}

int find_parent(int cur){ // change a->b->c->d ==> a,b,c -> d all the way up
	int p = cur;
	int plist_size = 0;
	int res;

	while(parent[p] != parent[parent[p]]){
		plist[plist_size++] = p;
		p = parent[p];
	}
	res = parent[p];

	for(int i=0; i<plist_size; ++i){
		parent[plist[i]] = res;
	}

	return res;
}

void p_merge(int pa, int pb){
	if(pa == pb)
		return;

	if(size[pa] > size[pb]){
		size[pa] += size[pb];
		parent[pb] = pa;
	}
	else{
		size[pb] += size[pa];
		parent[pa] = pb;
	}
}

void solve(){
	char word[10];
	int a,b;
	int pa,pb,p_epa,p_epb;
	vector<pair<int,int>> team;

	bool do_continue = false;

	for(int i=0; i<M; ++i){
		scanf("%s%d%d",word,&a,&b);

		if(do_continue)
			continue;

		pa = find_parent(a);
		pb = find_parent(b);

		if(word[0] == 'A'){ // ACK
			if(enemy[pa] == -1 && enemy[pb] == -1){
				p_merge(pa,pb);
			}
			else if(enemy[pa] == -1){
				p_epb = find_parent(enemy[pb]);
				p_merge(pa,pb);
				enemy[parent[pa]] = p_epb;
			}
			else if(enemy[pb] == -1){
				p_epa = find_parent(enemy[pa]);
				p_merge(pa,pb);
				enemy[parent[pa]] = p_epa;
			}
			else{
				p_epa = find_parent(enemy[pa]);
				p_epb = find_parent(enemy[pb]);

				if(pa == p_epa || pa == p_epb || pb == p_epa || pb == p_epb){
					printf("CONTRADICTION AT %d\n", i+1);
					do_continue = true;
					continue;
				}

				p_merge(pa,pb);
				p_merge(p_epa, p_epb);
				enemy[parent[pa]] = parent[p_epa];
				enemy[parent[p_epa]] = parent[pa];
			}
		}
		else{ // DIS
			if(pa == pb){
				printf("CONTRADICTION AT %d\n",i+1);
				do_continue = true;
				continue;
			}

			if(enemy[pa] == -1 && enemy[pb] == -1){
				enemy[pa] = pb;
				enemy[pb] = pa;
			}
			else if(enemy[pa] == -1){
				p_epb = find_parent(enemy[pb]);
				p_merge(p_epb,pa);
				enemy[parent[pa]] = pb;
				enemy[pb] = parent[pa];
			}
			else if(enemy[pb] == -1){
				p_epa = find_parent(enemy[pa]);
				p_merge(p_epa,pb);
				enemy[parent[pb]] = pa;
				enemy[pa] = parent[pb];
			}
			else{
				p_epa = find_parent(enemy[pa]);
				p_epb = find_parent(enemy[pb]);

				if(p_epa == p_epb){
					printf("CONTRADICTION AT %d\n", i+1);
					do_continue = true;
					continue;
				}
				p_merge(pa, p_epb);
				p_merge(pb, p_epa);
				enemy[parent[pa]] = parent[pb];
				enemy[parent[pb]] = parent[pa];
			}
		}
	}

	if(do_continue)
		return;

	int cnt = 0;
	memset(visited,0,N);
	for(int i=0; i<N; ++i){
		if(visited[i])
			continue;

		visited[i] = true;

		if(i != parent[i])
			continue;

		// printf("%d\n",i);

		if(enemy[i] == -1){
			cnt += size[i];
			// team.push_back(make_pair(size[i],0));
		}
		else{
			int p_ei = find_parent(enemy[i]);
			cnt += max(size[i],size[p_ei]);
			visited[p_ei] = true;
		}
	}

	printf("MAX PARTY SIZE IS %d\n", cnt);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}