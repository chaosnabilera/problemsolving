#include <iostream>

int main(){
	int N;
	int* nums;

	std::cin >> N;

	nums = new int[N];

	for(int i=0; i<N; ++i){
		std::cin >> nums[i];
	}

	std::cout << N;
	for(int i=0; i<N; ++i){
		std::cout << nums[i] << '\n';
	}
}