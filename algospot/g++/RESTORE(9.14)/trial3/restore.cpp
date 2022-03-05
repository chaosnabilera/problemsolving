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

int K;
vector<string> iWord;
vector<string> Word;

int Overlap[15][15];
bool Visited[15][(1<<15)];
string DP[15][(1<<15)];

void get_input(){
	char line[0x100];
	scanf("%d", &K);
	iWord.clear();
	for(int i=0; i<K; ++i){
		scanf("%s", line);
		iWord.push_back(line);
	}
}

bool compare_length(string& a, string& b){
	if(a.size() == b.size()){
		return a < b;
	}
	else{
		return a.size() < b.size();
	}
}

void remove_redundancy(){
	Word.clear();
	sort(iWord.begin(), iWord.end(), compare_length);
	for(int i=0; i<iWord.size(); ++i){
		bool included = false;
		for(int j=i+1; j<iWord.size(); ++j){
			int klim = iWord[j].size()-iWord[i].size()+1;
			for(int k=0; k < klim; ++k){
				string sk = iWord[j].substr(k, iWord[i].size());
				if(iWord[i] == sk){
					included = true;
					break;
				}
			}
			if(included)
				break;
		}
		if(!included){
			Word.push_back(iWord[i]);
		}
	}
	K = Word.size();
}

int single_overlap(string& a, string& b){
	int asize = a.size(); int bsize = b.size();
	int obbeg = max(1, asize-(bsize-1));
	for(int ob=obbeg; ob < a.size(); ++ob){
		string apart = a.substr(ob, a.size()-ob);
		string bpart = b.substr(0,apart.size());
		if(apart == bpart)
			return ob;
	}
	return a.size();
}

void compute_overlap(){
	for(int i=0; i<Word.size(); ++i){
		for(int j=0; j<Word.size(); ++j){
			if(i == j){
				Overlap[i][j] = 0;
			}
			else{
				Overlap[i][j] = single_overlap(Word[i],Word[j]);
			}
			// printf("Overlap[%d][%d] = %d\n",i,j,Overlap[i][j]);
		}
	}
}

string rec_solve(int beg, int state){
	if(Visited[beg][state])
		return DP[beg][state];

	Visited[beg][state] = true;

	if(state == 0){
		DP[beg][state] = Word[beg];
		return DP[beg][state];
	}

	string res;
	int reslen = INF;
	string& curstr = Word[beg];

	for(int nb=0; nb<Word.size(); ++nb){
		if(!((1<<nb) & state))
			continue;

		string cand = rec_solve(nb, state ^ (1<<nb));
		int overlap_beg = Overlap[beg][nb];

		if(overlap_beg + cand.size() < reslen){
			res = curstr.substr(0,overlap_beg) + cand;
			reslen = res.size();
		}
	}

	DP[beg][state] = res;
	return res;
}

void solve(){
	remove_redundancy();
	// for(string& s:Word)
	// 	printf("%s\n",s.c_str());
	compute_overlap();

	memset(Visited,0,sizeof(Visited));

	int fullstate = (1<<Word.size())-1;
	
	string res = rec_solve(0, fullstate ^ 1);
	for(int i=1; i<Word.size(); ++i){
		string cur = rec_solve(i, fullstate ^ (1<<i));
		if(cur.size() < res.size())
			res = cur;
	}

	printf("%s\n", res.c_str());
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}