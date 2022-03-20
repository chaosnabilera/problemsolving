// just for dijkstra
#include <iostream>
#include <vector>
#include <queue>

// for problem
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

/*
	Dijkstra algorithm
	음수 weight가 없는 graph에서 shortest path를 찾는 알고리즘
	시작점으로 부터 가까운 순서대로 vertex를 찾는다

	원리는 우리가 시작점으로 부터 가장 가까운 순으로 x개를 이미 찾아놨을때
	x+1번째로 가까운 vertex는 이미 찾아둔 x개의 vertex중 하나와 직접적으로 연결된
	vertex중 하나라는 것이다
	즉 이미 찾아둔 x개의 vertex와 직접적으로 연결된 vertex중에
	시작점으로 부터의 거리가 가장 가까운걸 찾으면 그것이 우리가 원하는 다음 x+1번째라는 것
	이것을 반복해 나가면 결국 vertex를 순서대로 정렬할 수 있음
	우리가 원하는 vertex가 나오면 거기서 종료해도 되고

	대략의 증명은 이렇다
	이미 x개를 찾아놨고 x+1번째로 가까운걸 찾으려고 하는데 이게 앞에 찾은 x개가 아닌
	다른 vertex p를 거쳐서 도달해야 하는 것이라고 해보자
	그런데 시작점에서 p까지의 거리는 x+1번째 까지 거리와 같거나(0짜리 edge가 있다면)
	가까워야만 한다. p에서 x+1번째 까지 edge가 연결되어 있을텐데 우리는 x+1에 도달하기
	전에 p에 먼저 도달해야만 할테니까
	0인 edge가 없다면 p는 그냥 존재할 수 없고
	0인 edge가 있다고 해도 p에 도달하기 위한 그 전 단계는 계속 0으로 이어져야 한다
	그렇게 계속 0으로 이어지다 보면 이미 찾은 x개에 연결이 될 수 밖에 없다.
	그러니 x개와 연결 안된 x+1번째는 존재할 수 없는 것

	Dijkstra 구현 방법은 두가지

	1. priority queue를 이용. 이미 찾은 x개에서 도달할 수 있는 vertex들을 그 거리 순으로 priority queue로 뽑아
	하나씩 발견하기
	2. 그냥 iterate해서 찾기. V가 작으면 이게 더 빠를 수 있다 (book의 2번째)
	근데 뭐... V가 그정도로 작으면 어차피 1을 써도 빠를 것이다. 그냥 1이나 쓰자
*/

// T : type of weight/distance
// adj : list of (dst, weight)
// Return : list of (vertex no, distance)
// if dst == -1 : return everything
// if dst != -1 : stop when we hit dst
template <typename T>
vector<pair<int, T>> dijkstra(vector<vector<pair<int, T>>>& adj, int src, int dst = -1){
	const T INF = numeric_limits<T>::max();
	vector<T> dist(adj.size(), INF);
	priority_queue<pair<T,int>,vector<pair<T,int>>,greater<pair<T,int>>> minq;
	vector<pair<int,T>> ans;

	minq.push(make_pair(0,src));
	while(!minq.empty()){
		auto p = minq.top(); minq.pop();
		T cost = p.first;
		int cur = p.second;

		if(dist[cur] <= cost)
			continue;

		dist[cur] = cost;
		ans.push_back(make_pair(cur,dist[cur]));

		if(cur == dst)
			break;

		for(int i=0; i<adj[cur].size(); ++i){
			int nxt = adj[cur][i].first;
			T nxt_dist = dist[cur] + adj[cur][i].second;
			if(nxt_dist < dist[nxt])
				minq.push(make_pair(nxt_dist,nxt));
		}
	}
	return ans;
}



// algospot 30.3 ROUTING
// https://algospot.com/judge/problem/read/ROUTING
// sample_input should give 1.3200000000

int N,M;
vector<vector<pair<int,double>>> Adj;

void get_input(){
	int a,b;
	double c;
	scanf("%d%d",&N,&M);

	Adj.clear();
	Adj.resize(N);
	for(int i=0; i<M; ++i){
		scanf("%d%d%lf",&a,&b,&c);
		c = log(c);
		Adj[a].push_back(make_pair(b,c));
		Adj[b].push_back(make_pair(a,c));
	}
}

void solve(){
	vector<pair<int,double>> ans = dijkstra<double>(Adj,0,N-1);
	double ans_dist = ans.back().second;
	printf("%.10lf\n", exp(ans_dist));
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}