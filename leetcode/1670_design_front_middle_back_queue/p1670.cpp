#include <iostream>
#include <deque>

class FrontMiddleBackQueue {
public:
	FrontMiddleBackQueue() {
	}
	
	void pushFront(int val) {
		front.push_front(val);
		rebalance();
	}
	
	void pushMiddle(int val) {
		if(front.size() == back.size()){
			front.push_back(val);
		}
		else{
			back.push_front(front.back());
			front.pop_back();
			front.push_back(val);
		}
		rebalance();
	}
	
	void pushBack(int val) {
		back.push_back(val);
		rebalance();
	}
	
	int popFront() {
		int retval = -1;
		if(front.size() > 0){
			retval = front.front();
			front.pop_front();
			rebalance();
		}
		return retval;
	}
	
	int popMiddle() {
		int retval = -1;
		if(front.size() > 0){
			retval = front.back();
			front.pop_back();
			rebalance();
		}
		return retval;
	}
	
	int popBack() {
		int retval = -1;

		if(back.size() > 0){
			retval = back.back();
			back.pop_back();
			rebalance();
		}
		else if(front.size() > 0){
			retval = front.back();
			front.pop_back();
			rebalance();
		}

		return retval;
	}
	void print(){
		printf("[ ");
		for(auto it : front){
			printf("%d ", it);
		}
		for(auto it : back){
			printf("%d ", it);
		}
		printf("]\n");
	}
private:
	void rebalance(){
		if (back.size() > front.size()){
			front.push_back(back.front());
			back.pop_front();
		}
		if (front.size() - back.size() > 1){
			back.push_front(front.back());
			front.pop_back();
		}
	}
	std::deque<int> front;
	std::deque<int> back;
};

int main(int argc, char** argv){
	FrontMiddleBackQueue q;
	q.pushFront(1);   // [1]
	q.print();
	q.pushBack(2);    // [1, 2]
	q.print();
	q.pushMiddle(3);  // [1, 3, 2]
	q.print();
	q.pushMiddle(4);  // [1, 4, 3, 2]
	q.print();
	q.popFront();     // return 1 -> [4, 3, 2]
	q.print();
	q.popMiddle();    // return 3 -> [4, 2]
	q.print();
	q.popMiddle();    // return 4 -> [2]
	q.print();
	q.popBack();      // return 2 -> []
	q.print();
	q.popFront();     // return -1 -> [] (The queue is empty)
	q.print();
}