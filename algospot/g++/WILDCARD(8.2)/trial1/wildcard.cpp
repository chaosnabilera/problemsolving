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

#define MAX_STRLEN 100

string Wildcard;
vector<string> Input;
string Line;

int dp[MAX_STRLEN+1][MAX_STRLEN+1];
int lenW;
int lenL;

int rec_match(int w, int l){
	if(dp[w][l] != -1){
		return dp[w][l];
	}

	if(w == Wildcard.size()){
		dp[w][l] = (l == Line.size()) ? 1 : 0;
	}
	else if(l == Line.size()){
		dp[w][l] = (Wildcard[w] == '*') ? rec_match(w+1,l) : 0;
	}
	else{
		if(Wildcard[w] == '*'){
			dp[w][l] = rec_match(w+1,l) || rec_match(w,l+1);
		}
		else if(Wildcard[w] == '?'){
			dp[w][l] = rec_match(w+1,l+1);
		}
		else{
			dp[w][l] = (Wildcard[w] == Line[l]) ? rec_match(w+1,l+1) : 0;
		}
	}

	return dp[w][l];
}

int match(){
	for(int i=0; i<=Wildcard.size(); ++i)
		for(int j=0; j<=Line.size(); ++j)
			dp[i][j] = -1;

	return rec_match(0,0);
}

void solve(){
	vector<string> ans;
	for(auto line:Input){
		Line = line;
		if(match()){
			ans.push_back(line);
		}
	}
	sort(ans.begin(),ans.end());
	for(string& line:ans){
		cout << line << endl;
	}
}

int main(int argc, char** argv){
	int C, N;
	string line;
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		cin >> Wildcard;
		Input.clear();
		scanf("%d", &N);
		for(int j=0; j<N; ++j){
			cin >> line;
			Input.push_back(line);
		}

		solve();
	}
}