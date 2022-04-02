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

void solve(){
    scanf("%d%d",&R,&C);
    for(int r=0; r<R; ++r){
        if(r == 0){
            printf("..");
            for(int c=1; c<C; ++c){
                printf("+-");
            }
            printf("+\n");
            printf("..");
            for(int c=1; c<C; ++c){
                printf("|.");
            }
            printf("|\n");
        }
        else{
            for(int c=0; c<C; ++c){
                printf("+-");
            }
            printf("+\n");
            for(int c=0; c<C; ++c){
                printf("|.");
            }
            printf("|\n");
        }
    }
    for(int c=0; c<C; ++c){
        printf("+-");
    }
    printf("+\n");
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        printf("Case #%d:\n",i+1);
        solve();
    }
}