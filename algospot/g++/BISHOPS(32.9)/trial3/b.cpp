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

int N;
int Board[8][8];

int LR[8][8];
int RL[8][8];

int A, B;

bool Adj[100][100];
vector<int> AMatch, BMatch;
vector<bool> Visited;

void get_input(){
    char line[0x10];

    scanf("%d", &N);
    for(int i=0; i<N; ++i){
        scanf("%s", line);
        for(int j=0; j<N; ++j)
            Board[i][j] = (line[j] == '.');
    }
}

void print_graph(int a2[][8]){
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            printf("%3d",a2[r][c]);
        }
        printf("\n");
    }
}

void build_graph(){
    memset(LR,0xFF,sizeof(LR));
    memset(RL,0xFF,sizeof(RL));
    // LR part1
    int no = -1;
    bool prev_obs = true;
    for(int rs = N-1; rs > 0; --rs){
        int cs = 0;
        int r = rs;
        int c = cs;
        while(r < N && c < N){
            if(Board[r][c]){
                if(prev_obs)
                    ++no;
                prev_obs = false;
                LR[r][c] = no;
            }
            else{
                prev_obs = true;
            }
            ++r; ++c;
        }
        prev_obs = true;
    }
    // LR part 2
    for(int cs = 0; cs < N; ++cs){
        int rs = 0;
        int r = rs;
        int c = cs;
        while(r < N && c < N){
            if(Board[r][c]){
                if(prev_obs)
                    ++no;
                prev_obs = false;
                LR[r][c] = no;
            }
            else{
                prev_obs = true;
            }
            ++r; ++c;
        }
        prev_obs = true;
    }
    A = no+1;

    // RL part 1
    no = -1;
    prev_obs = true;
    for(int rs = N-1; rs > 0; --rs){
        int cs = N-1;
        int r = rs;
        int c = cs;
        while(r < N && c >= 0){
            if(Board[r][c]){
                if(prev_obs)
                    ++no;
                prev_obs = false;
                RL[r][c] = no;
            }
            else{
                prev_obs = true;
            }
            ++r; --c;
        }
        prev_obs = true;
    }
    // RL part 2
    for(int cs = N-1; cs >= 0; --cs){
        int rs = 0;
        int r = rs;
        int c = cs;
        while(r < N && c >= 0){
            if(Board[r][c]){
                if(prev_obs)
                    ++no;
                prev_obs = false;
                RL[r][c] = no;
            }
            else{
                prev_obs = true;
            }
            ++r; --c;
        }
        prev_obs = true;
    }
    B = no+1;

    memset(Adj,0,sizeof(Adj));
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            if(Board[r][c]){
                int a = LR[r][c];
                int b = RL[r][c];
                Adj[a][b] = true;
            }
        }
    }
}

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



void solve(){
    build_graph();
    printf("%d\n", bipartite_match());
    // printf("LR\n");
    // print_graph(LR);
    // printf("RL\n");
    // print_graph(RL);
    // printf("\n");
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        solve();
    }
}