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

const int BIGNUM = 987654321;
int E,W;
int Exer[100][100];
int DP[100][100];
int Common[100][100];

void get_input(){
    scanf("%d%d",&E,&W);
    for(int e=0; e<E; ++e)
        for(int w=0; w<W; ++w)
            scanf("%d", &Exer[e][w]);
}

int rec_solve(int l, int r){
    if(DP[l][r] != -1)
        return DP[l][r];
    
    DP[l][r] = BIGNUM;
    for(int x=l; x<r; ++x){
        DP[l][r] = min(DP[l][r], rec_solve(l,x)+rec_solve(x+1,r)-2*(Common[l][r]));
    }
    return DP[l][r];
}

void compute_common(){
    for(int l=0; l<E; ++l){
        Common[l][l] = 0;
        for(int w=0; w<W; ++w)
            Common[l][l] += Exer[l][w];

        for(int r=l+1; r<E; ++r){
            Common[l][r] = 0;
            for(int w=0; w<W; ++w){
                int wc = Exer[l][w];
                for(int i=l+1; i<=r; ++i){
                    wc = min(wc, Exer[i][w]);
                }
                // printf("Common[%d][%d] += %d\n",l,r,wc);
                Common[l][r] += wc;
            }
        }
    }
}

void print_common(){
    for(int l=0; l<E; ++l){
        for(int r=0; r<E; ++r){
            printf("%3d",Common[l][r]);
        }
        printf("\n");
    }
    printf("\n");
}

int solve(){
    memset(DP,0xFF,sizeof(DP));
    compute_common();
    // print_common();
    for(int e=0; e<E; ++e){
        DP[e][e] = (Common[e][e] * 2);
        // printf("DP[%d][%d]: %d\n",e,e,DP[e][e]);
    }

    return rec_solve(0, E-1);
}

int main(int argc, char** argv){
    int t = 0;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        printf("Case #%d: %d\n", i+1, solve());
    }
}