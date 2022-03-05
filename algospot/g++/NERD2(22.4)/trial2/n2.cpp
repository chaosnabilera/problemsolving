#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int N;

void solve(){
	set<pair<int,int>> points;
	int x,y;
	pair<int,int> k;
	int cum = 0;
	vector<pair<int,int>> to_del;

	scanf("%d%d",&x,&y);
	k = make_pair(x,y);
	points.insert(k);
	++cum;

	for(int i=1; i<N; ++i){
		scanf("%d%d",&x,&y);
		pair<int,int> k = make_pair(x,y);

		auto sres = points.lower_bound(k);
		if(sres == points.end()){
			to_del.clear();
			for(auto it = points.rbegin(); it != points.rend(); ++it){
				pair<int,int> p = *it;
				if(p.second > y)
					break;
				to_del.push_back(p);
			}
			for(auto p:to_del){
				points.erase(p);
			}
			points.insert(k);
		}
		else if(y > sres->second){
			to_del.clear();

			set<pair<int,int>>::reverse_iterator it(sres);

			for(; it != points.rend(); ++it){
				pair<int,int> p = *it;
				if(p.second > y)
					break;
				to_del.push_back(p);
			}
			for(auto p:to_del){
				points.erase(p);
			}
			points.insert(k);
		}
		cum += points.size();
	}

	printf("%d\n", cum);
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		scanf("%d", &N);
		solve();
	}
}