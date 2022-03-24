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
    Ford-Fulkerson Algorithm

    Network max flow를 찾는 알고리즘 과정은 대략 이렇다

    - Breadth-First Search를 하면서 source -> sink 까지 유량을 더할 수 있는 path를 찾는다
        - 예를 들어 capacity(a->b) > flow(a->b) 라면 여기엔 아직 뭔가 더 더할 수 있다
        - path에 있는 capacity - flow 의 최소값이 그 path로 보낼 수 있는 유량의 최대다
        - a->b flow를 양의 정수 x라고 한다면, b->a flow를 -x라고 말한다
            - 즉 b->a capacity가 0이라도 b->a flow가 음수라면 우리는 b->a 로 유량을 보낼 수 있는 것
            - 이건 전에 a->b로 보낸 유량을 a->b로 보내는 대신 다른 곳으로 보냈을 때 얻을 수 있는
              path를 찾는데 쓰이는 중요한 컨셉임
    - 더 이상 path를 찾을 수 없을 때 까지 BFS를 반복한다

    - 한번 BFS가 O(E) 이고 (모든 edge를 다 봐도 edge를 2번까지만 볼테니까) 한번에 보낼 수 있는
    유량이 최소 1이라고 치고 최대 유량이 f라면 Time complexity는 O(fE) 이다
    - 증명이 구종만 책에도 자세히 설명은 안되어 있는데 f의 최대값은 O(VE)라고 함 그래서 실제 complexity는
    O(fE)와 O(VE^2) 둘 중 작은 쪽

    - 정당성 증명 1: Min-Cut Max-Flow
        - Cut : Source와 Sink를 서로 다른 집합에 속하 도록 정점들을 나누는 것
            - Source가 속한 집합을 S, Sink가 속한 집합을 T라고 함
            - 일단 여기서 같은 집합에 속한 vertex는 모두 연결되어 있음
        - Cut을 어떻게 나누든 Cut을 통해 S->T 로 가는 maximum flow는 언제나 같다
            - 결국 Source에서 나온 만큼 Sink로 들어가는 거고 같은 path를 쓰는 거니까 path를 어떻게 끊든
            Source -> Sink로 들어가는 양은 변하지 않는거고, 따라서 S->T로 가는 flow도 변하지 않음
        - Cut의 Capacity : S->T 방향으로 잇는 edge들의 capacity들의 합
        - Cut의 Flow : S->T 방향으로 잇는 edge의 flow - T->S 방향으로 잇는 edge의 flow
        
        - 우리는 max flow를 찾은 그래프에서 언제나 Capacity = Flow인 Cut을 찾을 수 있음
          이걸 Min-Cut이라고 한다
            - Source에서 시작해서 아직 Capacity가 남아 있는 edge를 통해 도달할 있는 정점의 집합 S
            - 그외의 정점의 집합 T
        - 왜 저게 Min-Cut이냐?
            - Capacity >= Flow 이니까 Capacity를 Minimize 하는 Cut의 Capacity는 최소 Flow와 같거나 커야함
            - Capacity = Flow인 Cut을 찾았으면 그게 Capacity를 Minimize하는 Cut임
        - S에는 당연히 Source가 들어감
        - T에는 무조건 Sink가 들어감. Source에서 Sink까지 Capacity가 남아있는 Path가 있었다면 그건
          max flow가 아님
        - 이렇게 찾고 나면 S -> T 인 edge는 죄다 꽉 찬 상태임
          안 그랬으면 edge의 T쪽 끝에 있는 것을 S에 넣었어야 했을 테니까
        - 따라서 이 Cut의 Capacity = Flow
        - 그리고 이때의 Capacity = Max Flow. 왜냐 하면 Flow는 Cut을 어떻게 잘라도 변하지 않으니까

    - 정당성 증명 2: 그래서 Ford-Fulkerson이 Min-cut을 정말 찾는 건가?
        - Ford-Fulkerson은 BFS를 하면서 더 이상 Flow가 가능한 Path를 못찾을때 까지 계속한다
        - 즉 다시 말해 BFS를 하면서 S에서 T로 가는 모든 Edge가 꽉 찰 때 까지 계속한다는 뜻
        - 그러니 Ford-Fulkerson이 멈출때 = Max Flow가 되었을 때인 셈
        - 이 부분은 책 설명도 좀 두루뭉술 하긴 한데 대략 직관적으로는 맞는 것 같음
        - 사실 그냥 이부분 직관만으로도 대충 저게 되는것 같긴 함
*/

int ford_fulkerson(vector<vector<int>>& capacity, vector<vector<int>>& flow, int source, int sink){
    const int INF = numeric_limits<int>::max();
    int vcnt = capacity.size();
    int total_flow = 0;
    vector<int> parent(vcnt);

    // initial flow is 0
    for(int i=0; i<vcnt; ++i)
        fill(flow[i].begin(),flow[i].end(),0);

    while(true){
        queue<int> q;
        fill(parent.begin(),parent.end(),-1);
        parent[source] = source;
        q.push(source);

        while(!q.empty() && parent[sink] == -1){
            int u = q.front(); q.pop();
            for(int v = 0; v < vcnt; ++vcnt){
                if(parent[v] == -1 && capacity[u][v] - flow[u][v] > 0){
                    q.push(v);
                    parent[v] = u;
                }
            }
        }

        if(parent[sink] == -1)
            break;

        int amount = INF;
        for(int v = sink; v != source; v = parent[v])
            amount = min(amount, capacity[parent[v]][v] - flow[parent[v]][v]);

        for(int v = sink; v != source; v = parent[v]){
            flow[parent[v]][v] += amount;
            flow[v][parent[v]] -= amount;
        }
        total_flow += amount;
    }
    return total_flow;
}


int main(int argc, char** argv){
    vector<vector<int>> capacity;
    vector<vector<int>> flow;
    int source = 0;
    int sink = 0;

    ford_fulkerson(capacity,flow,source,sink);
}