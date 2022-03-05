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
vector<int> iFood[50];   // list of people who can eat iFood[i]
vector<int> iPerson[50]; // list of food iPerson[i] can eat

unsigned long long FoodMask[50];
int GlobalMax;
int PersonFoodCount[50];

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
		iPerson[i].clear();
	}

	for(int i=0; i<M; ++i){
		iFood[i].clear();
		scanf("%d", &num_person);
		for(int j=0; j<num_person; ++j){
			cin >> nm;
			p = name_to_num[nm];
			iFood[i].push_back(p);
			// iPerson[p].push_back(i);
		}
	}
}

void preprocess(){
	pair<int, unsigned long long> foodmask[50];
	bool is_necessary[50];
	int num_nec_food;
	unsigned long long nec_food[50];

	for(int i=0; i<M; ++i){
		foodmask[i].first = iFood[i].size();
		foodmask[i].second = 0;
		for(auto p:iFood[i])
			foodmask[i].second |= (1<<p);
	}

	sort(&foodmask[0],&foodmask[M]);

	for(int i=0; i<M; ++i){
		is_necessary[i] = true;
		for(int j=i+1; j<M; ++j)
			if((foodmask[i].second & foodmask[j].second) == foodmask[i].second){
				is_necessary[i] = false;
				break;
			}
	}

	num_nec_food = 0;
	for(int i=0; i<M; ++i){
		if(is_necessary[i]){
			nec_food[num_nec_food] = foodmask[i].second;
			++num_nec_food;
		}
	}

	M = num_nec_food;
	for(int i=0; i<M; ++i){
		FoodMask[i] = nec_food[i];
		iFood[i].clear();
		for(int j=0; j<N; ++j){
			if(nec_food[i] & (1<<j)){
				iFood[i].push_back(j);
				iPerson[j].push_back(i);
			}
		}
	}
}

void print_bit(unsigned long long v){
	for(int i=63; i>=0; --i){
		if(v&((unsigned long long)1<<i))
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}

void print_pfc(){
	for(int i=0; i<N; ++i)
		printf("%d ", PersonFoodCount[i]);
	printf("\n");
}

int rec_solve(unsigned long long state, int already, int cur){
	int max_take = 0;

	print_bit(state);
	printf("already: %d  cur: %d\n", already, cur);
	print_pfc();
	print_bit(FoodMask[cur]);
	printf("\n");

	// base case;
	if(state == 0)
		return M-cur;

	if(already+(M-cur) < GlobalMax)
		return 0;

	// can remove cur?
	bool can_remove = true;
	for(int p:iFood[cur]){
		if(PersonFoodCount[p] == 1){
			can_remove = false;
			break;
		}
	}

	if(can_remove){
		// printf("can_remove %d\n",cur);
		for(int p:iFood[cur])
			--PersonFoodCount[p];

		max_take = max(max_take, 1+rec_solve(state, already+1, cur+1));
		GlobalMax = max(GlobalMax, already+max_take);
		
		for(int p:iFood[cur])
			++PersonFoodCount[p];
	}

	// printf("dont' remove %d\n",cur);
	max_take  = max(max_take, rec_solve(state & (~FoodMask[cur]), already, cur+1));
	GlobalMax = max(GlobalMax, already+max_take);

	return max_take;
}

void solve(){
	printf("M:%d\n",M);
	for(int i=0; i<M; ++i)
		print_bit(FoodMask[i]);

	// printf("NAND:\n");
	// for(int i=0; i<M; ++i)
	// 	print_bit(~FoodMask[i]);

	// for(int i=0; i<N; ++i){
	// 	printf("%d: ",i);
	// 	for(int f:iPerson[i])
	// 		printf("%d ", f);
	// 	printf("\n");
	// }

	GlobalMax = 0;
	for(int i=0; i<N; ++i){
		PersonFoodCount[i] = iPerson[i].size();
	}
	unsigned long long state = (1<<N)-1;
	rec_solve(state, 0, 0);

	printf("%d\n", M-GlobalMax);
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