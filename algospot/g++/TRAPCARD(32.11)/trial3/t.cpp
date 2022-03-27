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

int R,C;
bool iMap[20][20];
vector<int> Adj[400];

vector<int> AVertex, BVertex;
vector<int> AMatch, BMatch;
vector<bool> Visited;

bool dfs(int a){
    if(Visited[a])
        return false;
    Visited[a] = true;

    for(int b: Adj[a]){
        if(BMatch[b] == -1 || dfs(BMatch[b])){
            AMatch[a] = b;
            BMatch[b] = a;
            return true;
        }
    }
    return false;
}

// AMatch, BMatch 배열을 계산하고 최대 매칭의 크기를 반환한다
int bipartite_match(){
    int size = 0;
    int dim = R*C;
    int a;

    Visited.resize(dim);
    AMatch.resize(dim);
    BMatch.resize(dim);
    fill(AMatch.begin(),AMatch.end(),-1);
    fill(BMatch.begin(),BMatch.end(),-1);

    for(int a:AVertex){
        fill(Visited.begin(),Visited.end(),false);
        if(dfs(a))
            ++size;
    }

    return size;
}


void get_input(){
    char iline[0x20];
    scanf("%d%d",&R,&C);
    for(int r=0; r<R; ++r){
        scanf("%s",iline);
        for(int c=0; c<C; ++c)
            iMap[r][c] = (iline[c] == '.');
    }
}

int rc_to_a(int r, int c){
    return (r*C)+c;
}

void a_to_rc(int a, int& r, int& c){
    r = a / C;
    c = a % C;
}

void build_graph(){
    int u;
    for(int a=0; a<400; ++a)
        Adj[a].clear();
    
    AVertex.clear();
    BVertex.clear();

    for(int r=0; r<R; ++r){
        for(int c=0; c<C; ++c){
            if(!iMap[r][c])
                continue;
            u = rc_to_a(r,c);
            if((r+c) & 1)
                AVertex.push_back(u);
            else
                BVertex.push_back(u);

            if(r > 0 && iMap[r-1][c])
                Adj[u].push_back(rc_to_a(r-1,c));
            if(r < R-1 && iMap[r+1][c])
                Adj[u].push_back(rc_to_a(r+1,c));
            if(c > 0 && iMap[r][c-1])
                Adj[u].push_back(rc_to_a(r,c-1));
            if(c < C-1 && iMap[r][c+1])
                Adj[u].push_back(rc_to_a(r,c+1));
        }
    }
}

void solve(){
    int u,r,c;
    int dim = R*C;
    int size = 0;
    vector<bool> a_chosen(dim,true), b_chosen(dim,false);

    build_graph();
    int match_cnt = bipartite_match();

    for(int b:BVertex){
        if(BMatch[b] == -1)
            b_chosen[b] = true;
    }

    while(true){
        bool changed = false;
        for(int a: AVertex){
            for(int b:Adj[a]){
                if(a_chosen[a] && b_chosen[b]){
                    a_chosen[a] = false;
                    b_chosen[AMatch[a]] = true;
                    changed = true;
                }
            }
        }
        if(!changed)
            break;
    }

    int cnt = 0;
    for(int a:AVertex)
        if(a_chosen[a])
            ++cnt;
    for(int b:BVertex)
        if(b_chosen[b])
            ++cnt;

    printf("%d\n",cnt);
    for(int r=0; r<R; ++r){
        for(int c=0; c<C; ++c){
            if(iMap[r][c]){
                u = rc_to_a(r,c);
                if((r+c)&1){
                    if(a_chosen[u])
                        printf("^");
                    else
                        printf(".");
                }
                else{
                    if(b_chosen[u])
                        printf("^");
                    else
                        printf(".");
                }
            }
            else{
                printf("#");
            }
        }
        printf("\n");
    }
}

int main(int argc, char** argv){
    int c;
    scanf("%d", &c);
    for(int i=0; i<c; ++i){
        get_input();
        solve();
    }
}