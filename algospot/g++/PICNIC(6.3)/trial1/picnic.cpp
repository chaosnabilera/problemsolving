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

using namespace std;

int C, N, M;
int ALL_OCCUPIED;
bool FRIEND[10][10];

int rec_solve(int state){
	if(state == ALL_OCCUPIED){
		return 1;
	}

	int cnt = 0;
	for(int i=0; i<N; ++i){
		if((state & (1<<i)) == 0){
			for(int j=0; j<N; ++j){
				if((state & (1<<j)) == 0 && FRIEND[i][j]){
					int next_state = state;
					next_state |= (1<<i);
					next_state |= (1<<j);
					cnt += rec_solve(next_state);
				}
			}
			break;
		}
	}
	return cnt;
}

void get_input(){
	int a, b;
	scanf("%d %d", &N, &M);

	ALL_OCCUPIED = 0;
	for(int i=0; i<N; ++i){
		ALL_OCCUPIED |= (1<<i);
	}

	// printf("ALL_OCCUPIED: %d\n", ALL_OCCUPIED);

	memset(FRIEND, 0, sizeof(FRIEND));
	for(int i=0; i<M; ++i){
		scanf("%d %d", &a, &b);
		FRIEND[a][b] = true;
		FRIEND[b][a] = true;
	}
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		printf("%d\n", rec_solve(0));
	}
}