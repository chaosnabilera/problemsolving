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
#include <bitset>

int C, N;
int start_state;
int end_state;
int delmask[13];
int cost[1 << 24];

bool sign_match(int a, int b){
	return ((a > 0 && b >0) || (a<0 && b<0));
}

int increment(int a){
	return (a > 0) ? a+1 : a-1;
}

void printbin(int num){
	std::bitset<32> z(num);
	std::cout << z << std::endl;
}

void solve(){
	std::queue<int> bfs;
	int cost_size = 1 << (N*2);

	if(start_state == end_state){
		printf("0\n");
		return;
	}
	for(int i=0; i<cost_size; ++i){
		cost[i] = 0;
	}

	cost[start_state] = 1;
	cost[end_state] = -1;
	bfs.push(start_state);
	bfs.push(end_state);

	while(!bfs.empty()){
		int curstate = bfs.front(); bfs.pop();
		int curcost = cost[curstate];
		int top[4] = {0xFFFF,0xFFFF,0xFFFF,0xFFFF};
		for(int i=0; i<N; ++i){
			int i_at = (curstate >> (i*2)) & 3;
			if(top[i_at] > i){
				top[i_at] = i;
			}
		}

		// printf("top: %d %d %d %d\n", top[0],top[1],top[2],top[3]);

		for(int f=0; f<4; ++f){
			if(top[f] == 0xFFFF) continue;

			for(int t=0; t<4; ++t){
				if(top[f] < top[t]){
					int nextstate = curstate;
					// printbin(nextstate);
					nextstate &= delmask[top[f]];
					nextstate |= (t << (2*top[f]));
					// printbin(nextstate);
					// printf(">>\n");
					if(cost[nextstate] == 0){
						cost[nextstate] = increment(curcost);
						bfs.push(nextstate);
					}
					else{
						if(!sign_match(curcost, cost[nextstate])){
							printf("%d\n", std::abs(curcost)+std::abs(cost[nextstate])-1);
							return;
						}
					}
				}
			}
		}
	}
}

int main(int argc, char** argv){
	int icnt, ivar;

	for(int i=0; i<12; ++i){
		delmask[i] = 0xFFFFFFFF;
		delmask[i] ^= (3 << (i*2));
		// printf("%d: ",i);
		// printbin(delmask[i]);
	}

	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d", &N);
		start_state = 0;
		end_state = 0;
		for(int z=0; z<4; ++z){
			scanf("%d", &icnt);
			for(int x=0; x<icnt; ++x){
				scanf("%d", &ivar);
				start_state |= (z << ((ivar-1)*2));
			}
		}

		for(int x=0; x<N; ++x){
			end_state |= (3 << (x*2));	
		}

		// printbin(start_state);
		// printbin(end_state);
		solve();
	}
}
