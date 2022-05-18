#include <iostream>
#include <cstring>

unsigned long long N,K;
int D[100001];
int ModCnt[100001];
int ModLastIdx[100001];
int DP[100001];

void get_input(){
    scanf("%lld%lld", &N,&K);
    for(int i=0; i<N; ++i)
        scanf("%d", &D[i]);
}

void solve(){
    unsigned long long psum = 0;
    unsigned long long cnt = 0;
    unsigned long long curmod = 0;

    unsigned long long a = 0;
    unsigned long long b = 0;

    memset(ModCnt, 0, sizeof(ModCnt));

    for(int i=0; i<N; ++i){
        psum += D[i];
        curmod = psum % K;
        cnt += ModCnt[curmod];
        if(curmod == 0)
            ++cnt;
        ++ModCnt[curmod];
    }

    a = cnt % 20091101;

    cnt = 0;
    psum = 0;
    memset(ModLastIdx, 0xFF, sizeof(ModLastIdx));
    memset(DP,0,sizeof(DP));

    for(int i=N-1; i >=0; --i){
        psum += D[i];
        curmod = psum % K;

        // printf("i:%d psum:%lld curmod:%lld ModLastIdx[curmod]:%d\n", i, psum, curmod, ModLastIdx[curmod]);
        if(D[i] == 0){
            DP[i] = 1 + DP[i+1];
        }
        else{
            DP[i] = (curmod == 0) ? 1 : 0;
            DP[i] = std::max(DP[i], DP[i+1]);
            if(ModLastIdx[curmod] != -1){
                DP[i] = std::max(DP[i], 1 + DP[ModLastIdx[curmod]]);
            }
        }
        // printf("DP[%d]: %d\n",i,DP[i]);
        ModLastIdx[curmod] = i;
    }

    b = DP[0];

    printf("%lld %lld\n",a,b);
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        solve();
    }
}