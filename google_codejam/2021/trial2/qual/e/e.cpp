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

double PQ[101];

char iStat[100][10001];

void precompute_q(){
    double e[601];
    int pqcnt[101] = {0};
    double q,s;

    for(int i=0; i<=600; ++i){
        e[i] = 0;
        q = -3.0 + (0.01*i);
        for(int j=0; j<=600; ++j){
            s = -3.0 + (0.01*j);
            e[i] += 1.0/(1.0+exp(q-s));
        }
        e[i] *= 100.0/601.0;
    }

    for(int i=0; i<=600; ++i){
        PQ[((int)e[i])] += -3.0 + (0.01*i);
        pqcnt[((int)e[i])]++;
    }

    for(int i=0; i<=100; ++i){
        if(pqcnt[i] == 0){
            PQ[i] = (i<50) ? 3.0 : -3.0;
        }
        else{
            PQ[i] /= pqcnt[i];
        }
    }
}

void get_input(){
    for(int i=0; i<100; ++i)
        scanf("%s",iStat[i]);
}

void estimate_s(double* Q, int* ACnt, double* S){
    double e[601];
    double es[10001];

    for(int i=0; i<=600; ++i){
        double s = -3.0 + (0.01*i);
        e[i] = 0.0;
        for(int j=0; j<10000; ++j){
            e[i] += 1.0/(1.0+exp(Q[j]-s));
        }
    }

    // for(int i=0; i<=600; ++i){
    //     printf("e[%lf] : %lf\n", -3.0+(0.01*i), e[i]);
    // }

    int prev = 0;
    for(int i=0; i<=600; ++i){
        int cur = (int)e[i];
        for(int j=prev; j<=cur; ++j){
            es[j] = -3.0 + (0.01*i);
        }
        prev = cur;
    }
    for(int i=prev; i<=10000; ++i){
        es[i] = 3.0;
    }

    for(int i=0; i<100; ++i)
        S[i] = es[ACnt[i]];
}

int solve(){
    double Q[10000];
    int ACnt[100];
    double S[100];

    vector<pair<double,int>> difficulty;
    double anomaly[100];

    for(int q=0; q<10000; ++q){
        int cnt = 0;
        for(int s=0; s<100; ++s){
            iStat[s][q] -= '0';
            cnt += iStat[s][q];
        }
        Q[q] = PQ[cnt];
    }

    for(int s=0; s<100; ++s){
        ACnt[s] = 0;
        for(int q=0; q<10000; ++q)
            ACnt[s] += iStat[s][q];
    }

    estimate_s(Q, ACnt, S);

    // for(int i=0; i<100; ++i){
    //     printf("S[%d]: %lf (%d/10000)\n", i, S[i], ACnt[i]);
    // }

    for(int i=0; i<10000; ++i){
        difficulty.push_back(make_pair(Q[i],i));
    }
    sort(difficulty.begin(),difficulty.end(),greater<pair<double,int>>());

    for(int s=0; s<100; ++s){
        anomaly[s] = 0;
        for(int i=0; i<100; ++i){
            int q = difficulty[i].second;
            double prob_correct = 1.0/(1.0 + exp(Q[q]-S[s]));
            if(iStat[s][q])
                anomaly[s] += (1-prob_correct);
        }
    }

    int max_i = 0;
    for(int i=1; i<100; ++i){
        if(anomaly[i] > anomaly[max_i])
            max_i = i;
    }

    return max_i+1;
}

int main(int argc, char** argv){
    int t,p;
    precompute_q();
    scanf("%d%d", &t, &p);
    for(int i=0; i<t; ++i){
        get_input();
        printf("Case #%d: %d\n", i+1, solve());
    }
}