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

const int BIGNUM = 987654321;

int K;
string iLine[15];
string DP[(1<<15)];
bool Visited[(1<<15)];

void get_input(){
	char line[0x100];

	scanf("%d", &K);
	for(int i=0; i<K; ++i){
		scanf("%s", line);
		iLine[i] = line;
	}
}

string* rec_solve(int bitmask){
	char combined[0x300];
	int combined_len = 0x300;

	if(Visited[bitmask])
		return &DP[bitmask];

	for(int b=0; b<K; ++b){
		if(!(bitmask & (1<<b)))
			continue;

		string* pstr1 = &iLine[b];
		string* pstr2 = rec_solve(bitmask ^ (1<<b));
		
		if(pstr1->size() > pstr2->size())
			swap(pstr1,pstr2);

		string& str1 = *pstr1;
		string& str2 = *pstr2;

		// printf("%d str1:%s str2:%s\n", bitmask, str1.c_str(),str2.c_str());

		int ilim, jlim;
		bool match;
		int match_idx;

		// 1. str1 is part of str2 (best case)
		ilim = str2.size()-str1.size()+1;
		jlim = str1.size();
		match = false;
		for(int i=0; i<ilim && !match; ++i){
			match = true;
			for(int j=0; j<jlim; ++j){
				if(str1[j] != str2[i+j]){
					match = false;
					break;
				}
			}
		}
		if(match && str2.size() < combined_len){
			strcpy(combined, str2.c_str());
			combined_len = str2.size();
			continue;
		}

		// str1 is prefix of str2
		match = false;
		match_idx = BIGNUM;
		for(int i=1; i<str1.size() && !match; ++i){
			match = true;
			match_idx = i;
			for(int j=i; j<str1.size(); ++j){
				if(str1[j] != str2[j-i]){
					match = false;
					break;
				}
			}
		}
		// printf("%d match:%d\n",bitmask,match);
		if(match && (match_idx+str2.size()) < combined_len){
			for(int i=0; i<match_idx; ++i)
				combined[i] = str1[i];
			strcpy(&combined[match_idx], str2.c_str());
			combined_len = match_idx+str2.size();
		}

		// str1 is suffix of str2
		match = false;
		match_idx = BIGNUM;
		for(int i=str2.size()-str1.size()+1; i<str2.size() && !match; ++i){
			match = true;
			match_idx = i;
			for(int j=i; j<str2.size(); ++j){
				if(str2[j] != str1[j-i]){
					match = false;
					break;
				}
			}
		}
		if(match && (match_idx+str1.size()) < combined_len){
			for(int i=0; i<match_idx; ++i)
				combined[i] = str2[i];
			strcpy(&combined[match_idx], str1.c_str());
			combined_len = match_idx+str1.size();
		}

		// just do str1 + str2
		if(!match && (str1.size()+str2.size()) < combined_len){
			strcpy(combined,str1.c_str());
			strcpy(&combined[str1.size()],str2.c_str());
			combined_len = str1.size()+str2.size();
		}
	}

	Visited[bitmask] = true;
	DP[bitmask] = combined;

	// printf("%d %s\n", bitmask, DP[bitmask].c_str());

	return &DP[bitmask];
}

void solve(){
	memset(Visited,0,sizeof(Visited));

	// base case
	Visited[0] = true;
	DP[0] = "";
	printf("%s\n", rec_solve((1<<K)-1)->c_str());
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}