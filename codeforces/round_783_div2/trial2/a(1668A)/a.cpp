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

int solve(){
    int n,m;
    scanf("%d%d",&n,&m);
    if(n > m)
        swap(n,m);

    if(n == 1 && m > 2)
        return -1;

    int e = m-n;
    return ((n-1)*2) + ((e/2)*4) + (e & 1);
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        printf("%d\n",solve());
    }
}