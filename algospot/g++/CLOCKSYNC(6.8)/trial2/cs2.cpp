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

bool try_solve(int* scnt){
	int curstate[16];
	int scntsum = 0;
	int sumstate = 0;

	memcpy(curstate,State,sizeof(State));

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

	return (sumstate == 0);
}

bool rec_try(int* scnt, int s, int left){
	// printf("%d %d\n",s,left);
	if(s == 10){
		if(left > 0)
			return false;
		return try_solve(scnt);
	}

	if(left > ((10-s)*4)){
		return false;
	}

	int ilim = min(3, left);

	for(int i=0; i <= ilim; ++i){
		scnt[s] = i;
		if(rec_try(scnt, s+1, left-i))
			return true;
	}

	return false;
}

void solve(){
	int scnt[10];
	int leftlim = 4*10;
	int mincnt = -1;

	for(int left=0; left <= leftlim; ++left){
		memset(scnt,0,sizeof(scnt));
		if(rec_try(scnt,0,left)){
			printf("%d\n",left);
			return;
		}
	}

	printf("-1\n");
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}