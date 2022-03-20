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
	Floyd-Warshall All Pair Shortest Path algorithm

	O(V^3) 의 시간 복잡도로 all-pair shortest path를 계산한다
	negative cycle이 없다면 negative weight edge가 있어도 잘 계산한다

	<원리 1>
	u->v 로의 shortest path는 직접 연결이든지, 아니면 뭔가를 경유하게 되어있다
	이 경유하는 vertex를 m이라고 한다면, shortest path는 u->m->v와 같이 표현할수 있다
	여기에서 u->m, m->v도 예외가 아님. 즉 이런식으로 재귀적으로 shortest path를 정의 가능함

	근데 이렇게만 생각하면 V^4 짜리 알고리즘이 나온다. 왜?
	u->m을 알기 위해서는 u와 m사이에 있을 수 있는 V개의 가능성을 다 봐야 함
	그리고 m->v 사이에 있을 수 있는 V개의 가능성도 봐야 함
	즉 u->v 사이에 올 수 있는 vertex하나에 대한 O(V) operation이 필요
	그리고 u->v 사이에 올 수 있는 vertex는 V개
	그리고 u,v 쌍의 개수는 V^2 개
	그래서 다 합치면 O(V^4) 가 되는 것

	<원리 2>
	모든 쌍 u,v에 대해서, vertex중 k개'만' shortest path의 경유 node로 썼을때 얻을 수 있는 shortest
	path를 우리가 이미 알고 있다고 해보자
	여기에 경유용 node로 k+1번째 node x를 추가해야 한다고 하자. 그럼 각 shortest path는 
	다음과 같이 update할 수 있다

	D(k+1)(u,v) = min(D(k)(u,v), D(k)(u,x) + D(k)(x,v))

	새로운 경유 node를 쓴다 = 어떤 식으로든 시작점에서 경유 node까지 갔다가 거기에서 목적지로 간다

	이기 때문. 그리고 '어떤식으로든 경유 node까지 간다' 부분은 이전 경유 node들을 이용해서 거기까지
	가는 길을 미리 그 전단계에서 만들어 놨으니 그걸 그대로 쓴다

	즉 이렇게 하면 각 D(k+1)(u,v) 를 O(1)에 할 수 있게 되고 k는 V번까지만 하면 되니까 
	(총 경유 가능이 V개니) 이 알고리즘은 O(V^3) 이 된다

	참 몇번이나 배우고 까먹고 배우고 까먹고 하게 된다 이 알고리즘...

	<원리 3>
	저건 언제나 전단계를 쓰니까 적어도 테이블을 두개는 유지해야 할 것 같다
	근데 사실 하나만 유지하면 됨
	왜냐하면 
	D(k+1)(u,v) = min(D(k)(u,v), D(k)(u,x) + D(k)(x,v))
	여기에서 각 u,v에 대해 결론적으로 쓰는건 원래 그 자리에 있던 값과 D(k)(u,x), D(k)(x,v) 이다

	근데 k+1번째가 x임을 생각하고 D(k)(u,x), D(k)(x,v)를 다시 보자
	u에서 x를 경유해 x를 가는 길, x에서 x를 경유해 v로 가는 길이라는건
	그냥 u에서 x, x에서 v이다
	즉 D(k+1)(u,x) = D(k)(u,x), D(k+1)(x,v) = D(k)(x,v) 이다

	즉 x를 matrix의 차례대로 0번째, ..., V-1번째로 꼽는다면 각 iteration에서 
	(row 0, col 0), (row 1,col 1), ... , (row V-1,col V-1) 이 다 invariant하다는 것이다

	그러니 그냥 adj를 있는 그대로 써도 상관 없다
*/

// adj에 바로 shortest path를 계산해서 넣어 버린다
// adj가 아닌 곳은 INF에 해당하는 매우 큰 값이 있다는 가정
template <typename T>
void floyd_warshall(vector<vector<T>>& adj){
	const size_t V = adj.size();
	for(size_t i=0; i < V; ++i)
		adj[i][i] = 0;
	for(int k=0; k<V; ++k)
		for(int i=0; i<V; ++i)
			for(int j=0; j<V; ++j)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

int main(int argc, char** argv){
}