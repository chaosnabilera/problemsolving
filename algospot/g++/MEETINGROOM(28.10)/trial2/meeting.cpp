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

const int W = 0;
const int NW = 1;
const int M = 2;
const int NM = 3;

int N;
int iSched[100][4];
vector<int> Adj[400];

char FinalStatus[400];
char Status[400];
bool Visited[400];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i)
		scanf("%d %d %d %d", &iSched[i][0], &iSched[i][1], &iSched[i][2], &iSched[i][3]);
}

bool overlaps(int abeg, int aend, int bbeg, int bend){
	if(abeg < bbeg){
		return aend > bbeg;
	}
	else{
		return bend > abeg;
	}
}

void build_graph(){
	for(int i=0; i<N*4; ++i)
		Adj[i].clear();

	for(int i=0; i<N*4; i+=4){
		Adj[i+W].push_back(i+NM); // weekly -> no monthly
		Adj[i+NW].push_back(i+M); // no weekly -> monthly
		Adj[i+M].push_back(i+NW); // monthly -> no weekly
		Adj[i+NM].push_back(i+W); // no monthly -> weekly
	}

	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			if(i==j)
				continue;
			if(overlaps(iSched[i][0],iSched[i][1],iSched[j][0],iSched[j][1])){
				Adj[(i*4)+W].push_back((j*4)+NW);
			}
			if(overlaps(iSched[i][0],iSched[i][1],iSched[j][2],iSched[j][3])){
				Adj[(i*4)+W].push_back((j*4)+NM);
			}
			if(overlaps(iSched[i][2],iSched[i][3],iSched[j][0],iSched[j][1])){
				Adj[(i*4)+M].push_back((j*4)+NW);
			}
			if(overlaps(iSched[i][2],iSched[i][3],iSched[j][2],iSched[j][3])){
				Adj[(i*4)+M].push_back((j*4)+NM);
			}
		}
	}
}

void print_graph(){
	for(int i=0; i<N*4; ++i){
		printf("%d: ",i);
		for(int j:Adj[i])
			printf("%d ",j);
		printf("\n");
	}
}

bool traverse(int cur){
	// printf("%d\n",cur);
	if(Status[cur] == 0){
		return false;
	}
	Status[cur] = 1;
	Visited[cur] = true;

	int base = cur & 0xFFFFFFFC;
	int opt = cur & 3;
	if(
		(opt == W  && (Status[base+NW] == 1 || Status[base+M] == 1 || Status[base+NM] == 0)) ||
		(opt == NW && (Status[base+W]  == 1 || Status[base+M] == 0 || Status[base+NM] == 1)) ||
		(opt == M  && (Status[base+W]  == 1 || Status[base+NW]== 0 || Status[base+NM] == 1)) ||
		(opt == NM && (Status[base+W]  == 0 || Status[base+NW]== 1 || Status[base+M]  == 1))
	){
		// printf("opt:%d Status[%d]:%d Status[%d]:%d Status[%d]:%d Status[%d]:%d\n",
		// 	opt, base+W, Status[base+W], base+NW, Status[base+NW], base+M, Status[base+M], base+NM, Status[base+NM]);
		return false;
	}

	switch(opt){
	case W:
		Status[base+NW] = 0;
		Status[base+M]  = 0;
		Status[base+NM] = 1;
		break;
	case NW:
		Status[base+W] = 0;
		Status[base+M] = 1;
		Status[base+NM]= 0;
		break;
	case M:
		Status[base+W] = 0;
		Status[base+NW]= 1;
		Status[base+NM]= 0;
		break;
	case NM:
		Status[base+W] = 1;
		Status[base+NW]= 0;
		Status[base+M] = 0;
		break;
	}

	for(int nxt:Adj[cur]){
		if(!Visited[nxt]){
			if(!traverse(nxt))
				return false;
		}
	}

	return true;
}

void reset_status(){
	int ilim = N*4;
	for(int i=0; i<ilim; ++i)
		Status[i] = -1;
	memset(Visited,0,sizeof(Visited));
}

void copy_status(){
	int ilim = N*4;
	for(int i=0; i<ilim; ++i){
		if(Status[i] != -1)
			FinalStatus[i] = Status[i];
	}
}

void solve(){
	bool all_possible = true;

	for(int i=0; i<N*4; ++i)
		FinalStatus[i] = -1;

	build_graph();
	// print_graph();

	for(int i=0; i<(N*4); i+=4){
		// printf("? %d %d\n",i,N);
		if(FinalStatus[i] == -1){
			// try weekly
			reset_status();
			if(traverse(i+W)){
				copy_status();
				continue;
			}
			// printf("%d didn't work\n",i+W);

			reset_status();
			if(traverse(i+M)){
				copy_status();
				continue;
			}
			// printf("?????\n");

			// printf("%d didn't work\n",i+M);
			all_possible = false;
			break;
		}
	}

	if(all_possible){
		printf("POSSIBLE\n");
		for(int i=0; i<N*4; i+=4){
			if(FinalStatus[i+W] == 1){
				printf("%d %d\n", iSched[i>>2][0], iSched[i>>2][1]);
			}
			else{
				printf("%d %d\n", iSched[i>>2][2], iSched[i>>2][3]);
			}
		}
	}
	else{
		printf("IMPOSSIBLE\n");
	}
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}