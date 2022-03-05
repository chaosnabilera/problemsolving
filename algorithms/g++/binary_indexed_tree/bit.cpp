#include <iostream>
#include <vector>

template <typename T> // Since we use delta, T must be signed type!
class BinaryIndexedTree{
public:
	BinaryIndexedTree(T* iarr, unsigned int iarr_size){
		raw_arr.resize(iarr_size+1, 0);
		bit_arr.resize(iarr_size+1, 0);
		for(int zi = 0; zi < iarr_size; ++zi){
			update(zi, iarr[zi]);
		}
	}
	// input index is 0-based, but our internal representation is 1-based
	void update(const unsigned int zi, T val){
		unsigned int i = zi+1;

		T delta = val - raw_arr[i];
		raw_arr[i] = val;

		while(i < bit_arr.size()){
			bit_arr[i] += delta;
			i += (i & -i); // add least significant bit
		}
	}
	T cumulative_sum(const unsigned int zi){
		unsigned int i = zi+1;
		T result = 0;
		while(i){
			result += bit_arr[i];
			i &= (i-1);
		}
		return result;
	}

	T range_sum(const unsigned int beg_zi, const unsigned int end_zi){
		if(beg_zi == 0){
			return cumulative_sum(end_zi);
		}
		return cumulative_sum(end_zi) - cumulative_sum(beg_zi-1);
	}

	void print_bit(){
		for(int i=0; i<bit_arr.size(); ++i){
			printf("%d ", bit_arr[i]);
		}
		printf("\n");
	}
private:
	std::vector<T> raw_arr;
	std::vector<T> bit_arr;
};

int main(int argc, char** argv){
	int iarr[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	BinaryIndexedTree<int> bit(iarr, 16);
	bit.print_bit();

	for(int i=0; i<16; ++i){
		printf("%d ", bit.cumulative_sum(i));
	}
	printf("\n");
}