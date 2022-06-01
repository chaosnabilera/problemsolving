#include <iostream>

int main(int argc, char** argv){
    int t, n, m;
    int ur, uc;
    char board[10][10];
    bool possible;

    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        
        scanf("%d%d", &n, &m);
        for(int r=0; r<n; ++r)
            scanf("%s", board[r]);

        ur = -1; uc = 0;
        for(int r=0; r<n && ur == -1; ++r)
            for(int c=0; c<m; ++c)
                if(board[r][c] == 'R'){
                    ur = r;
                    uc = c;
                    break;
                }

        possible = true;    
        for(int r=ur; r<n && possible; ++r){
            for(int c=0; c<m; ++c){
                if(board[r][c] == 'R' && c < uc){
                    possible = false;
                    break;
                }
            }
        }

        if(possible)
            printf("YES\n");
        else
            printf("NO\n");
    }
}