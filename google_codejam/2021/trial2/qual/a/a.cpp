/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int N;
vector<int> L;

void get_input(){
    scanf("%d", &N);
    L.resize(N);
    for(int i=0; i<N; ++i)
        scanf("%d", &L[i]);
}

int solve(){
    int minval;
    int minidx;
    int ans = 0;
    
    for(int i=0; i<N-1; ++i){
        minval = L[i];
        minidx = i;
        for(int j=i+1; j<N; ++j){
            if(L[j] < minval){
                minval = L[j];
                minidx = j;
            }
        }
        ans += (minidx-i+1);
        reverse(&L[i],&L[minidx+1]);
    }
    
    return ans;
}

int main(int argc, char** argv)
{
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        printf("Case #%d: %d\n", i+1, solve());
    }
}
