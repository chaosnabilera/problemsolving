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

struct Sched{
	Sched(int b=-1, int e=-1) : beg(b), end(e) {};
	int beg, end;
};

int N;
vector<Sched> W;
vector<Sched> M;

vector<int> Graph[400];
const int tW = 0;
const int fW = 1;
const int tM = 2;
const int fM = 3;

char WM[100];
bool Visited[400];

void get_input(){
	int a,b,c,d;
	scanf("%d", &N);

	W.clear();
	M.clear();
	for(int i=0; i<N; ++i){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		W.push_back(Sched(a,b));
		M.push_back(Sched(c,d));
	}
	for(int i=0; i<4*N; ++i)
		Graph[i].clear();
}

bool overlaps(Sched& a, Sched& b){
	if(a.beg < b.beg){
		return a.end > b.beg;
	}
	else{
		return b.end > a.beg;
	}
}

void build_graph(){
	for(int i=0; i<N; ++i){
		int base = i*4;
		Graph[base + tW].push_back(base+fM);
		Graph[base + fW].push_back(base+tM);
		Graph[base + tM].push_back(base+fW);
		Graph[base + fM].push_back(base+tW);

		for(int j=i+1; j<N; ++j){
			int tbase = j*4;
			if(overlaps(W[i],W[j])){
				Graph[base + tW].push_back(tbase + fW);
				Graph[tbase+ tW].push_back(base + fW);
			}
			if(overlaps(W[i],M[j])){
				Graph[base + tW].push_back(tbase + fM);
				Graph[tbase+ tM].push_back(base + fW);	
			}
			if(overlaps(M[i],W[j])){
				Graph[base + tM].push_back(tbase + fW);
				Graph[tbase+ tW].push_back(base + fM);
			}
			if(overlaps(M[i],M[j])){
				Graph[base + tM].push_back(tbase + fM);
				Graph[tbase+ tM].push_back(base + fM);	
			}
		}
	}
}

void print_graph(){
	for(int i=0; i<4*N; ++i){
		printf("%d: ",i);
		for(int v:Graph[i])
			printf("%d ",v);
		printf("\n");
	}
}

void dfs(int cur){
	Visited[cur] = true;
	for(int nxt:Graph[cur])
		if(!Visited[nxt])
			dfs(nxt);
}

bool solve(){
	bool last_Visited[400];
	bool contradiction = false;

	build_graph();
	// print_graph();

	memset(WM,0,sizeof(WM));
	memset(Visited,0,sizeof(Visited));

	for(int i=0; i<N; ++i){
		if(WM[i])
			continue;

		memcpy(last_Visited, Visited, sizeof(Visited));

		dfs((i*4)+tW);
		contradiction = false;
		for(int j=0; j<N; ++j){
			if((Visited[(j*4)+tW] && Visited[(j*4)+fW]) || (Visited[(j*4)+tM] && Visited[(j*4)+fM])){
				contradiction = true;
				break;
			}
		}
		if(!contradiction){
			for(int j=0; j<N; ++j){
				if(Visited[(j*4)+tW]){
					WM[j] = 'W';
				}
				else if(Visited[(j*4)+tM]){
					WM[j] = 'M';
				}
			}
			continue;
		}

		memcpy(Visited, last_Visited, sizeof(Visited));
		dfs((i*4)+tM);
		contradiction = false;
		for(int j=0; j<N; ++j){
			if((Visited[(j*4)+tW] && Visited[(j*4)+fW]) || (Visited[(j*4)+tM] && Visited[(j*4)+fM])){
				contradiction = true;
				break;
			}	
		}
		if(!contradiction){
			for(int j=0; j<N; ++j){
				if(Visited[(j*4)+tW]){
					WM[j] = 'W';
				}
				else if(Visited[(j*4)+tM]){
					WM[j] = 'M';
				}
			}
		}
		else{
			return false;
		}
	}

	return true;
}

void print_answer(){
	for(int i=0; i<N; ++i){
		if(WM[i] == 'W')
			printf("%d %d\n",W[i].beg,W[i].end);
		else
			printf("%d %d\n",M[i].beg,M[i].end);
	}
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		if(solve()){
			printf("POSSIBLE\n");
			print_answer();
		}
		else{
			printf("IMPOSSIBLE\n");
		}
	}
}