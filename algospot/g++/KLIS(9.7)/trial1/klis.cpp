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

int C,N;
long long K;
int iNum[500];

vector<int> gt_idx[500]; // index of elements that are greater than ith element
double NIS[500][501]; // NIS[i][n] = Number of Increasing Sequence of Length n starting from i

void solve(){
	for(int i=0; i<N; ++i)
		gt_idx[i].clear();

	for(int i=0; i<N-1; ++i){
		for(int j=i+1; j<N; ++j){
			if(iNum[i] < iNum[j])
				gt_idx[i].push_back(j);
		}
	}

	for(int i=0; i<N; ++i){
		NIS[i][1] = 1;
		NIS[i][0] = 0;
	}
	for(int i=0; i<N; ++i)
		for(int n=2; n<N; ++n)
			NIS[i][n] = 0;

	int lis = 1;
	bool updated = true;
	while(updated){
		updated = false;
		for(int i=0; i<N; ++i){
			for(int j:gt_idx[i]){
				NIS[i][lis+1] += NIS[j][lis];
			}
			if(NIS[i][lis+1] > 0)
				updated = true;
		}
		if(updated)
			++lis;
	}

	int curlen = lis;
	long long curcnt = K;
	int leftlim = -1;
	int vallim = -1;
	vector<int> ans;

	while(curlen){
		vector<pair<int,int>> cand;
		for(int i=leftlim+1; i<N; ++i){
			if(iNum[i] > vallim && NIS[i][curlen] > 0)
				cand.push_back(make_pair(iNum[i],i));
		}

		sort(cand.begin(), cand.end());
		for(auto cp:cand){
			int val = cp.first;
			int idx = cp.second;

			if(NIS[idx][curlen] < curcnt){
				curcnt -= NIS[idx][curlen];
			}
			else{
				leftlim = idx;
				vallim = val;
				--curlen;
				ans.push_back(val);
				break;
			}
		}
	}

	printf("%d\n", lis);
	for(int v:ans)
		printf("%d ", v);
	printf("\n");
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d %lld", &N, &K);
		for(int j=0; j<N; ++j){
			scanf("%d", &iNum[j]);
		}
		solve();
	}
}