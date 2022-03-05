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

int C,N,N4;
int timetable[400][2];

std::vector<int> adj[400];
int visit_order[400];
int visit_idx;
std::vector<int> visit_stack;
int scc_order;
int scc_label[400];
std::vector<int> scc;
bool sat2[400];

void clearvar(){
	for(int i=0; i<N4; ++i){
		adj[i].clear();
	}
	for(int i=0; i<N4; ++i){
		visit_order[i] = -1;
	}
	visit_idx = 0;
	visit_stack.clear();
	scc_order = 0;
	for(int i=0; i<N4; ++i){
		scc_label[i] = -1;
	}
	memset(sat2, 0, sizeof(sat2));
}

bool overlaps(int i, int j){
	if(timetable[i][0] < timetable[j][0]){
		return timetable[j][0] < timetable[i][1];
	}
	else{
		return timetable[i][0] < timetable[j][1];
	}
}

void buildgraph(){
	// monthly-weekly relationship
	for(int n=0; n<N; ++n){
		int w = (n*4);	int nw = w+1;
		int m = w+2;    int nm = w+3;
		// either weekly or monthly
		adj[w].push_back(nm);
		adj[m].push_back(nw);
		// if not weekly then must monthly. vice versa
		adj[nw].push_back(m);
		adj[nm].push_back(w);
	}
	// if 1 meeting at a time relationship
	for(int i=0; i<N4; i+=2){
		for(int j=0; j<N4; j+=2){
			if(i == j){
				continue;
			}
			if(overlaps(i,j)){
				adj[i].push_back(j+1);
				adj[j].push_back(i+1);
			}
		}
	}
}

int tarjan(int cur){
	visit_order[cur] = visit_idx++;
	int least_connected_visit = visit_order[cur];

	visit_stack.push_back(cur);

	for(auto nxt: adj[cur]){
		if(visit_order[nxt] == -1){
			least_connected_visit = std::min(least_connected_visit, tarjan(nxt));
		}
		else if(scc_label[nxt] == -1){
			least_connected_visit = std::min(least_connected_visit, visit_order[nxt]);
		}
	}

	if(least_connected_visit == visit_order[cur]){
		int e;
		do{
			e = visit_stack.back(); visit_stack.pop_back();
			scc_label[e] = scc_order;
			scc.push_back(e);
		} while(e != cur);
		scc_order++;
	}

	return least_connected_visit;
}

void solve(){
	clearvar();
	buildgraph();
	for(int i=0; i<N4; ++i){
		if(visit_order[i] == -1){
			tarjan(i);
		}
	}

	for(int i=0; i<N4; i+=2){
		if(scc_label[i] == scc_label[i+1]){
			printf("IMPOSSIBLE\n");
			return;
		}
	}

	// solve 2-SAT
	std::reverse(scc.begin(), scc.end());
	for(auto i:scc){
		// printf("%d ",i);
		if(sat2[i]) continue;
		if((i&1) == 0){
			sat2[i+1] = true;
		}
		else{
			sat2[i-1] = true;
		}
	}
	// printf("\n");

	// for(int i=0; i<N4; ++i){
	// 	printf("%d(%d) ", scc[i], sat2[scc[i]]);
	// }
	// printf("\n");

	printf("POSSIBLE\n");
	for(int i=0; i<N4; i+=4){
		if(sat2[i]){
			printf("%d %d\n", timetable[i][0], timetable[i][1]);
		}
		else{
			printf("%d %d\n", timetable[i+2][0], timetable[i+2][1]);
		}
	}
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d", &N);
		N4 = N*4;
		for(int n=0; n<N; ++n){
			scanf("%d %d %d %d",
				&timetable[n*4][0],   &timetable[n*4][1],
				&timetable[n*4+2][0], &timetable[n*4+2][1]);
		}
		solve();
	}
}