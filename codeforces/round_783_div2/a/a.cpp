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

int solve(int n, int m){
    if(n == m){
        return (n-1) + (m-1);
    }
    if(n == 1){
        if(m == 2){
            return 1;
        }
        else{
            return -1;
        }
    }

    int base = (n-1)*2;
    int left = m-n;
    int more = ((left/2)*4);
    if(left & 1)
        ++more;
    
    return base+more;
}

int main(int argc, char** argv){
    int t = 0;
    int n,m;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        scanf("%d%d",&n,&m);
        if(n > m)
            swap(n,m);

        printf("%d\n", solve(n,m));
    }
}