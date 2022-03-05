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

struct Node{
	Node(char* arr, int _len, int _cost) : len(_len), cost(_cost) {
		for(int i=0; i<len; ++i)
			A[i] = arr[i];
	}
	char A[8];
	const int len;
	const int cost;
};

int N;
int A[8];

unordered_map<int,int> MinSwap;
// map<int,int> MinSwap;

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i)
		scanf("%d", &A[i]);
}

int arr_to_int(char* arr, int len){
	int res = 0;
	for(int i=0; i<len; ++i)
		res = (res*10)+(arr[i]);
	return res;
}

void bfs(char* arr, int len){
	int curnum;
	queue<Node> q;
	q.push(Node(arr,len,0));

	while(!q.empty()){
		Node cur = q.front(); q.pop();
		curnum = arr_to_int(cur.A, cur.len);
		if(MinSwap.find(curnum) != MinSwap.end())
			continue;

		MinSwap[curnum] = cur.cost;

		for(int i=0; i<cur.len; ++i){
			for(int j=i+1; j<cur.len; ++j){
				Node nxt(cur.A, cur.len, cur.cost+1);
				reverse(&(nxt.A[i]),&(nxt.A[j+1]));
				q.push(nxt);
			}
		}
	}
}

void precompute(){
	char arr[8] = {1,2,3,4,5,6,7,8};
	for(int n=1; n<=8; ++n)
		bfs(arr,n);
}

void solve(){
	vector<pair<int,int>> order;
	char arr[8] = {0};
	int arrnum;

	order.reserve(N);
	for(int i=0; i<N; ++i)
		order.push_back(make_pair(A[i],i));

	sort(order.begin(), order.end());
	for(int i=0; i<N; ++i){
		arr[order[i].second] = i+1;
	}

	arrnum = arr_to_int(arr,N);

	printf("%d\n", MinSwap[arrnum]);
}

int main(int argc, char** argv){
	int T;
	precompute();
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}

	
	// for(auto p:MinSwap){
	// 	printf("%d : %d\n",p.first,p.second);
	// }
}