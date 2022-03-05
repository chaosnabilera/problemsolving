#include <random>
#include <limits>
#include <utility>
#include <unordered_map>
#include <unordered_set>

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

class RandomizedCollection {
public:
	/** Initialize your data structure here. */
	RandomizedCollection() {
	}
	
	/** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
	bool insert(int val) {
		bool is_new = (eidx.find(val) == eidx.end());
		eidx[val].insert(element.size());
		element.push_back(val);
		// print();
		return is_new;
	}
	
	/** Removes a value from the collection. Returns true if the collection contained the specified element. */
	bool remove(int val) {
		if(eidx.find(val) == eidx.end()){
			// print();
			return false;
		}

		int val_idx = *eidx[val].begin();
		int end_elem = element[element.size()-1];

		if(end_elem == val){
			eidx[val].erase(element.size()-1);
		}
		else{
			eidx[val].erase(val_idx);
			element[val_idx] = end_elem;
			eidx[end_elem].erase(element.size()-1);
			eidx[end_elem].insert(val_idx);
		}

		element.pop_back();
		if(eidx[val].empty()){
			eidx.erase(val);
		}

		// print();
		return true;
	}
	
	/** Get a random element from the collection. */
	int getRandom() {
		// print();
		return element[rng()%element.size()];
	}

	void print(){
		printf("[");
		for(auto it:element){
			printf("%d ", it);
		}
		printf("]\n");
	}
private:
	RNG32<int> rng;
	std::vector<int> element;
	std::unordered_map<int, std::unordered_set<int>> eidx;
};

int main(int argc, char** argv){
	return 0;
}