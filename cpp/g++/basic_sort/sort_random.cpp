#include <iostream>
#include <algorithm>
#include <random>

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

bool custom_compare(int a, int b){
	if((a&1) == 0 && (b&1) == 0){
		return a<b;
	}
	else if ((a&1) == 0){
		return true;
	}
	else if ((b&1) == 0){
		return false;
	}
	else{
		return a<b;
	}
}

int main(){
	int rand_arr[10];
	RNG32<int> rng(-5,5); 

	for(int i=0; i<10; ++i){
		rand_arr[i] = rng();
	}

	printf("Generated random arr:\n");
	for(int i=0; i<10; ++i){
		printf("%d ", rand_arr[i]);
	}
	printf("\n");

	std::sort(&rand_arr[0], &rand_arr[10]);

	printf("After sort:\n");
	for(int i=0; i<10; ++i){
		printf("%d ", rand_arr[i]);
	}
	printf("\n");

	std::sort(&rand_arr[0], &rand_arr[10], std::greater<int>());

	printf("After reversed sort:\n");
	for(int i=0; i<10; ++i){
		printf("%d ", rand_arr[i]);
	}
	printf("\n");

	std::sort(&rand_arr[0], &rand_arr[10], custom_compare);

	printf("After custom sort (even number goes front):\n");
	for(int i=0; i<10; ++i){
		printf("%d ", rand_arr[i]);
	}
	printf("\n");
}