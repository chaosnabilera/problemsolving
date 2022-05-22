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

long long count_case(int zi, vector<long long>& a){
    vector<long long> b(a.size(), 0);
    long long cnt = 0;
    for(int i=zi-1; i>=0; --i){
        long long curcnt = (b[i+1] / a[i]) + 1;
        b[i] = a[i] * curcnt;
        cnt += curcnt;
    }
    for(int i=zi+1; i<a.size(); ++i){
        long long curcnt = (b[i-1] / a[i]) + 1;
        b[i] = a[i] * curcnt;
        cnt += curcnt;
    }
    return cnt;
}

int main(int argc, char** argv){
    int n;
    vector<long long> a;

    scanf("%d", &n);
    a.resize(n);
    for(int i=0; i<n; ++i)
        scanf("%lld", &a[i]);
    
    long long mincnt = numeric_limits<long long>::max();
    for(int zi=0; zi<n; ++zi)
        mincnt = min(mincnt, count_case(zi, a));

    printf("%lld\n", mincnt);
}