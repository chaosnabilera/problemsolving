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
    Bipartite matching

    Max-flow의 특수 케이스

    서로 disjoint한 vertex그룹 A와 B가 있다고 하자
    우리는 A그룹에 있는 vertex와 B그룹에 있는 vertex를 paring하고 싶다
    하나와 이미 paring 되어 있는 vertex는 다른 paring에 쓸 수 없다
    pair수를 최대화 하려면 어떻게 하면 될까?

    생각해 보면 Source -> A의 각 정점에 capacity 1, A와 연결된 모든 B로의 edge가 모두 capacity 1,
    각 B에서 sink로 가는 edge를 하나씩 두고 그것에 capacity 1을 둔 다음 maximum flow를 구하면
    우리가 원하는 maximum matching이 된다

    Ford-fulkerson을 쓸수도 있겠지만 좀 더 간단한 방법이 있다

    일단 모든 edge가 capacity를 1만 가진다는 점에 착안해 보자
    a에서 b로 matching해 보려고 했는데 이미 a`가 b와 matching했다고 치자
    그럼 a`는 자신이 연결 되어 있는 다른 B의 점과 matching할 수 있는지 확인해 보면 된다
    그게 이미 다른 누군가 또 matching 되어 있다면 recursive하게 가능한지 다 본다
    즉 내가 갈 자리가 없으면 그 자리를 차지하고 있는 다른 누군가가 '비켜 줄 수 있는지'를 확인해 
    볼 수 있으면 된다

    이걸 구현한게 구종만 책 코드
*/

// A와 B의 정점의 개수
int A, B;
// adj[i][j] = Ai와 Bj가 연결되어 있는가?
const int MAX_N = 1000;
const int MAX_M = 1000;
bool Adj[MAX_N][MAX_M];
// 각 정점에 매칭된 상대 정점의 번호를 저장한다
vector<int> AMatch, BMatch;
/*
    dfs()의 방문 여부
    dfs를 할때 마다 false로 초기화 해야 함
    이미 matching되어 있는 애들에게 비켜 줄 수 있는지 확인해봐야 하는데
    확인은 각각 한번씩만 해보면 되니까 이게 있음
*/
vector<bool> Visited;

/*
    a에 연결된 B의 정점들 중 matching이 가능한 정점을 찾는다
    연결된 B의 정점이 이미 다른 A의 정점과 matching이 되어 있다면 그 정점이
    비켜줄 수 있는지 recursive하게 확인한다
*/
bool dfs(int a){
    if(Visited[a])
        return false;
    Visited[a] = true;
    for(int b=0; b<B; ++b){
        if(Adj[a][b]){
            if(BMatch[b] == -1 || dfs(BMatch[b])){
                AMatch[a] = b;
                BMatch[b] = a;
                return true;
            }
        }
    }
    return false;
}

// AMatch, BMatch 배열을 계산하고 최대 매칭의 크기를 반환한다
int bipartite_match(){
    int size = 0;

    Visited.resize(A);
    AMatch.resize(A);
    BMatch.resize(B);
    fill(AMatch.begin(),AMatch.end(),-1);
    fill(BMatch.begin(),BMatch.end(),-1);
    for(int a=0; a<A; ++a){
        fill(Visited.begin(),Visited.end(),false);
        if(dfs(a))
            ++size;
    }
    return size;
}

int main(int argc, char** argv){
    bipartite_match();
}