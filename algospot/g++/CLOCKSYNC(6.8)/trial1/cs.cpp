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

int C;

const int INF = 987654321;
const int LIMIT = (1<<20);
const int switch_len[10] = {3,4,4,5,5,4,3,5,5,5};
const int cswitch[10][5] = {
	{0,1,2,-1,-1},
	{3,7,9,11,-1},
	{4,10,14,15,-1},
	{0,4,5,6,7},
	{6,7,8,10,12},
	{0,2,14,15,-1},
	{3,14,15,-1,-1},
	{4,5,7,14,15},
	{1,2,3,4,5},
	{3,4,5,9,13}
};

int clock_pos[16];

// void test_print(){
// 	for(int cs=0; cs<10; ++cs){
// 		printf("%d: ", cs);
// 		for(int i=0; i<switch_len[cs]; ++i){
// 			printf("%d ", cswitch[cs][i]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");
// }

void print_clock(){
	for(int i=0; i<16; ++i){
		printf("%d ", clock_pos[i]*3);
	}
	printf("\n");
}

int test(int curclock[], int arg){
	int move_cnt = 0;

	// printf("%d\n", arg);
	for(int cs=0; cs<10; ++cs){
		int cur = (arg & 3);
		for(int i=0; i<switch_len[cs]; ++i){
			curclock[cswitch[cs][i]] += cur;
		}
		move_cnt += cur;
		arg >>= 2;
	}

	// print_clock();

	for(int i=0; i<16; ++i){
		if((curclock[i] & 3) != 0){
			return INF;
		}
	}
	// printf("move_cnt: %d\n",move_cnt);
	return move_cnt;
}

int solve(){
	int res = INF;
	int curclock[16];
	for(int arg=0; arg<LIMIT; ++arg){
		memcpy(curclock,clock_pos,sizeof(clock_pos));
		res = min(res, test(curclock, arg));
	}

	if(res == INF){
		return -1;
	}
	else{
		return res;
	}
}

int main(int argc, char** argv){
	scanf("%d", &C);
	//test_print();
	for(int i=0; i<C; ++i){
		for(int j=0; j<16; ++j){
			scanf("%d", &clock_pos[j]);
			clock_pos[j] /= 3;
		}
		// print_clock();
		printf("%d\n", solve());
	}
}