#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,C;
int Ans[100];

void get_input(){
    scanf("%d%d", &N, &C);
}

void solve(){
    vector<int> D;
    int min_c = N-1;
    int max_c = 0;
    for(int i=N; i>1; --i)
        max_c += i;
    
    if(C < min_c || C > max_c){
        printf("IMPOSSIBLE\n");
        return;
    }
    
    int cost_left = C;
    for(int i=0; i<N-1; ++i){
        int max_cost = N-i;
        int min_mod = N-i-2;
        D.push_back(min(cost_left-min_mod,max_cost));
        cost_left -= D.back();
    }
    
    for(int i=0; i<N; ++i)
        Ans[i] = i+1;
    
    for(int i=N-2; i>=0; --i){
        int d = D.back(); D.pop_back();
        reverse(&Ans[i],&Ans[i+d]);
    }
    
    for(int i=0; i<N; ++i){
        printf("%d ",Ans[i]);
    }
    printf("\n");
}

int main(int argc, char** argv){
    int t = 0;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        printf("Case #%d: ",i+1);
        solve();
    }
}