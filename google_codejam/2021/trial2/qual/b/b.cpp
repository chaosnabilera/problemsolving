#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 987654321;
int X,Y;
char S[1024];
int Slen;

int DP[1000][2];
bool Visited[1000][2];

void get_input(){
    scanf("%d%d%s",&X,&Y,S);
    Slen = strlen(S);
}

int rec_solve(int i, int c){
    if(Visited[i][c])
        return DP[i][c];
    
    Visited[i][c] = true;
    if(i == Slen-1){
        DP[i][c] = 0;
        return 0;
    }
    
    if(S[i+1] == 'C'){
        if(c == 0)
            DP[i][c] = rec_solve(i+1,0);
        else
            DP[i][c] = Y + rec_solve(i+1,0);
    }
    else if(S[i+1] == 'J'){
        if(c == 0)
            DP[i][c] = X + rec_solve(i+1,1);
        else
            DP[i][c] = rec_solve(i+1,1);
    }
    else{
        if(c == 0)
            DP[i][c] = min(rec_solve(i+1,0), X+rec_solve(i+1,1));
        else
            DP[i][c] = min(Y+rec_solve(i+1,0), rec_solve(i+1,1));
    }
    
    return DP[i][c];
}

int solve(){
    memset(Visited,0,sizeof(Visited));
    
    if(S[0] == 'C')
        return rec_solve(0,0);
    else if(S[0] == 'J')
        return rec_solve(0,1);
    else
        return min(rec_solve(0,0),rec_solve(0,1));
}

int main(int argc, char** argv){
    int t = 0;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        printf("Case #%d: %d\n",i+1,solve());
    }
}