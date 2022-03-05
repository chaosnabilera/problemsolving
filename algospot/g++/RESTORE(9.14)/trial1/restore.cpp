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

int C, K;

string rawinput[15];
string iLine[15];

string dp[15][32768];

string& rec_solve(int front, int available){
	if(dp[front][available].size() > 0)
		return dp[front][available];

	int min_combined_len = 0xFFFF;

	for(int nxt=0; nxt<K; ++nxt){
		if((available & (1<<nxt)) == 0)
			continue;

		string& s1 = iLine[front];
		string& s2 = rec_solve(nxt, available ^ (1<<nxt));

		char combined[1000];
		int combined_len;
		bool matched;
		int match_lim;
		int match_beg = s1.size();
		
		memset(combined, 0, s1.size()+s2.size()+1);

		for(int s=0; s<s1.size(); ++s){
			matched = true;
			match_lim = min(s1.size()-s, s2.size());
			for(int i=0; i<match_lim; ++i){
				if(s1[s+i] != s2[i]){
					matched = false;
					break;
				}
			}
			if(matched){
				match_beg = s;
				break;
			}
		}

		for(int i=0; i < s1.size(); ++i)
			combined[i] = s1[i];
		for(int i=0; i < s2.size(); ++i)
			combined[match_beg + i] = s2[i];

		combined_len = strlen(combined);

		if(combined_len < min_combined_len){
			dp[front][available] = combined;
			min_combined_len = combined_len;
		}
	}

	return dp[front][available];
} 

bool compare_length(string& a, string& b){
	return a.size() > b.size();
}

// sf.size() >= sb.size()
bool contains(string& sf, string& sb){
	int ilim = sf.size()-sb.size();
	bool contain;
	for(int s=0; s<=ilim; ++s){
		contain = true;
		for(int i=0; i<sb.size(); ++i){
			if(sf[s+i] != sb[i]){
				contain = false;
				break;
			}
		}
		if(contain)
			return true;
	}
	return false;
}

void precompute(){
	int nK = 0;
	sort(&rawinput[0],&rawinput[K], compare_length);

	bool taken[15] = { 0 };

	for(int i=0; i<K; ++i){
		if(taken[i])
			continue;
		for(int j=i+1; j<K; ++j)
			if(contains(rawinput[i],rawinput[j]))
				taken[j] = true;
	}

	for(int i=0; i<K; ++i){
		if(taken[i])
			continue;
		iLine[nK++] = rawinput[i];
	}
	K = nK;
}

void solve(){
	int all_mask = (1<<K)-1;

	// clear dp table
	for(int i=0; i<K; ++i)
		for(int j=1; j<(1<<K); ++j)
			dp[i][j].clear();

	// construct base case
	for(int i=0; i<K; ++i)
		dp[i][0] = iLine[i];

	// solve
	for(int i=0; i<K; ++i)
		rec_solve(i, all_mask ^ (1<<i));

	// for(int i=0; i<K; ++i){
	// 	printf("%d: %s\n", i, dp[i][all_mask ^ (1<<i)].c_str());
	// }

	// get shortest
	string* shortest = &dp[0][all_mask ^ 1];
	for(int i=1; i<K; ++i){
		if(dp[i][all_mask ^ (1<<i)].size() < shortest->size())
			shortest = &dp[i][all_mask ^ (1<<i)];
	}

	printf("%s\n",shortest->c_str());
}

void get_input(){
	char iarr[41];
	scanf("%d", &K);
	for(int i=0; i<K; ++i){
		scanf("%s", iarr);
		rawinput[i] = iarr;
	}
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		get_input();
		precompute();
		solve();
	}
}