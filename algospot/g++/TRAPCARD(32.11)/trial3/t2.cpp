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

bool iMap[20][20];
int R,C;
vector<int> AVertex;
vector<int> BVertex;
vector<int> Adj[400];

int AMatch[400];
int BMatch[400];
bool Visited[400];

void get_input(){
    char iline[0x20];
    scanf("%d%d",&R,&C);
    for(int r=0; r<R; ++r){
        scanf("%s", iline);
        for(int c=0; c<C; ++c)
            iMap[r][c] = (iline[c] == '.');
    }
}

int rc_to_v(int r, int c){
    return (r*C)+c;
}

void build_graph(){
    int v;

    AVertex.clear();
    BVertex.clear();
    for(int i=0; i<400; ++i)
        Adj[i].clear();

    for(int r=0; r<R; ++r){
        for(int c=0; c<C; ++c){
            if(!iMap[r][c])
                continue;
            v = rc_to_v(r,c);

            if((r+c)&1)
                AVertex.push_back(v);
            else
                BVertex.push_back(v);

            if(r > 0 && iMap[r-1][c])
                Adj[v].push_back(rc_to_v(r-1,c));
            if(r < R-1 && iMap[r+1][c])
                Adj[v].push_back(rc_to_v(r+1,c));
            if(c > 0 && iMap[r][c-1])
                Adj[v].push_back(rc_to_v(r,c-1));
            if(c < C-1 && iMap[r][c+1])
                Adj[v].push_back(rc_to_v(r,c+1));
        }
    }
}

bool dfs(int a){
    if(Visited[a])
        return false;
    Visited[a] = true;
    for(int b:Adj[a]){    
        if(BMatch[b] == -1 || dfs(BMatch[b])){
            AMatch[a] = b;
            BMatch[b] = a;
            return true;
        }
    }
    return false;
}

int bipartite_match(){
    int size = 0;
    memset(AMatch,0xFF,sizeof(AMatch));
    memset(BMatch,0xFF,sizeof(BMatch));
    for(int a:AVertex){
        memset(Visited,0,sizeof(Visited));
        if(dfs(a))
            ++size;
    }
    return size;
}

void solve(){
    bool place_bomb[400] = {0};
    bool changed = false;
    int num_bomb = 0;

    build_graph();
    bipartite_match();

    for(int a:AVertex){
        place_bomb[a] = true;
        num_bomb++;
    }
        

    for(int b:BVertex){
        if(BMatch[b] == -1){
            place_bomb[b] = true;
            num_bomb++;
        }
    }

    while(true){
        changed = false;
        for(int a:AVertex){
            if(!place_bomb[a] || AMatch[a] == -1)
                continue;
            for(int b:Adj[a]){
                if(place_bomb[b]){
                    changed = true;
                    place_bomb[a] = false;
                    place_bomb[AMatch[a]] = true;
                    break;
                }
            }
        }
        if(!changed)
            break;
    }

    printf("%d\n",num_bomb);
    for(int r=0; r<R; ++r){
        for(int c=0; c<C; ++c){
            if(iMap[r][c]){
                if(place_bomb[rc_to_v(r,c)])
                    printf("^");
                else
                    printf(".");
            }
            else{
                printf("#");
            }
        }
        printf("\n");
    }
}

int main(int argc, char** argv){
    int c = 0;
    scanf("%d", &c);
    for(int i=0; i<c; ++i){
        get_input();
        solve();
    }
}