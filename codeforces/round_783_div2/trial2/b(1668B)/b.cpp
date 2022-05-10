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
long long M;
long long A[100000];

void get_input(){
    scanf("%d%lld", &N, &M);
    for(int i=0; i<N; ++i)
        scanf("%lld", &A[i]);
}

bool solve(){
    long long minA = 987654321987654321;
    long long maxA = 0;
    long long sum = 0;
    for(int i=0; i<N; ++i){
        long long a = A[i];
        minA = min(a,minA);
        maxA = max(a,maxA);
        sum += a;
    }
    // printf("sum: %lld minA: %lld maxA: %lld\n", sum, minA, maxA);
    sum = sum - minA + maxA + N;
    // printf("sum: %lld M: %lld\n", sum, M);
    return (M >= sum);
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        if(solve())
            printf("YES\n");
        else
            printf("NO\n");
    }
}