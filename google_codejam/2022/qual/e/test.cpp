#include <iostream>
#include <random>
#include <limits>
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
private:
	std::random_device* rd;
	std::mt19937* gen;
	std::uniform_int_distribution<T>* dis;
};

int main(int argc, char** argv){
    int N = 91967;
    int K = 100;
    double step = ((double)N)/((double)K);

    unordered_set<int> h;
    for(int i=1; i<=10; ++i)
        h.insert(i);

    while(!h.empty()){
        int a = *h.begin();
        h.erase(a);
        printf("%d\n",a);
    }

    // for(int k=0; k<K; ++k){
    //     int beg = k*step;
    //     int end = (k+1)*step;
    //     printf("%d %d\n",beg,end);
    // }

    // RNG32<int> rng(0,2);
    // for(int i=0; i<100; ++i)
    //     printf("%d\n",rng());
}