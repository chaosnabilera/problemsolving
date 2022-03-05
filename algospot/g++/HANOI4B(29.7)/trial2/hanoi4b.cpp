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
int Target;
int Mask[12];
short DP1[(1<<24)];
short DP2[(1<<24)];

void get_input(){
	int x,n;

	Target = 0;
	scanf("%d", &N);
	for(int i=0; i<4; ++i){
		scanf("%d", &n);
		for(int j=0; j<n; ++j){
			scanf("%d", &x);
			Target |= i << ((x-1)*2);
		}
	}
}

void print_bit(int s, int i){
	int n = (s & (1<<i)) ? 1 : 0;
	printf("%d",n);
}

void print_int(int s){
	for(int i=(N-1)*2; i>=0; i-=2){
		print_bit(s,i+1);
		print_bit(s,i);
		printf(" ");
	}
	printf("\n");
}

int run_queue(queue<pair<int,short>>& q, short* dp, short* dp_other, int target_state){
	bool found = false;
	int res = -1;
	int topcnt = q.front().second;

	while(q.front().second == topcnt){
		int state = q.front().first;
		int cnt = q.front().second;
		q.pop();

		if(dp[state] == -1){
			if(state == target_state){
				return cnt;
			}
			if(dp_other[state] != -1){
				if(!found){
					found = true;
					res = dp_other[state] + cnt;
				}
				else{
					res = min(res, dp_other[state] + cnt);
				}
			}
			
			dp[state] = cnt;

			int top[4] = {-1,-1,-1,-1};
			for(int i=11; i>=0; --i){
				top[(state >> (i*2)) & 3] = i;
			}

			for(int i=0; i<4; ++i){
				if(top[i] == -1)
					continue;
				for(int j=0; j<4; ++j){
					if(i != j && (top[j] == -1 || top[i] < top[j])){
						int cno = top[i];
						int next_state = state & Mask[cno];
						next_state |= j << (cno*2);

						// printf("top[%d]:%d  top[%d]:%d cno:%d\n",i,top[i],j,top[j],cno);
						// printf("state: ");
						// print_int(state);
						// printf("next_state: ");
						// print_int(next_state);
						// printf("\n");

						if(dp[next_state] == -1)
							q.push(make_pair(next_state,cnt+1));
					}
				}
			}
		}
	}

	return res;
}

void solve(){
	int begin = 0;
	for(int i=0; i<N; ++i)
		begin |= 3 << (i*2);

	// print_int(begin);
	// print_int(Target);

	memset(DP1,0xFF,sizeof(DP1));
	memset(DP2,0xFF,sizeof(DP1));

	// for(int i=0; i<=begin; ++i){
	// 	DP1[i] = -1;
	// 	DP2[i] = -1;
	// }

	queue<pair<int,short>> q1;
	q1.push(make_pair(begin,0));

	queue<pair<int,short>> q2;
	q2.push(make_pair(Target,0));

	while(true){
		int res = -1;
		res = run_queue(q1, DP1, DP2, Target);
		if(res != -1){
			printf("%d\n",res);
			return;
		}
		res = run_queue(q2, DP2, DP1, begin);
		if(res != -1){
			printf("%d\n",res);
			return;
		}
	}
}

int main(int argc, char** argv){
	int T;

	// precompute Mask
	for(int i=0; i<12; ++i){
		Mask[i] = 3 << (i*2);
		Mask[i] = ~Mask[i];
	}

	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}