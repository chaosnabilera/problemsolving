#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

class AllOne {
public:
	/** Initialize your data structure here. */
	AllOne() {
		maxheap.push_back( std::make_pair(std::numeric_limits<unsigned long long>::max(),std::numeric_limits<unsigned int>::max()) );
		minheap.push_back( std::make_pair(std::numeric_limits<unsigned long long>::max(),std::numeric_limits<unsigned int>::max()) );
	}

	std::pair<unsigned long long, unsigned int> str_to_pair(std::string& str){
		char sseq[12] = {0};
		for(int i=0; i<str.size(); ++i){
			sseq[i] = str[i];
		}
		unsigned long long key_l1 = *(unsigned long long*)(&sseq[0]);
		unsigned int key_l2 = *(unsigned int*)(&sseq[8]);
		return std::make_pair(key_l1, key_l2);
	}

	std::string pair_to_str(std::pair<unsigned long long, unsigned int> pair){
		char key_seq[12] = {0};
		*(unsigned long long*)(&key_seq[0]) = pair.first;
		*(unsigned int*)(&key_seq[8]) = pair.second;
		return std::string(key_seq);
	}
	
	/** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
	void inc(std::string key) {
		std::pair<unsigned long long, unsigned int> keypair = str_to_pair(key);
		if(cnt.find(keypair) == cnt.end()){
			cnt[keypair] = 1;
			idx[keypair] = std::pair<int,int>(maxheap.size(), minheap.size());
			maxheap.push_back(keypair);
			minheap.push_back(keypair);
			rebalance_maxheap_up(keypair);
			rebalance_minheap_up(keypair);
		}
		else{
			cnt[keypair] += 1;
			rebalance_maxheap_up(keypair);
			rebalance_minheap_down(keypair);
		}
		// std::cout << "inc " << key << "  ";
		// print();
	}
	
	/** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
	void dec(std::string key) {
		std::pair<unsigned long long, unsigned int> keypair = str_to_pair(key);

		// std::cout << "dec " << key << "  ";

		if(cnt[keypair] == 1){
			int maxheap_idx = idx[keypair].first;
			int minheap_idx = idx[keypair].second;

			// std::cout << "maxheap_idx: " << maxheap_idx << "  " << "minheap_idx: " << minheap_idx << "  "; 

			if (maxheap_idx != maxheap.size()-1){
				maxheap[maxheap_idx] = maxheap[maxheap.size()-1];
				maxheap.pop_back();
				idx[maxheap[maxheap_idx]].first = maxheap_idx;
				rebalance_maxheap_down(maxheap[maxheap_idx]);
			}
			else{
				maxheap.pop_back();
			}

			if (minheap_idx != minheap.size()-1){
				minheap[minheap_idx] = minheap[minheap.size()-1];
				minheap.pop_back();
				idx[minheap[minheap_idx]].second = minheap_idx;
				rebalance_minheap_down(minheap[minheap_idx]);
			}
			else{
				minheap.pop_back();
			}

			cnt.erase(keypair);
			idx.erase(keypair);
		}
		else{
			cnt[keypair] -= 1;
			rebalance_maxheap_down(keypair);
			rebalance_minheap_up(keypair);
		}
		
		// print();
	}

	void rebalance_maxheap_up(std::pair<unsigned long long, unsigned int> keypair){
		int curidx = idx[keypair].first;
		int cntval = cnt[keypair];
		int parentidx = curidx >> 1;

		while(parentidx > 0){
			std::pair<unsigned long long, unsigned int> parent_keypair = maxheap[parentidx];
			if(cnt[parent_keypair] < cntval){
				// swap idx
				idx[parent_keypair].first = curidx;
				idx[keypair].first = parentidx;
				// swap maxheap position
				maxheap[parentidx] = keypair;
				maxheap[curidx] = parent_keypair;
				// move up
				curidx = parentidx;
				parentidx = curidx >> 1;	
			}
			else{
				break;
			}
		}
	}

	void rebalance_maxheap_down(std::pair<unsigned long long, unsigned int> keypair){
		int curidx = idx[keypair].first;
		int cntval = cnt[keypair];
		int child_left_idx = curidx << 1;
		int child_right_idx = child_left_idx+1;

		while(child_left_idx < maxheap.size()){
			if(cntval < cnt[maxheap[child_left_idx]]){
				std::pair<unsigned long long, unsigned int> child_left_keypair = maxheap[child_left_idx];
				// swap idx
				idx[child_left_keypair].first = curidx;
				idx[keypair].first = child_left_idx;
				// swap maxheap position
				maxheap[child_left_idx] = keypair;
				maxheap[curidx] = child_left_keypair;
				// move down
				curidx = child_left_idx;
				child_left_idx = curidx << 1;
				child_right_idx = child_left_idx+1;
			}
			else if(child_right_idx < maxheap.size() && cntval < cnt[maxheap[child_right_idx]]){
				std::pair<unsigned long long, unsigned int> child_right_keypair = maxheap[child_right_idx];
				// swap idx
				idx[child_right_keypair].first = curidx;
				idx[keypair].first = child_right_idx;
				// swap maxheap position
				maxheap[child_right_idx] = keypair;
				maxheap[curidx] = child_right_keypair;
				// move down
				curidx = child_right_idx;
				child_left_idx = curidx << 1;
				child_right_idx = child_left_idx+1;
			}
			else{
				break;
			}
		}
	}

	void rebalance_minheap_up(std::pair<unsigned long long, unsigned int> keypair){
		int curidx = idx[keypair].second;
		int cntval = cnt[keypair];
		int parentidx = curidx >> 1;

		while(parentidx > 0){
			std::pair<unsigned long long, unsigned int> parent_keypair = minheap[parentidx];
			if(cnt[parent_keypair] > cntval){
				// swap idx
				idx[parent_keypair].second = curidx;
				idx[keypair].second = parentidx;
				// swap minheap position
				minheap[parentidx] = keypair;
				minheap[curidx] = parent_keypair;
				// move up
				curidx = parentidx;
				parentidx = curidx >> 1;	
			}
			else{
				break;
			}
		}
	}

	void rebalance_minheap_down(std::pair<unsigned long long, unsigned int> keypair){
		int curidx = idx[keypair].second;
		int cntval = cnt[keypair];
		int child_left_idx = curidx << 1;
		int child_right_idx = child_left_idx+1;

		while(child_left_idx < minheap.size()){
			if(cntval > cnt[minheap[child_left_idx]]){
				std::pair<unsigned long long, unsigned int> child_left_keypair = minheap[child_left_idx];
				// swap idx
				idx[child_left_keypair].second = curidx;
				idx[keypair].second = child_left_idx;
				// swap minheap position
				minheap[child_left_idx] = keypair;
				minheap[curidx] = child_left_keypair;
				// move down
				curidx = child_left_idx;
				child_left_idx = curidx << 1;
				child_right_idx = child_left_idx+1;
			}
			else if(child_right_idx < minheap.size() && cntval > cnt[minheap[child_right_idx]]){
				std::pair<unsigned long long, unsigned int> child_right_keypair = minheap[child_right_idx];
				// swap idx
				idx[child_right_keypair].second = curidx;
				idx[keypair].second = child_right_idx;
				// swap minheap position
				minheap[child_right_idx] = keypair;
				minheap[curidx] = child_right_keypair;
				// move down
				curidx = child_right_idx;
				child_left_idx = curidx << 1;
				child_right_idx = child_left_idx+1;
			}
			else{
				break;
			}
		}
	}
	
	/** Returns one of the keys with maximal value. */
	std::string getMaxKey() {
		if(maxheap.size() > 1){
			return pair_to_str(maxheap[1]);
		}
		else{
			return "";
		}
	}
	
