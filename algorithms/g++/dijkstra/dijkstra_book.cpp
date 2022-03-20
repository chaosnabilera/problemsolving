#include <iostream>
#include <vector>

using namespace std;

// 정점의 개수
int V;
const int INF = 987654321;

// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다
vector<pair<int,int>> adj[MAX_V];
vector<int> dijkstra(int src){   // basic dijkstra
	vector<int> dist(V,INF);
	dist[src] = 0;
	priority_queue<pair<int,int>> pq;
	pq.push(make_pair(0,src));

	while(!pq.empty()){
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if(dist[here] < cost)
			continue;

		for(int i=0; i<adj[here].size(); ++i){
			int there = adj[here][i].first;
			int nextdist = cost+adj[here][i].second;
			if(dist[there] > nextdist){
				dist[there] = nextdist;
				pq.push(make_pair(-nextdist,there));
			}
		}
	}
	return dist;
}

vector<int> dijkstra2(int src){
	vector<int> dist(V,INF);
	// 각 정점을 방문했는지 여부를 저장한다
	vector<bool> visited(V, false);

	dist[src] = 0;
	visited[src] = false;
	while(true){
		// 아직 방문하지 않은 정점 중 가장 가까운 정점을 찾는다
		int closest = INF;
		int here;
		for(int i=0; i<V; ++i){
			if(dist[i] < closest && !visited[i]){
				here = i;
				closest = dist[i];
			}
		}
		if(closest == INF)
			break;
		visited[here] = true;
		for(int i=0; i<adj[here].size(); ++i){
			int there = adj[here][i].first;
			if(visited[there])
				continue;
			int nextdist = dist[here] + adj[here][i].second;
			dist[there] = min(dist[there], nextdist);
		}
	}
	return dist;
}