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

int C, N;
std::array<unsigned long long,4> start_state;
std::array<unsigned long long,4> end_state;

inline int increment(int icost){
	return (icost > 0) ? icost+1 : icost-1;
}

// void print_arr(std::array<unsigned long long,4>& arr){
// 	printf("%p\n%p\n%p\n%p\n", arr[0], arr[1], arr[2], arr[3]);
// }

bool different_direction(int a, int b){
	return ((a > 0 && b < 0) || (a < 0 && b > 0));
}

void solve(){
	std::queue<std::array<unsigned long long,4>> bfs;
	std::map<std::array<unsigned long long,4>,int> cost;

	if(start_state == end_state){
		printf("0\n");
		return;
	}

	cost[start_state] = 1;
	cost[end_state] = -1;
	bfs.push(start_state);
	bfs.push(end_state);

	while(!bfs.empty()){
		std::array<unsigned long long,4> cur = bfs.front(); bfs.pop();
		int curcost = cost[cur];

		// printf("<%d>\n",curcost);
		// print_arr(cur);

		for(int f=0; f<4; ++f){
			int ftop = cur[f] & 0xF;
			if(ftop == 0) continue;

			for(int t=0; t<4; ++t){
				if(f==t) continue;
				int ttop = cur[t] & 0xF;
				if(ftop < ttop || cur[t] == 0){
					std::array<unsigned long long, 4> nxt = cur;
					nxt[f] >>= 4;
					nxt[t] = (nxt[t] << 4) | ftop;

					// printf("<<nxt>>\n");
					// print_arr(nxt);

					auto cost_nxt = cost.find(nxt);

					if(cost_nxt == cost.end()){
						cost[nxt] = increment(curcost);
						bfs.push(nxt);
					}
					else if(different_direction(curcost, cost_nxt->second)){
						printf("%d\n", std::abs(curcost)+std::abs(cost_nxt->second)-1);
						return;
					}
				}
			}
		}
	}
}


int main(int argc, char** argv){
	int icnt;
	int ivar;

	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d", &N);
		for(int s=0; s<4; ++s){
			start_state[s] = 0;
			scanf("%d", &icnt);
			for(int ic=0; ic<icnt; ++ic){
				scanf("%d", &ivar);
				start_state[s] = (start_state[s] << 4) | ivar;
			}
		}
		for(int s=0; s<4; ++s){
			end_state[s] = 0;
			scanf("%d", &icnt);
			for(int ic=0; ic<icnt; ++ic){
				scanf("%d", &ivar);
				end_state[s] = (end_state[s] << 4) | ivar;
			}
		}

		solve();
	}
}