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

char D[10];
int lenD;
int N,M;

string MinModStr[10000];

void solve(){
	string digits[10];
	queue<pair<string,int>> q;

	scanf("%s %d %d", D, &N, &M);
	lenD = strlen(D);

	for(int i=0; i<N; ++i)
		MinModStr[i].clear();

	sort(&D[0],&D[lenD]);

	for(int i=0; i<lenD; ++i){
		char dd[2] = {0};
		dd[0] = D[i];
		digits[i] = dd;
	}

	for(int i=0; i<lenD; ++i){
		if(D[i] == '0')
			continue;
		char dd[2] = {0};
		dd[0] = D[i];
		q.push(make_pair(dd,D[i]-'0'));
	}

	// fill q with numbers at least as big as N
	while(!q.empty()){
		pair<string,int> cp = q.front();
		string& cstr = cp.first;
		int cmod = cp.second;
		int cint = stoi(cstr);

		if(cint >= N)
			break;

		// less than N. pop this number
		q.pop();
		for(int i=0; i<lenD; ++i){
			int d = digits[i][0] - '0';
			string nxt = cstr + digits[i];
			int nxtmod = ((cmod*10)+d) % N;
			q.push(make_pair(nxt,nxtmod));
		}
	}

	while(!q.empty()){
		pair<string,int> cp = q.front(); q.pop();
		string& cstr = cp.first;
		int cmod = cp.second;

		if(MinModStr[cmod].size() != 0)
			continue;

		MinModStr[cmod] = cstr;
		if(cmod == M){
			break;
		}

		for(int i=0; i<lenD; ++i){
			int d = digits[i][0]-'0';
			string nxt = cstr + digits[i];
			int nxtmod = ((cmod*10)+d) % N;
			q.push(make_pair(nxt,nxtmod));
		}
	}

	if(MinModStr[M].size() == 0){
		printf("IMPOSSIBLE\n");
	}
	else{
		printf("%s\n",MinModStr[M].c_str());
	}
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		solve();
	}
}