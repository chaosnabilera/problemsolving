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

#define MAXLEN 4000

int K;
char iLine[MAXLEN+1];
int iLineLen;

class Compare2T{
public:
	Compare2T(int* _groupno) : t(1), groupno(_groupno) {}
	bool operator()(int a, int b){
		if(groupno[a] == groupno[b]){
			return groupno[a+t] < groupno[b+t];
		}
		return groupno[a] < groupno[b];
	}
	int t;
	int* groupno;
};

void compute_suffix_array(char* text, int len, int* result){
	int indices[MAXLEN];
	int buf1[MAXLEN+1];
	int buf2[MAXLEN+1];

	int* groupno = buf1;
	int* nextgno = buf2;

	buf1[len] = -1;
	buf2[len] = -1;

	Compare2T cmp2t(groupno);

	for(int i=0; i<len; ++i)
		groupno[i] = text[i];

	for(int t=1; t < len; t *= 2){
		cmp2t.t = t;
		for(int i=0; i<len; ++i)
			indices[i] = i;

		sort(&indices[0], &indices[len], cmp2t);

		nextgno[indices[0]] = 0;
		for(int i=1; i<len; ++i){
			nextgno[indices[i]] = nextgno[indices[i-1]];
			if(cmp2t(indices[i-1],indices[i])){
				++nextgno[indices[i]];
			}
		}
		cmp2t.groupno = nextgno;
		swap(groupno, nextgno);
	}

	memcpy(result, cmp2t.groupno, sizeof(int)*len);
}

int len_common_prefix(char* text, int textlen, int suf1, int suf2){
	int res = 0;
	for(int i=0; (suf1+i < textlen) && (suf2 + i < textlen); ++i){
		if(text[suf1+i] != text[suf2+i])
			break;
		++res;
	}
	return res;
}

void solve(){
	int suffix_array[MAXLEN];
	int rev_array[MAXLEN];

	compute_suffix_array(iLine, iLineLen, suffix_array);

	for(int i=0; i<iLineLen; ++i)
		rev_array[suffix_array[i]] = i;

	// for(int i=0; i<iLineLen; ++i)
	// 	printf("%s\n", &iLine[rev_array[i]]);

	int i = 0;
	int ilim = iLineLen - K + 1;
	int maxlen = 0;

	while(i < ilim){
		int suf1 = rev_array[i];
		int suf2 = rev_array[i+K-1];
		int lcp = len_common_prefix(iLine, iLineLen, suf1, suf2);

		// printf("%d: %s %s %d\n", i, &iLine[suf1], &iLine[suf2], lcp);

		maxlen = max(maxlen, lcp);
		++i;

		// if(lcp > 0){
		// 	int add = 0;
		// 	while((suf1+lcp+add) < iLineLen && (suf2+lcp+add) < iLineLen && iLine[suf1+lcp+add] == iLine[suf2+lcp+add])
		// 		++add;
		// 	maxlen = max(maxlen, lcp+add);
		// 	i = i+K+add;
		// }
		// else{
		// 	++i;
		// }
	}

	printf("%d\n", maxlen);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		scanf("%d", &K);
		scanf("%s", iLine);
		iLineLen = strlen(iLine);

		solve();
	}
}