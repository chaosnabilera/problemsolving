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

unordered_map<int, int> bfs_dist[9];

void print_vector(vector<char>& e){
	for(char v:e){
		printf("%d ",v);
	}
	printf("\n");
}

int vec_to_int(vector<char>& v){
	const int factor[8] = {1,10,100,1000,10000,100000,1000000,10000000};
	int res = 0;
	int f = 0;
	for(int i=v.size()-1; i>=0; --i){
		res += v[i]*factor[f];
		++f;
	}
	return res;
}

void precompute_part(int num_elem){
	queue<vector<char>> bfs_q1;
	queue<vector<char>> bfs_q2;

	queue<vector<char>>* cur = &bfs_q1;
	queue<vector<char>>* next = &bfs_q2;

	vector<char> s(num_elem);
	for(int i=1; i<=num_elem; ++i)
		s[i-1] = i;
	cur->push(s);

	int curlv = 0;
	while(!cur->empty()){
		while(!cur->empty()){
			vector<char> v = cur->front(); cur->pop();
			int vi = vec_to_int(v);
			
			if(bfs_dist[num_elem].find(vi) != bfs_dist[num_elem].end())
				continue;

			bfs_dist[num_elem][vi] = curlv;

			for(int i=0; i<num_elem-1; ++i){
				for(int j=i+2; j<=num_elem; ++j){
					vector<char> n = v;
					reverse(&n[i],&n[j]);
					next->push(n);
				}
			}
		}
		curlv++;
		swap(cur, next);
	}
}

void precompute(){
	for(int i=2; i<=8; ++i){
		//printf("%d\n",i);
		precompute_part(i);
	}
}

int N;
vector<int> A;

void get_input(){
	int v;
	scanf("%d", &N);
	A.clear();
	for(int i=0; i<N; ++i){
		scanf("%d", &v);
		A.push_back(v);
	}
}

void solve(){
	vector<pair<int,int>> O;
	vector<char> seq;

	for(int i=1; i<=N; ++i){
		O.push_back(make_pair(A[i-1],i));
	}
	sort(O.begin(),O.end());

	for(auto& p:O)
		seq.push_back(p.second);

	int k = vec_to_int(seq);
	printf("%d\n", bfs_dist[N][k]);
}

int main(int argc, char** argv){
	int c = 0;
	precompute();

	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}