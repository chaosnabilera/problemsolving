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

int main(int argc, char** argv){
    int n = 0;
    scanf("%d", &n);

    if(n%3 == 0)
        printf("%d\n",2*(n/3));
    else
        printf("%d\n",2*(n/3)+1);

    if(n%3 == 0){
        printf("%d %d\n",n,n);
        --n;
    }

    int x = n/3;
    for(int i=0; i<x+1; ++i){
        printf("%d %d\n",x+1-i,i+1);
    }
    for(int i=0; i<x; ++i){
        printf("%d %d\n",n-i,n-x+1+i);
    }
}