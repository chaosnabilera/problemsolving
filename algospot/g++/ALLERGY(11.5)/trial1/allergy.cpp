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

int N,M;
map<string, int> name_to_num;
map<int, string> num_to_name;
vector<int> eaters[50];   // list of people who can eat eaters[i]
vector<int> canEat[50];   // list of food canEat[i] can eat
int best;

void get_input(){
	int num_person;
	int p;
	string nm;

	scanf("%d %d",&N,&M);
	
	name_to_num.clear();
	num_to_name.clear();
	for(int i=0; i<N; ++i){
		cin >> nm;
		name_to_num[nm] = i;
		num_to_name[i] = nm;
		canEat[i].clear();
	}

	for(int i=0; i<M; ++i){
		eaters[i].clear();
		scanf("%d", &num_person);
		for(int j=0; j<num_person; ++j){
			cin >> nm;
			p = name_to_num[nm];
			eaters[i].push_back(p);
			canEat[p].push_back(i);
		}
	}
}

void search(vector<int>& edible, int chosen){
	if(chosen >= best)
		return;
	int first = 0;
	while(first < N && edible[first] > 0) 
		++first;
	if(first == N){
		best = chosen; 
		return;
	}
	for(int i=0; i<canEat[first].size(); ++i){
		int food = canEat[first][i];
		for(int j=0; j<eaters[food].size(); ++j)
			edible[eaters[food][j]]++;
		search(edible, chosen+1);
		for(int j=0; j<eaters[food].size(); ++j)
			edible[eaters[food][j]]--;
	}
}

void solve(){
	vector<int> edible(N,0);
	best = 987654321;
	search(edible, 0);
	printf("%d\n", best);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}