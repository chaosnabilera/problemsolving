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

int main(int argc, char** argv){
    scanf("%d", &N);

    if(N%3 == 0){
        printf("%d\n",2*(N/3));
        printf("%d %d\n",N,N);
        --N;
    }
    else{
        printf("%d\n",2*(N/3)+1);
    }
    

    int x = N/3;
    for(int i=0; i<x+1; ++i)
        printf("%d %d\n",x+1-i,i+1);
    for(int i=0; i<x; ++i)
        printf("%d %d\n",N-i,N-x+1+i);
}