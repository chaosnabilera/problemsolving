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

const int BIGNUM = 987654321;

int N,M;
map<string,int> NameToIdx;
vector<int> iFood[50];

vector<int> CanEat[50];       // list of food person i can eat
unsigned long long bEdible[50]; // list of people who can eat food i as bitmask

unsigned long long EVERYONE;
int GlobalMinCnt;

void get_input(){
	int num_person;
	string iname;

	NameToIdx.clear();

	scanf("%d %d", &N, &M);
	for(int i=0; i<N; ++i){
		cin >> iname;
		NameToIdx[iname] = i;
	}

	for(int i=0; i<M; ++i){
		iFood[i].clear();
		scanf("%d", &num_person);
		for(int j=0; j<num_person; ++j){
			cin >> iname;
			iFood[i].push_back(NameToIdx[iname]);
		}
	}
}

void preprocess(){
	for(int i=0; i<N; ++i)
		CanEat[i].clear();

	for(int i=0; i<M; ++i){
		bEdible[i] = 0;
		for(int p:iFood[i]){
			bEdible[i] |= (1ULL<<p);
			CanEat[p].push_back(i);
		}
	}
}

int rec_solve(unsigned long long pi, int already, unsigned long long food_taken, unsigned long long person_taken){
	if(person_taken == EVERYONE)
		return 0;

	if(already >= GlobalMinCnt)
		return BIGNUM;

	if((1ULL<<pi) & person_taken)
		return rec_solve(pi+1, already, food_taken, person_taken);

	int min_cnt = BIGNUM;

	for(int fi:CanEat[pi]){
		if((1ULL<<fi) & food_taken)
			continue;
		min_cnt = min(min_cnt, 1+rec_solve(pi+1, already+1, 
			(food_taken | (1ULL<<fi)) , (person_taken | bEdible[fi]) ));
		GlobalMinCnt = min(GlobalMinCnt, already+min_cnt);
	}

	return min_cnt;
}

string to_bin_str(unsigned long long bm, int n){
	string ret;
	for(int i=n-1; i>=0; --i){
		if(bm & (1ULL<<i))
			ret += "1";
		else
			ret += "0";
	}
	return ret;
}

void solve(){
	EVERYONE = (1ULL<<N)-1;
	GlobalMinCnt = BIGNUM;

	// printf("%d %d\n",N,M);
	// cout << to_bin_str(EVERYONE, N) << endl;

	printf("%d\n", rec_solve(0,0,0,0));
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		preprocess();
		solve();
	}
}