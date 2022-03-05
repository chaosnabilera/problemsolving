#include <iostream>
#include <queue>
#include <vector>

class MedianFinder {
public:
	/** initialize your data structure here. */
	MedianFinder() {
		left.push(-9999999);
		right.push(9999999);
	}
	
	void addNum(int num) {
		if(left.size() == right.size()){
			if(num < right.top()){
				left.push(num);
			}
			else{
				left.push(right.top()); right.pop();
				right.push(num);
			}
		}
		else{
			if(num > left.top()){
				right.push(num);
			}
			else{
				right.push(left.top()); left.pop();
				left.push(num);
			}
		}
	}
	
	double findMedian() {
		if(left.size() == right.size()){
			return (left.top() + right.top()) * 0.5;
		}
		else{
			return left.top();
		}
	}

private:
	std::priority_queue<int> left; //maxq
	std::priority_queue<int, std::vector<int>, std::greater<int>> right; //minq
};

int main(int argc, char** argv){
	MedianFinder medianFinder ;
	medianFinder.addNum(1);    // arr = [1]
	medianFinder.addNum(2);    // arr = [1, 2]
	printf("%f\n", medianFinder.findMedian()); // return 1.5 (i.e., (1 + 2) / 2)
	medianFinder.addNum(3);    // arr[1, 2, 3]
	printf("%f\n", medianFinder.findMedian()); // return 2.0

	return 0;
}