	/** Returns one of the keys with Minimal value. */
	std::string getMinKey() {
		if(minheap.size() > 1){
			return pair_to_str(minheap[1]);
		}
		else{
			return "";
		}
	}

	void print(){
		std::cout << "max: [";
		for(int i=1; i<maxheap.size(); ++i){
			std::cout << pair_to_str(maxheap[i]) << "(" << cnt[maxheap[i]] << ") ";
		}
		std::cout << "]    ";

		std::cout << "min: [";
		for(int i=1; i<minheap.size(); ++i){
			std::cout << pair_to_str(minheap[i]) << "(" << cnt[minheap[i]] << ") ";
		}
		std::cout << "]    " ;

		std::cout << "idx: [";
		for(auto it: idx){
			std::cout << pair_to_str(it.first) << "(" << it.second.first << "," << it.second.second << ")   ";
		}
		std::cout << "]" << std::endl;
	}

private:
	std::map<std::pair<unsigned long long, unsigned int>, std::pair<int,int>> idx;
	std::map<std::pair<unsigned long long, unsigned int>, int> cnt;
	std::vector<std::pair<unsigned long long, unsigned int>> maxheap;
	std::vector<std::pair<unsigned long long, unsigned int>> minheap;
};


int main(int argc, char** argv){
	AllOne allOne;
	allOne.inc("a");
	allOne.inc("b");
	allOne.inc("b");
	allOne.inc("c");
	allOne.inc("c");
	allOne.inc("c");
	allOne.dec("b");
	allOne.dec("b");
	std::cout << allOne.getMinKey() << std::endl;
	allOne.dec("a");
	std::cout << allOne.getMaxKey() << std::endl;
	std::cout << allOne.getMinKey() << std::endl;
}