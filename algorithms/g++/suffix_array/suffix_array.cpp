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

struct SuffixArrayComparator{
	SuffixArrayComparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
	bool operator()(int idx1, int idx2){
		// 여기에서 group은 이미 t글자 기준으로 정렬되어 있다
		// 즉 길이가 t글자 보다 작은 suffix에 대해서는 group[idx1]과 group[idx2]의 대소관계가 정해져 있다
		// 따라서 group[idx+t] 로 가지 않는다 
		if(group[idx1] != group[idx2]) return group[idx1] < group[idx2];
		return group[idx1+t] < group[idx2+t];
	}
	const vector<int>& group;
	int t;
};

// note that this this function is bound to int, so maximum group size should be that of int
template <typename T>
void get_suffix_array(vector<T>& iarr, vector<int>& suffix_order){
	size_t n = iarr.size();
	size_t t = 1;

	vector<int> group1(n+1);
	vector<int> group2(n+1);

	for(int i=0; i<n; ++i)
		group1[i] = iarr[i]; // shouldn't use memcopy, since T and int can be different type
	group1[n] = -1;

	suffix_order.clear();
	suffix_order.resize(n);
	for(int i=0; i<n; ++i)
		suffix_order[i] = i;

	vector<int>* pcurgrp = &group1;
	vector<int>* pnxtgrp = &group2;

	while(t < n){
		vector<int>& curgrp = *pcurgrp;

		SuffixArrayComparator cmp_2t(curgrp, t);
		sort(suffix_order.begin(), suffix_order.end(), cmp_2t);

		if((t*2) >= n)
			break;
		t *= 2;

		vector<int>& nxtgrp = *pnxtgrp;
		nxtgrp[n] = -1;
		nxtgrp[suffix_order[0]] = 0;
		for(int i=1; i<n; ++i){
			if(cmp_2t(suffix_order[i-1], suffix_order[i])){
				nxtgrp[suffix_order[i]] = nxtgrp[suffix_order[i-1]]+1;
			}
			else{
				nxtgrp[suffix_order[i]] = nxtgrp[suffix_order[i-1]];
			}
		}

		swap(pcurgrp, pnxtgrp);
	}
}

int main(int argc, char** argv){
	string sample = "uhmhellouhmmynameislibe";

	vector<char> iarr(sample.begin(),sample.end());
	vector<int> suffixarray;

	get_suffix_array(iarr, suffixarray);

	for(auto i:suffixarray){
		printf("%s\n", &sample[i]);
	}

	return 0;
}