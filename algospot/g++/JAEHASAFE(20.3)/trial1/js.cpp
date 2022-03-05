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

int N;
char iLine[101][10001];
int iLineLen[101];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<=N; ++i){
		scanf("%s", iLine[i]);
		iLineLen[i] = strlen(iLine[i]);
	}
}

void compute_failure_function(char* needle, int len, int* res){
	res[0] = 0;
	for(int i=1; i<len; ++i){
		int prev = i-1;

		res[i] = -1;
		while(prev > 0 && res[prev] > 0){
			if(needle[res[prev]] == needle[i]){
				res[i] = res[prev]+1;
				break;
			}
			prev = res[prev]-1;
		}
		if(res[i] < 0){
			res[i] = (needle[i] == needle[0]) ? 1 : 0;
		}
	}
}

int kmp_search(char* haystack, int hlen, char* needle, int nlen){
	int sufpref[10001];
	int idx;
	int ilim = hlen-nlen+1;

	compute_failure_function(needle, nlen, sufpref);

	// printf("haystack: %s\n", haystack);
	// printf("needle: %s\n", needle);

	// for(int i=0; i<nlen; ++i){
	// 	printf("%d ",sufpref[i]);
	// }
	// printf("\n");

	idx = 0;
	int nummatch = 0;
	while(idx<ilim){
		// printf("%d %d\n",idx,nummatch);
		while(nummatch<nlen){
			if(haystack[idx+nummatch] != needle[nummatch])
				break;
			++nummatch;
		}
		if(nummatch == nlen){
			break;
		}

		if(nummatch > 1){
			idx = idx + nummatch - sufpref[nummatch-1];
			nummatch = sufpref[nummatch-1];
		}
		else{
			++idx;
			nummatch = 0;
		}
	}

	// printf("result: %d\n",i);

	if(idx >= ilim)
		return -1;
	else
		return idx;
}

int ccw_count(int haystack_idx, int needle_idx){
	char haystack[20001];
	int hsrc_len = iLineLen[haystack_idx];
	int hlen = hsrc_len*2;
	int nlen = iLineLen[needle_idx];

	memcpy(haystack, iLine[haystack_idx], hsrc_len);
	memcpy(haystack+hsrc_len, iLine[haystack_idx], hsrc_len);
	haystack[hlen] = 0;

	return kmp_search(haystack,hlen,iLine[needle_idx],nlen);
}

void solve(){
	int cnt = 0;
	for(int i=1; i<=N; ++i){
		if(i&1){
			cnt += ccw_count(i, i-1);
		}
		else{
			cnt += ccw_count(i-1, i);
		}
	}
	printf("%d\n", cnt);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}