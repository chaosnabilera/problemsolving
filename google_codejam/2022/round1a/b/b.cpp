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
vector<int> A;
vector<int> B;

void generate_A(){
    A.clear();
    for(int i=0; i<30; ++i)
        A.push_back(1<<i);
    for(int i=3000; i<3070; ++i)
        A.push_back(i);
}

void solve(){
    vector<int> groupP;
    long long sumP = 0;
    vector<int> groupQ;
    long long sumQ = 0;

    scanf("%d", &N);
    // fprintf(stderr, "N: %d ", N);
    B.resize(N);
    for(int i=0; i<A.size(); ++i){
        printf("%d ", A[i]);
    }
    printf("\n"); fflush(stdout);
    for(int i=0; i<N; ++i){
        scanf("%d", &B[i]);
    }

    // for(int b:B){
    //     fprintf(stderr, "%d ", b);
    // }
    // fprintf(stderr, "\n");

    sort(B.begin(), B.end());
    reverse(B.begin(), B.end());
    groupP.push_back(B[0]);
    sumP = B[0];
    for(int i=1; i<B.size(); ++i){
        if(sumP < sumQ){
            groupP.push_back(B[i]);
            sumP += B[i];
        }
        else{
            groupQ.push_back(B[i]);
            sumQ += B[i];
        }
    }

    // fprintf(stderr, "sumP 1:%lld\nsumQ 1:%lld\n\n",sumP,sumQ);

    for(int i=29; i>=0; --i){
        int curnum = 1<<i;
        if(sumP < sumQ){
            groupP.push_back(curnum);
            sumP += curnum;
        }
        else{
            groupQ.push_back(curnum);
            sumQ += curnum;
        }
    }

    for(int i=0; i<17; ++i){
        groupP.push_back(3000+(2*i));
        sumP += groupP.back();
        groupP.push_back(3069-(2*i));
        sumP += groupP.back();
        groupQ.push_back(3001+(2*i));
        sumQ += groupQ.back();
        groupQ.push_back(3068-(2*i));
        sumQ += groupQ.back();
    }

    if(sumP < sumQ){
        groupP.push_back(3035);
        groupQ.push_back(3034);
    }
    else {
        groupP.push_back(3034);
        groupQ.push_back(3035);
    }
    sumP += groupP.back();
    sumQ += groupQ.back();

    // fprintf(stderr, "sumP 2:%lld\nsumQ 2:%lld\n\n",sumP,sumQ);

    for(int p:groupP){
        printf("%d ",p);
    }
    printf("\n"); fflush(stdout);
}

int main(int argc, char** argv){
    int t = 0;
    generate_A();
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        solve();
    }
}