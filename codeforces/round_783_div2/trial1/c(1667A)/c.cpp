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
long long A[5000];

long long count_operation(int zi){
    long long count = 0;
    long long prev;

    prev = 0;
    for(int i=zi-1; i>=0; --i){
        long long cur_cnt = (prev/A[i])+1;
        count += cur_cnt;
        prev = cur_cnt * A[i];
    }
    prev = 0;
    for(int i=zi+1; i<N; ++i){
        long long cur_cnt = (prev/A[i])+1;
        count += cur_cnt;
        prev = cur_cnt * A[i];
    }
    return count;
}

long long solve(){
    long long min_count = numeric_limits<long long>::max();
    for(int zi=0; zi<N; ++zi){
        min_count = min(min_count, count_operation(zi));
    }
    return min_count;
}

int main(int argc, char** argv){
    scanf("%d", &N);
    for(int i=0; i<N; ++i){
        scanf("%lld", &A[i]);
    }
    printf("%lld\n",solve());
}