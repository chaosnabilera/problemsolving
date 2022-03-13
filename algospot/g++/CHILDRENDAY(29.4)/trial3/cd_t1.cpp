#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

char D[0x10];
int N,M;

struct Elem{
	string numstr;
	bool over_n;
	int modnum;
};

Elem ModStat[10000];

string solve(){
	vector<string> digit;
	queue<Elem> bfsq;

	Elem e; e.over_n = false; e.modnum = -1;
	for(int i=0; i<N; ++i)
		ModStat[i] = e;

	char single[2] = {0};
	char* c = D;
	while(*c){
		single[0] = *c;
		digit.push_back(single);
		++c;
	}
	sort(digit.begin(), digit.end());

	for(string& d:digit)
		if(d != "0"){
			Elem ne;
			int inum = d[0]-'0';
			ne.numstr = d;
			ne.over_n = (inum >= N);
			ne.modnum = inum % N;

			bfsq.push(ne);
		}

	while(!bfsq.empty()){
		Elem e = bfsq.front(); bfsq.pop();
		bool should_add_more = false;

		if(e.over_n && e.modnum == M){
			return e.numstr;
		}

		if(!ModStat[e.modnum].over_n){
			ModStat[e.modnum] = e;

			for(string& d:digit){
				Elem ne;
				ne.numstr = e.numstr+d;
				if(!e.over_n){
					int en = stoi(e.numstr);
					ne.over_n = (((en*10)+(d[0]-'0')) >= N);
				}
				else
					ne.over_n = true;
				ne.modnum = ((e.modnum*10)+(d[0]-'0')) % N;

				if(!ModStat[ne.modnum].over_n)
					bfsq.push(ne);
			}
		}
	}
	return "IMPOSSIBLE";
}

int main(int argc, char** argv){
	int t = 0;
	scanf("%d", &t);
	for(int i=0; i<t; ++i){
		scanf("%s %d %d", D,&N,&M);
		string ans = solve();
		cout << ans << endl;
	}
}