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

int T,M;
int A[500];
int B[500];
int mindist[400];
bool visited[400];

void solve(){
	std::priority_queue<
		std::pair<int, int>,
		std::vector<std::pair<int, unsigned int>>,
		std::greater<std::pair<int, unsigned int>>
	> minq;

	memset(visited, 0, sizeof(visited));
	for(int i=0; i<400; ++i){
		mindist[i] = std::numeric_limits<int>::max();
	}

	for(int i=0; i<M; ++i){
		unsigned int d = A[i]-B[i]+200;
		minq.push(std::make_pair(A[i],d));
	}

	while(!minq.empty()){
		auto cp = minq.top(); minq.pop();
		int w = cp.first;
		int d = cp.second;

		if(visited[d]){
			continue;
		}

		visited[d] = true;
		mindist[d] = w;

		if(d == 200){
			break;
		}

		for(int i=0; i<M; ++i){
			int nd = d+(A[i]-B[i]);
			if(nd >= 1 && nd < 400 && !visited[nd]){
				minq.push(std::make_pair(mindist[d]+A[i],nd));	
			}
		}
	}

	printf("%d\n", mindist[200]);
}

int main(int argc, char** argv){
	int a,b;
	int cnt_pos, cnt_neg;
	scanf("%d", &T);
	for(int t=0; t<T; ++t){
		scanf("%d", &M);
		for(int i=0; i<M; ++i){
			scanf("%d %d", &A[i], &B[i]);
		}
		//check sanity
		cnt_pos = 0;
		cnt_neg = 0;
		for(int i=0; i<M; ++i){
			if(A[i]-B[i] > 0){
				cnt_pos++;
			}
			else if(A[i]-B[i] < 0){
				cnt_neg++;
			}
		}

		if(cnt_pos == M || cnt_neg == M){
			printf("IMPOSSIBLE\n");
		}
		else{
			solve();
		}
	}
}