#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

const int MILLION = 1000000;

int C[3];
int M[3];
int Y[3];
int K[3];

void get_input(){
    for(int i=0; i<3; ++i)
        scanf("%d%d%d%d",&C[i],&M[i],&Y[i],&K[i]);
}

void solve(){
    int mins[4] = { *min_element(&C[0],&C[3]),
                    *min_element(&M[0],&M[3]),
                    *min_element(&Y[0],&Y[3]),
                    *min_element(&K[0],&K[3]) };

    int sum_mins = accumulate(&mins[0],&mins[4],0);

    if(sum_mins < MILLION){
        printf("IMPOSSIBLE\n");
        return;
    }
        
    
    int left = MILLION;
    for(int i=0; i<4; ++i){
        int cur = min(mins[i],left);
        printf("%d ",cur);
        left -= cur;
    }
    printf("\n");
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        printf("Case #%d: ",i+1);
        get_input();
        solve();
    }
}