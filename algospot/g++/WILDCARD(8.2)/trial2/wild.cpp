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

char DP[101][101];
string Pattern;
string Word;

void get_input(){
	char line[0x100];
	scanf("%s", line);

	int p = 0;
	for(int i=0; i <= 100; ++i){
		if(line[i] == '*'){
			if(i == 0 || line[i-1] != '*'){
				line[p] = line[i];
				++p;
			}
		}
		else{
			line[p] = line[i];
			++p;
		}
		if(line[i] == 0)
			break;
	}

	Pattern = line;
}

char rec_match(int p, int w){
	if(DP[p][w] != -1)
		return DP[p][w];

	if(Pattern[p] == '*'){
		DP[p][w] = false;
		for(int nw=w; nw <= Word.size(); ++nw){
			DP[p][w] = rec_match(p+1,nw);
			if(DP[p][w])
				break;
		}
	}
	else if(Pattern[p] == '?'){
		if(w == Word.size())
			DP[p][w] = false;
		else
			DP[p][w] = rec_match(p+1, w+1);
	}
	else{
		if(w == Word.size())
			DP[p][w] = false;
		else
			DP[p][w] = (Pattern[p] == Word[w]) ? rec_match(p+1, w+1) : false;
	}

	return DP[p][w];
}

void precompute_dp(){
	DP[Pattern.size()][Word.size()] = true;
	for(int i=0; i<Word.size(); ++i){
		DP[Pattern.size()][i] = false;
	}
	if(Pattern[Pattern.size()-1] == '*'){
		for(int i=0; i <= Word.size(); ++i){
			DP[Pattern.size()-1][i] = true;
		}
	}
}

void solve(){
	vector<string> words;
	int numword;
	char line[0x100];

	scanf("%d", &numword);
	words.reserve(numword);

	for(int i=0; i<numword; ++i){
		scanf("%s", line);
		words.push_back(line);
	}

	sort(words.begin(),words.end());
	for(int i=0; i<words.size(); ++i){
		Word = words[i];
		memset(DP,-1,sizeof(DP));

		precompute_dp();		

		if(rec_match(0,0))
			printf("%s\n",Word.c_str());
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