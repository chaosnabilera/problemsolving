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

const int INF = 987654321;

int N, M;
char Name[50][0x10];
map<string, int> NameToIdx;
vector<int> Food[50];
vector<int> Person[50];

unsigned long long FoodMask[50];

int GMinCnt;

void print_bit(unsigned long long v, int bitlen){
	for(int i=bitlen-1; i>=0; --i){
		if(v & (1ULL<<i))
			printf("1");
		else
			printf("0");
	}
	// printf("\n");
}

void get_input(){
	char word[0x10];
	int f, p;

	NameToIdx.clear();
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; ++i){
		scanf("%s", Name[i]);
		NameToIdx[Name[i]] = i;
		Person[i].clear();
	}

	for(int i=0; i<M; ++i){
		Food[i].clear();
		FoodMask[i] = 0xFFFFFFFFFFFFFFFF;

		scanf("%d", &f);
		for(int j=0; j<f; ++j){
			scanf("%s", word);
			p = NameToIdx[word];
			Food[i].push_back(p);
			Person[p].push_back(i);
			FoodMask[i] ^= (1ULL<<p);
		}

		// printf("FoodMask[%d]: ",i);
		// print_bit(FoodMask[i], N);
		// printf("\n");
	}
}



int rec_solve(int already, unsigned long long people, unsigned long long food){
	// print_bit(people, N);
	// printf(" ");
	// print_bit(food, M);
	// printf("\n");

	if(people == 0ULL)
		return 0;

	if(already >= GMinCnt)
		return INF;

	int cnt = INF;

	for(int p=0; p<N; ++p){
		if(people & (1ULL<<p)){
			for(int f:Person[p]){
				if(food & (1ULL<<f)){
					cnt = min(cnt, 1 + rec_solve(already+1, people & FoodMask[f], food ^ (1ULL << f)));
					GMinCnt = min(GMinCnt, already+cnt);
				}
			}
			break;
		}
	}

	return cnt;
}

void solve(){
	GMinCnt = INF;
	printf("%d\n", rec_solve(0, (1ULL<<N)-1, (1ULL<<M)-1));
}

int main(int argc, char** argv){
	int t;
	scanf("%d", &t);
	for(int i=0; i<t; ++i){
		get_input();
		solve();
	}
}