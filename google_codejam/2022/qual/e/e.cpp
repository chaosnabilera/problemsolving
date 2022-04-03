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

int N,K;

template <typename T>
class RNG32{
public:
	RNG32<T>(T beg = std::numeric_limits<T>::min(), T end = std::numeric_limits<T>::max()){
		rd = new std::random_device();
		gen = new std::mt19937((*rd)());
		dis = new std::uniform_int_distribution<T>(beg, end);
	}
	T operator()(){
		return (*dis)(*gen);
	}
    ~RNG32<T>(){
        delete rd;
        delete gen;
        delete dis;
    }
private:
	std::random_device* rd;
	std::mt19937* gen;
	std::uniform_int_distribution<T>* dis;
};

void simple_solve(){
    int beg_room;
    int room, edges;
    long long total_count = 0;

    scanf("%d%d", &beg_room, &edges);
    total_count += edges;

    for(int i=1; i<=N; ++i){
        if(i == beg_room)
            continue;
        printf("T %d\n",i); fflush(stdout);
        scanf("%d%d", &room, &edges);
        total_count += edges;
    }

    total_count >>= 1;
    printf("E %lld\n",total_count); fflush(stdout);
}

void estimation_solve(){
    vector<int> hT;
    vector<double> hW; 
    vector<bool> visited(N+1,false);
    RNG32<int> rng(1,N);
    int T, W, A, B;

    scanf("%d%d", &T, &A);
    hT.push_back(A);
    hW.push_back(1.0);
    visited[T] = true;

    for(int k=0; k<K; ++k){
        if((k&1) == 0){
            do{
                T = rng();
            } while(visited[T]);
            printf("T %d\n", T); fflush(stdout);
            scanf("%d%d",&T,&A);
            visited[T] = true;
            hT.push_back(A);
            hW.push_back(1.0);
        }
        else{
            printf("W\n"); fflush(stdout);
            scanf("%d%d",&W,&B);
            visited[W] = true;
            hT.push_back(B);
            hW.push_back(((double)A)/((double)B));
        }
    }

    double wtsum = 0;
    double wsum = 0;
    for(int i=0; i<hT.size(); ++i){
        wtsum += hW[i] * hT[i];
        wsum += hW[i];
    }
    double edge_avg = wtsum/wsum;
    unsigned long long total_cnt = (unsigned long long)(edge_avg * N * 0.5);

    // fprintf(stderr,"adjusted_avg:%lf adjusted_cnt:%d\n",adjusted_avg,adjusted_cnt);
    printf("E %llu\n", total_cnt); fflush(stdout);
}

void solve(){
    scanf("%d%d", &N, &K);
    if(K >= N){
        simple_solve();
    }
    else{
        estimation_solve();
    }
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        solve();
    }
    return 0;
}