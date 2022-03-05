#include <iostream>

int main(){
	int N;
	int* nums;

	scanf("%d", &N);

	nums = new int[N];

	for(int i=0; i<N; ++i){
		scanf("%d", &nums[i]);
	}

	printf("%d\n", N);
	for(int i=0; i<N; ++i){
		printf("%d\n", nums[i]);
	}
}