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

int C;
string ILINE;

string solve(int b){
	if(ILINE[b] == 'x'){
		string ul = solve(b+1);
		string ur = solve(b+1+ul.size());
		string dl = solve(b+1+ul.size()+ur.size());
		string dr = solve(b+1+ul.size()+ur.size()+dl.size());
		return "x"+dl+dr+ul+ur;
	}
	else{
		return string(1,ILINE[b]);
	}
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		cin >> ILINE;
		cout << solve(0) << endl;
	}
}