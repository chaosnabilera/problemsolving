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
unsigned long long Target;

const unsigned long long Filter = (1<<12)-1;

// 0 : left most
// 3 : right most
unsigned long long Bit[4][12];

void get_input(){
	int n,x;

	Target = 0;
	scanf("%d", &N);
	for(int i=0; i<4; ++i){
		scanf("%d", &n);
		for(int j=0; j<n; ++j){
			scanf("%d", &x);
			Target |= 1ULL << ((12*i)+(x-1));
		}
	}
}

unsigned long long move_disk(unsigned long long stat, unsigned long long b, int s, int d){
	unsigned long long bs = b<<(s*12);
	unsigned long long bd = b<<(d*12);
	stat ^= bs;
	stat |= bd;
	return stat;
}

void print_bit(unsigned long long v){
	for(int i=63; i>=0; --i){
		printf("%3d",i);
	}
	printf("\n");
	for(int i=63; i>=0; --i){
		if(v & (1ULL<<i)){
			printf("%3d",1);
		}
		else{
			printf("%3d",0);
		}
	}
	printf("\n");
}

void solve(){
	unsigned long long begin  = 0;
	for(int i=0; i<N; ++i)
		begin |= 1ULL<<(36+i);

	// Special case
	if(begin == Target){
		printf("0\n");
		return;
	}

	unordered_map<unsigned long long, int> v1;
	unordered_map<unsigned long long, int> v2;
	// map<unsigned long long, int> v1;
	// map<unsigned long long, int> v2;

	queue<pair<unsigned long long, int>> q1;
	queue<pair<unsigned long long, int>> q2;

	q1.push(make_pair(begin,0));
	q2.push(make_pair(Target,0));

	int ans = -1;
	// return;

	while(true){
		bool ans_detected = false;

		int cur_p1_topcnt = q1.front().second;

		while(q1.front().second == cur_p1_topcnt){
			auto p1 = q1.front(); q1.pop();
			unsigned long long stat1 = p1.first;
			int cnt1 = p1.second;

			if(v1.find(stat1) == v1.end()){
				v1[stat1] = cnt1;

				if(stat1 == Target){
					printf("%d\n", cnt1);
					return;
				}
				if(v2.find(stat1) != v2.end()){
					if(!ans_detected){
						ans_detected = true;
						ans = v2[stat1] + cnt1;
					}
					else{
						ans = min(ans, v2[stat1] + cnt1);
					}
				}

				unsigned long long l[4] = {0};
				unsigned long long b[4] = {0};
				l[0] = stat1 & Filter;
				l[1] = (stat1 >> 12) & Filter;
				l[2] = (stat1 >> 24) & Filter;
				l[3] = (stat1 >> 36) & Filter;

				for(int i=0; i<4; ++i)
					b[i] = (l[i] == 0) ? 0 : l[i] ^ (l[i] & (l[i]-1));

				for(int i=0; i<4; ++i){
					if(b[i] == 0)
						continue;
					for(int j=0; j<4; ++j){
						if(b[i] < b[j] || b[j] == 0){
							unsigned long long nxt = move_disk(stat1, b[i], i, j); 
							// if(v1.find(nxt) == v1.end())
							q1.push(make_pair(nxt,cnt1+1));
						}
					}
				}
			}
		}

		int cur_p2_topcnt = q2.front().second;
		while(q2.front().second == cur_p2_topcnt){
			auto p2 = q2.front(); q2.pop();
			unsigned long long stat2 = p2.first;
			int cnt2 = p2.second;

			if(v2.find(stat2) == v2.end()){
				v2[stat2] = cnt2;

				if(stat2 == begin){
					printf("%d\n",cnt2);
					return;
				}

				if(v1.find(stat2) != v1.end()){
					if(!ans_detected){
						ans_detected = true;
						ans = v1[stat2] + cnt2;
					}
					else{
						ans = min(ans,v1[stat2] + cnt2);
					}
				}

				unsigned long long l[4] = {0};
				unsigned long long b[4] = {0};
				l[0] = stat2 & Filter;
				l[1] = (stat2 >> 12) & Filter;
				l[2] = (stat2 >> 24) & Filter;
				l[3] = (stat2 >> 36) & Filter;

				for(int i=0; i<4; ++i)
					b[i] = (l[i] == 0) ? 0 : l[i] ^ (l[i] & (l[i]-1));

				for(int i=0; i<4; ++i){
					if(b[i] == 0)
						continue;
					for(int j=0; j<4; ++j){
						if(b[i] < b[j] || b[j] == 0){
							unsigned long long nxt = move_disk(stat2, b[i], i, j); 
							// if(v2.find(nxt) == v2.end())
							q2.push(make_pair(nxt,cnt2+1));
						}
					}
				}
			}
		}

		if(ans_detected){
			printf("%d\n",ans);
			return;
		}
	}
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}