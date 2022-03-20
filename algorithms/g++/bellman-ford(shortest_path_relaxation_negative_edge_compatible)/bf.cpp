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

/*
	Bellman-Ford Algorithm
	- Shortest Path를 찾는 알고리즘. 결론적으로 원점에서 부터 가장 가까운 것 순으로 하나씩 찾아나간다는 점은
	Dijkstra와 비슷하지만 Relaxation 이라는 개념을 사용한다는게 좀 다르다.
	Relaxation은 다음 operation을 모든 Edge에 대해 반복하는 것이다

	dist[v] <= dist[u] + w(u,v)

	이건 당연하다면 당연한 성질인데 처음에 dist[원점]=0, 나머지는 무한대로 놓고 생각해 보면 다음과 같은 직관을 얻을 수 있다
	1. Iteration 1에는 원점에서 한번에 갈 수 있는 vertex가 모두 무한대가 아니게 된다. 
	   그리고 그 중 반드시 1번째로 가까운게 존재한다
	2. Iteration 2에는 원점에서 두번에 갈 수 있는 vertex가 모두 무한대가 아니게 된다. 
	   그리고 두번에 가는게 한번에 가는 것보다 더 짧은 것들도 모두 이번에 업데이트가 된다
	3. 이하 반복

	Vertex가 V개 있는 그래프에서 최대 Path 단계 수는 V-1이니까, V-1번의 Iteration을 거치면 도달할 수 있는 모든 점에 대한
	Shortest Path를 알 수 있게 된다
	또한 Relaxation에서 w(u,v)가 음수가 아니라는 법이 없으니 Cycle이 없는 한 음수 edge가 있는 그래프에서도 이건 통한다

	음수 Cycle은 어떻게 감지할 수 있을까?
	V-1번 하는 대신 한번 더 Iterate해서 V번째 Iteration에 업데이트 되는데가 있으면 음수 Cycle이 있는 것이다
	음수 Cycle이 있으면 매 Iteration마다 음수 Cycle에 포함되는 Vertex들은 모두 무조건 업데이트 되기 때문

	그래서 최종적인 Time Complexity는 O(|V||E|)

	한가지 주의점
	모든 vertex에 무한대를 할당한다고 하는데 사실 정말 무한대를 할당하는 건 아님
	그래서 그냥 큰 숫자를 넣게 되는데 문제는 '무한대보다 작다 = reachable 하다'는 아니라는 것
	예를 들어:
		s->a->b->c   d-(-2)->e 와 같은 그래프가 있을때
	e는 s에서 reachable하지 않지만 d-e edge를 relaxation하면서 e가 INF-2가 된다
	그래서 reachable한가 어떤가를 보려면 최종 distance가 INF보다 어느정도 이상 많이 작아야 함
	얼마나 작아야 하는지는 조건마다 다름
*/

// src로 부터 각 점까지의 shortest path를 담은 list를 리턴
// dfs를 이용해 reachability를 한번 계산한다음 bellman-ford를 실행한다
// 음수 사이클이 있으면 빈 list를 return
template <typename T>
void dfs(vector<vector<pair<int,T>>>& graph, vector<bool>& visited, int cur){
	if(visited[cur])
		return;
	visited[cur] = true;
	for(auto& p:graph[cur]){
		dfs(graph,visited,p.first);
	}
}

template <typename T>
vector<T> bellman_ford(vector<vector<pair<int,T>>>& adj, int src){
	const T INF = 987654321; // Big enough to represent Infinity. Small enough for checking dist[v] > dist[u] + w(u,v)
	vector<T> upper(adj.size(), INF);
	vector<bool> visited(adj.size(),false);
	upper[src] = 0;
	bool updated = false;

	dfs<int>(adj, visited, src);

	for(int it=0; it<adj.size(); ++it){
		updated = false;
		for(int u=0; u<adj.size(); ++u){
			if(!visited[u])
				continue;
			for(auto& p:adj[u]){
				int v = p.first;
				T cost = p.second;
				if(upper[v] > upper[u] + cost){ // relaxable
					upper[v] = upper[u] + cost;
					updated = true;
				}
			}
		}
		if(!updated)
			break;
	}

	if(updated) // negative cycle exist
		upper.clear();

	return upper;
}

int main(int argc, char** argv){
}