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
    unordered_set<int> not_visited;
    vector<int> edge_history;
    RNG32<int> rng(1,N);
    int room, edges;
    int rn;

    for(int i=1; i<=N; ++i)
        not_visited.insert(i);

    scanf("%d%d", &room, &edges);
    edge_history.push_back(edges);
    for(int k=0; k<K; ++k){
        if((not_visited.find(room) == not_visited.end()) || edges < 5){
            int rn = *not_visited.begin();
            printf("T %d\n",rn); fflush(stdout);
            // fprintf(stderr,"T\n");
        }
        else{
            printf("W\n"); fflush(stdout);
            // fprintf(stderr,"W\n");
        }

        if(not_visited.find(room) != not_visited.end())
            not_visited.erase(room);

        scanf("%d%d", &room, &edges);
        edge_history.push_back(edges);
    }

    double edge_sum = 0;
    for(int e:edge_history)
        edge_sum += e;

    double edge_avg = edge_sum / edge_history.size();
    unsigned long long total_cnt = edge_avg * N * 0.5;
    
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