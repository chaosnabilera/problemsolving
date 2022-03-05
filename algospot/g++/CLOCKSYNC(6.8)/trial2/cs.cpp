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

int State[16];
int Switch[10][6] = {
	{ 0, 1, 2,-1,-1,-1},
	{ 3, 7, 9,11,-1,-1},
	{ 4,10,14,15,-1,-1},
	{ 0, 4, 5, 6, 7,-1},
	{ 6, 7, 8,10,12,-1},
	{ 0, 2,14,15,-1,-1},
	{ 3,14,15,-1,-1,-1},
	{ 4, 5, 7,14,15,-1},
	{ 1, 2, 3, 4, 5,-1},
	{ 3, 4, 5, 9,13,-1}
};

void get_input(){
	for(int i=0; i<16; ++i){
		scanf("%d", &State[i]);
		State[i] = (State[i]/3) & 0x3;
	}
}

int try_solve(int state){
	int scnt[10] = {0};
	int curstate[16];
	int scntsum = 0;
	int sumstate = 0;

	memcpy(curstate,State,sizeof(State));

	for(int i=0; i<10; ++i){
		scnt[i] = state & 0x3;
		state >>= 2;
	}

	for(int s=0; s<10; ++s){
		scntsum += scnt[s];
		for(int i=0; i<6; ++i){
			if(Switch[s][i] == -1)
				break;
			curstate[Switch[s][i]] += scnt[s];
		}
	}

	for(int i=0; i<16; ++i)
		sumstate += (curstate[i] & 0x3);

	if(sumstate == 0)
		return scntsum;
	else
		return -1;
}

void solve(){
	int ilim = 1<<20;
	int mincnt = 987654321;
	for(int state=0; state<ilim; ++state){
		int res = try_solve(state);
		if(res != -1)
			mincnt = min(mincnt,res);
	}

	if(mincnt == 987654321)
		printf("-1\n");
	else
		printf("%d\n",mincnt);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}