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

const int INF = 987654321;

char Line[10001];
int Linelen;
int DP[10001];

bool is_sameval(int s, int len){
	for(int i=1; i<len; ++i){
		if(Line[s] != Line[s+i])
			return false;
	}
	return true;
}

bool is_single_increase(int s, int len){
	for(int i=1; i<len; ++i){
		if(Line[s+i] != Line[s]+i)
			return false;
	}
	return true;
}

bool is_single_decrease(int s, int len){
	for(int i=1; i<len; ++i){
		if(Line[s+i] != Line[s]-i)
			return false;
	}
	return true;
}

bool is_flip(int s, int len){
	int flip[2] = { Line[s], Line[s+1] };
	for(int i=2; i<len; ++i){
		if(Line[s+i] != flip[i&1])
			return false;
	}
	return true;
}

bool is_step(int s, int len){
	int step = Line[s+1]-Line[s];
	for(int i=2; i<len; ++i){
		if(Line[s+i] - Line[s+i-1] != step)
			return false;
	}
	return true;
}

void get_input(){
	scanf("%s", Line);
	Linelen = strlen(Line);
	memset(DP,0xFF,sizeof(DP));
}

void print_dp(){
	for(int i=0; i<=Linelen; ++i){
		if(DP[i] > 100000)
			printf("  INF");
		else
			printf("%5d",DP[i]);
	}
	printf("\n");
}

void solve(){
	DP[Linelen] = 0;
	DP[Linelen-1] = INF;
	DP[Linelen-2] = INF;

	for(int s=Linelen-3; s >= 0; --s){
		DP[s] = INF;
		for(int len=3; len <= 5; ++len){
			if(s+len > Linelen)
				break;
			if(is_sameval(s,len)){
				DP[s] = min(DP[s],DP[s+len]+1);
				continue;
			}
			if(is_single_increase(s,len) || is_single_decrease(s,len)){
				DP[s] = min(DP[s],DP[s+len]+2);
				continue;
			}
			if(is_flip(s,len)){
				DP[s] = min(DP[s],DP[s+len]+4);
				continue;
			}
			if(is_step(s,len)){
				DP[s] = min(DP[s],DP[s+len]+5);
				continue;
			}
			DP[s] = min(DP[s],DP[s+len]+10);
		}
	}

	// print_dp();

	printf("%d\n",DP[0]);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}