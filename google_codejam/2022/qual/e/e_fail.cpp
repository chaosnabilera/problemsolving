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
    vector<int> edge_history;
    int beg_room;
    int room, edges;
    double step = ((double)N)/((double)K);
    double edge_sum = 0;
    double edge_avg = 0;
    double edge_std = 0;
    double adjusted_avg = 0;
    int adjusted_cnt = 0;
    unsigned long long total_cnt = 0;

    scanf("%d%d", &beg_room, &edges);
    edge_history.push_back(edges);

    for(int k=0; k<K; ++k){
        int beg = k*step;
        int end = (k+1)*step;
        beg = max(1,beg);
        end = min(N,end);
        RNG32<int> rng(beg,end);

        printf("T %d\n", rng()); fflush(stdout);
        scanf("%d%d", &room, &edges);
        edge_history.push_back(edges);
    }

    // remove outliers from both sides
    sort(edge_history.begin(),edge_history.end());
    int ocnt = max(1,(int)(((double)K)*0.025));
    // fprintf(stderr,"ocnt:%d\n",ocnt);
    for(int i=0; i<edge_history.size()-(2*ocnt); ++i){
        edge_history[i] = edge_history[i+ocnt];
    }
    for(int i=0; i<(2*ocnt); ++i)
        edge_history.pop_back();
    
    edge_sum = 0;
    for(int e:edge_history)
        edge_sum += e;
    edge_avg = edge_sum / edge_history.size();

    // compute std
    for(int e:edge_history){
        double se = ((double)e)-edge_avg;
        edge_std += (se*se);
    }
    edge_std /= (edge_history.size()-1);
    edge_std = sqrt(edge_std);

    // fprintf(stderr,"edge_std:%lf\n",edge_std);

    // compute adjusted average based on standard deviation
    adjusted_avg = 0;
    adjusted_cnt = 0;
    for(int e:edge_history){
        if(abs((double)e-edge_avg) > 1.0*edge_std)
            continue;
        adjusted_avg += e;
        adjusted_cnt++;
    }

    if(adjusted_cnt < 1000){ // if adjusted_cnt is too small, just use total_cnt
        total_cnt = edge_avg * N * 0.5;
    }
    else{
        adjusted_avg /= adjusted_cnt;
        total_cnt = adjusted_avg * N * 0.5;
    }
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