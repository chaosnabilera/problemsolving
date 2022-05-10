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
long long    A[500001];
long long PSum[500001];
int DP[500001];
int Ord[500001];
int BIT[500001];

void get_input(){
    scanf("%d", &N);
    A[0] = 0;
    for(int i=1; i <= N; ++i)
        scanf("%lld", &A[i]);
}

int lsb(int val){
    return (val & -val);
}

void update(int i, int val){
    while(i <= N){
        BIT[i] = max(BIT[i], val);
        i += lsb(i);
    }
}

int query(int i){
    --i; // should not contain self
    int maxval = -INF;
    while(i > 0){
        maxval = max(BIT[i], maxval);
        i -= lsb(i);
    }
    return maxval;
}

int solve(){
    vector<pair<long long, int>> pord;

    PSum[0] = 0;
    for(int i=1; i<=N; ++i)
        PSum[i] = PSum[i-1] + A[i];

    for(int i=1; i<=N; ++i)
        pord.push_back(make_pair(PSum[i],-i));
    sort(pord.begin(), pord.end());

    for(int i=1; i<=N; ++i)
        Ord[-pord[i-1].second] = i;

    for(int i=0; i<=N; ++i)
        BIT[i] = -INF;

    DP[0] = 0;
    for(int i=1; i<=N; ++i){
        // case 1
        DP[i] = (A[i] > 0) ? DP[i-1] + 1 : (A[i] == 0) ? DP[i-1] : DP[i-1] - 1;
        // printf("i:%d DP[i]:%d\n",i,DP[i]);
        // case 2
        if(PSum[i] > 0){
            DP[i] = i;
        }
        else{
            DP[i] = max(DP[i], query(Ord[i]) + i);
        }
        // printf("i:%d Ord[i]:%d DP[i]:%d\n",i,Ord[i],DP[i]);
        update(Ord[i], DP[i] - i);
    }

    return DP[N];
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        printf("%d\n", solve());
    }
}