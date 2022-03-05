#include <iostream>
#include <random>
#include <queue>
#include <vector>

template <typename T>
class RNG32{
public:
	RNG32<T>(T beg, T end){
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
	int rnd[20];
	RNG32<int> rng(-10,10);

	for(int i=0; i<20; ++i){
		rnd[i] = rng();
	}

	printf("generated random sequence : ");
	for(int i=0; i<20; ++i){
		printf("%d ", rnd[i]);
	}
	printf("\n");

	std::priority_queue<int> maxq;
	std::priority_queue<int, std::vector<int>, std::greater<int>> minq;

	for(int i=0; i<20; ++i){
		maxq.push(rnd[i]);
		minq.push(rnd[i]);
	}

	printf("pop from maxq :");
	for(int i=0; i<20; ++i){
		printf("%d ", maxq.top());
		maxq.pop();
	}
	printf("\n");

	printf("pop from minq :");
	for(int i=0; i<20; ++i){
		printf("%d ", minq.top());
		minq.pop();
	}
	printf("\n");

	return 0;
}