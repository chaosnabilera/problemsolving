#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int N, Len;
char Buf1[10001];
char Buf2[10001];
char* Cur;
char* Nxt;

template <typename T>
void kmp_search(vector<T>& haystack, vector<T>& needle, vector<size_t>& out_idx){
	std::vector<size_t> needle_kmp;
	size_t beg, match;
	size_t haystack_len = haystack.size(); size_t needle_len = needle.size();

	// get suffix-prefix match of needle
	needle_kmp.resize(needle_len, 0);
	beg = 1; match = 0;
	needle_kmp[0] = 0;
	while(beg + match < needle_len){
		if(needle[beg+match] == needle[match]){
			needle_kmp[beg+match] = match+1; ++match;
		}
		else{
			if(match == 0){	++beg; }
			else{
				beg = beg + match - needle_kmp[match-1]; //-1 because of 0-index
				match = needle_kmp[match-1];
			}
		}
	}

	// match haystack with needle
	beg = 0; match = 0;
	while(beg <= haystack_len - needle_len){
		if(match < needle_len && haystack[beg+match] == needle[match]){
			++match;
			if(match == needle_len){
				out_idx.push_back(beg);
				return;
			}
		}
		else{
			if(match == 0){ ++beg; }
			else{
				beg = beg+match-needle_kmp[match-1];
				match = needle_kmp[match-1];
			}
		}
	}
}

int solve(bool clockwise);

void get_input_and_solve(){
	int cnt = 0;
	Cur = Buf1;
	Nxt = Buf2;
	
	scanf("%d", &N);
	scanf("%s", Cur);
	Len = strlen(Cur);
	for(int i=0; i<N; ++i){
		scanf("%s", Nxt);
		cnt += solve((i&1) == 0);
		swap(Cur,Nxt);
	}

	printf("%d\n", cnt);
}

int solve(bool clockwise){
	vector<char> haystack(Len*2);
	vector<char> needle(Len);
	vector<size_t> result;

	if(clockwise){
		memcpy(&haystack[0], Nxt, Len);
		memcpy(&haystack[Len], Nxt, Len);
		memcpy(&needle[0], Cur, Len);
	}
	else{
		memcpy(&haystack[0], Cur, Len);
		memcpy(&haystack[Len],Cur, Len);
		memcpy(&needle[0], Nxt, Len);
	}

	kmp_search(haystack, needle, result);

	return result[0];
}

int main(int argc, char** argv){
	int t;
	scanf("%d", &t);
	for(int i=0; i<t; ++i){
		get_input_and_solve();
	}
}