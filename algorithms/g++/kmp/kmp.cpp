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
			if(match == needle_len)
				out_idx.push_back(beg);
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

int main(int argc, char** argv){
	char h[] = "abcdefababcabcabcjkghijkzzzabcdefabcabcabcjkdefgabcdabcabcabcj";
	char n[] = "abcabcabcjk";

	int hlen = strlen(h);
	int nlen = strlen(n);

	std::vector<char> haystack(&h[0],&h[hlen-1]);
	std::vector<char> needle(&n[0],&n[nlen-1]);
	std::vector<size_t> result;

	kmp_search(haystack, needle, result);

	for (auto it: result){
		printf("%lu ", it);
	}
	printf("\n");

	return 0;
}