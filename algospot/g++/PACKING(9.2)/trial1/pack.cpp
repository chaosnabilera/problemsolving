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

int C,N,W;
int dp[100][1001];

char name[100][21];
int cost[100];
int value[100];
bool used[100];

int rec_dp(int maxi, int cap){
	if(dp[maxi][cap] != -1){
		// printf("1) maxi:%d cap:%d : %d\n", maxi, cap, dp[maxi][cap]);
		return dp[maxi][cap];
	}

	if(cost[maxi] > cap){
		dp[maxi][cap] = 0;
		// printf("2) maxi:%d cap:%d : %d\n", maxi, cap, dp[maxi][cap]);
		return dp[maxi][cap];
	}

	dp[maxi][cap] =  value[maxi];
	for(int i=maxi-1; i >= 0; --i){
		if(cost[i] <= cap-cost[maxi]){
			int cand = value[maxi] + rec_dp(i,cap-cost[maxi]);
			if(cand > dp[maxi][cap]){
				dp[maxi][cap] = cand;
			}
		}
	}

	// printf("3) maxi:%d cap:%d : %d\n", maxi, cap, dp[maxi][cap]);
	return dp[maxi][cap];
}

void solve(){
	for(int i=0; i<N; ++i)
		for(int cap=1; cap<=W; ++cap)
			dp[i][cap] = -1;

	for(int i=0; i<N; ++i){
		dp[i][0] = 0;
		dp[i][cost[i]] = value[i];
	}

	for(int i=N-1; i>=0; --i){
		rec_dp(i,W);
	}
}

void print_table(){
	for(int i=0; i<N; ++i){
		for(int cap=0; cap<=W; ++cap){
			printf("%4d ", dp[i][cap]);
		}
		printf("\n");
	}
	printf("\n");
}

void print_answer(){
	vector<int> ans;
	
	int maxv = 0;
	int maxvi = -1;

	for(int i=N-1; i >= 0; --i){
		if(dp[i][W] > maxv){
			maxvi = i;
			maxv = dp[i][W];
		}
	}

	int head = maxvi;
	ans.push_back(head);
	int value_left = maxv - value[head];
	int capacity_left = W - cost[head];
	
	while(value_left > 0){
		for(int i=head-1; i >= 0; --i){
			if(capacity_left >= cost[i] && dp[i][capacity_left] == value_left){
				head = i;
				break;
			}
		}
		ans.push_back(head);
		value_left -= value[head];
		capacity_left -= cost[head];
	}

	reverse(ans.begin(), ans.end());

	printf("%d %ld\n", maxv, ans.size());
	for(auto i:ans){
		printf("%s\n", name[i]);
	}
}


int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d %d", &N, &W);
		for(int j=0; j<N; ++j){
			scanf("%s %d %d", name[j], &cost[j], &value[j]);
		}
		solve();
		// print_table();
		print_answer();
	}
}