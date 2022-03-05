#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

struct SuffixArrayComparatorS32{
	const std::vector<int>& group;
	int t;
	SuffixArrayComparatorS32(const std::vector<int>& _group, int _t) : group(_group), t(_t) {}
	bool operator()(int idx1, int idx2){
		// 여기에서 group은 이미 t글자 기준으로 정렬되어 있다
		// 즉 길이가 t글자 보다 작은 suffix에 대해서는 group[idx1]과 group[idx2]의 대소관계가 정해져 있다
		// 따라서 group[idx+t] 로 가지 않는다 
		if(group[idx1] != group[idx2]) return group[idx1] < group[idx2];
		return group[idx1+t] < group[idx2+t];
	}
};

template <typename T>
std::vector<int>* get_suffix_array_s32(std::vector<T> iarr){
	unsigned int N = iarr.size();
	unsigned int t = 1;

	//we will use these 2 only
	std::vector<int> group1(N+1);
	std::vector<int> group2(N+1);
	for(int i=0; i<N; ++i) {group1[i] = iarr[i];}
	group1[N] = -1;

	std::vector<int>* psuffixord = new std::vector<int>(N);
	std::vector<int>& suffix_order = *psuffixord;
	for(int i=0; i<N; ++i) {suffix_order[i]= i;}

	std::vector<int>* pcurgrp = &group1;
	std::vector<int>* pnextgrp = &group2;

	while(t < N){
		std::vector<int>& curgrp = *pcurgrp;

		SuffixArrayComparatorS32 cmp_2t(curgrp, t);
		std::sort(suffix_order.begin(), suffix_order.end(), cmp_2t);

		if((2*t) >= N) break;
		t *= 2;

		std::vector<int>& nextgrp = *pnextgrp;
		nextgrp[N] = -1;
		nextgrp[suffix_order[0]] = 0;
		for(int i=1; i<N; ++i){
			if(cmp_2t(suffix_order[i-1],suffix_order[i])){
				nextgrp[suffix_order[i]] = nextgrp[suffix_order[i-1]]+1;
			}
			else{
				nextgrp[suffix_order[i]] = nextgrp[suffix_order[i-1]];
			}
		}
		std::swap<std::vector<int>*>(pcurgrp,pnextgrp);
	}

	return psuffixord;
}

int common_prefix(int i, int j, char* istr, int istrlen){
	int cplen = 0;
	while((i<istrlen) && (j<istrlen) && (istr[i] == istr[j])){
		++cplen; ++i; ++j;
	}
	return cplen;
}

void solve(int K, char* istr){
	int N = strlen(istr);
	std::vector<char> iarr(&istr[0],&istr[N]);
	std::vector<int>* psufarr = get_suffix_array_s32<char>(iarr);
	std::vector<int>& suffix_array = *psufarr;

	int maxklen = 0;

	for(int i=0; i<=N-K; ++i){
		maxklen = std::max(maxklen, common_prefix(suffix_array[i],suffix_array[i+K-1],istr,N));
	}
	printf("%d\n",maxklen);

	delete psufarr;
}

int main(int argc, char** argv){
	int C,K;
	char istr[4001];

	scanf("%d",&C);
	for(int c=0; c<C; ++c){
		scanf("%d",&K);
		scanf("%s",istr);
		solve(K,istr);
	}
}