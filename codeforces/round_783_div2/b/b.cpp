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

int N,M;
int A[100000];

void get_input(){
    scanf("%d%d",&N,&M);
    for(int i=0; i<N; ++i)
        scanf("%d", &A[i]);
}

bool solve(){
    if(N > M)
        return false;
    
    int left = M;
    sort(&A[0],&A[N],greater<int>());
    
    left -= 1+(2*A[0]);

    for(int i=1; i<N; ++i){
        if(left <= 0)
            return false;
        left -= (1+A[i]);
    }
    return true;
}
int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        if(solve()){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
}