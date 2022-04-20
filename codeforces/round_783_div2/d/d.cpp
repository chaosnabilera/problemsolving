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

const int INF = 987654321;

int N;
int A[500001];
long long PSum[500001];
int DP[500001];
int Order[500001];
int BIT[500001];

void update(int i, int val){ // i is 1-indexed
    while(i <= N){
        BIT[i] = max(BIT[i], val);
        i += (i & -i);
    }
}

int query(int i){
    int ret = -INF;
    --i;
    while(i > 0){
        ret = max(BIT[i], ret);
        i -= (i & -i);
    }
    return ret;
}

void get_input(){
    scanf("%d", &N);
    A[0] = 0;
    for(int i=1; i<=N; ++i)
        scanf("%d", &A[i]);
}

int solve(){
    vector<pair<long long, int>> porder;

    PSum[0] = 0;
    for(int i=1; i<=N; ++i){
        PSum[i] = PSum[i-1] + A[i];
        porder.push_back(make_pair(PSum[i],-i));
    }

    Order[0] = 0;
    sort(porder.begin(), porder.end());
    for(int i=0; i<N; ++i)
        Order[-porder[i].second] = i+1;

    for(int i=0; i<=N; ++i)
        BIT[i] = -INF;

    DP[0] = 0;
    for(int i=1; i<=N; ++i){
        if(PSum[i] > 0){
            DP[i] = i;
            update(Order[i], 0);
        }
        else{
            if(A[i] > 0)
                DP[i] = DP[i-1] + 1;
            else if(A[i] < 0)
                DP[i] = DP[i-1] - 1;
            else
                DP[i] = DP[i-1];
            
            int dp_j = query(Order[i]);
            DP[i] = max(DP[i], dp_j + i);
            update(Order[i], DP[i] - i);
        }
    }

    return DP[N];
}

int main(int argc, char** argv){
    int t = 0;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        printf("%d\n", solve());
    }
}