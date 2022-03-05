#include <iostream>
#include <unordered_map>

class CEntry;
class FreqLL;

class CEntry{
public:
	CEntry(int _key, int _value) : 
		key(_key), value(_value), prev(nullptr), next(nullptr), freqll(nullptr) {};
	void remove_from_ll(){
		prev->next = next;
		next->prev = prev;
	}
	int key;
	int value;
	CEntry* prev;
	CEntry* next;
	FreqLL* freqll;
};

class FreqLL{
public:
	FreqLL(int _freq) : freq(_freq), up(nullptr), down(nullptr) {
		cehead = new CEntry(-1,-1);
		cetail = new CEntry(-1,-1);
		cehead->next = cetail;
		cetail->prev = cehead;
	};
	~FreqLL(){
		delete cehead;
		delete cetail;
	}
	bool empty(){
		return (cehead->next == cetail);
	}
	void remove_from_ll(){
		up->down = down;
		down->up = up;
	}
	void push_front(CEntry* ce){
		cehead->next->prev = ce;
		ce->next = cehead->next;
		ce->prev = cehead;
		cehead->next = ce;
		ce->freqll = this;
	}
	FreqLL* add_new_freqll_up(){
		FreqLL* newfreqll = new FreqLL(freq+1);
		up->down = newfreqll;
		newfreqll->up = up;
		newfreqll->down = this;
		up = newfreqll;
		return newfreqll;
	}
	int freq;
	FreqLL* up;
	FreqLL* down;
	CEntry* cehead;
	CEntry* cetail;
};

class LFUCache {
public:
	LFUCache(int _capacity) : capacity(_capacity), count(0) {
		flhead = new FreqLL(0x7FFFFFFF);
		fltail = new FreqLL(0);
		flhead->down = fltail;
		fltail->up = flhead;
	}
	
	int get(int key) {
		if(capacity == 0 || kv.find(key) == kv.end()){
			return -1;
		}
		CEntry* ce = kv[key];
		increase_frequency(ce);
		return ce->value;
	}
	
	void put(int key, int value) {
		if(capacity == 0){
			return;
		}
		
		if(kv.find(key) == kv.end()){
			if(count == capacity){
				remove_lfu();
				--count;
			}
			CEntry* newce = new CEntry(key, value);
			kv[key] = newce;
			if(fltail->up->freq != 1){
				fltail->add_new_freqll_up();
			}
			fltail->up->push_front(newce);
			++count;
		}
		else{
			CEntry* ce = kv[key];
			increase_frequency(ce);
			ce->value = value;
		}
	}

private:
	void increase_frequency(CEntry* ce){
		int ce_freq = ce->freqll->freq;
		FreqLL* ce_original_freqll = ce->freqll;

		ce->remove_from_ll();

		if(ce_original_freqll->up->freq == ce_freq+1){
			ce_original_freqll->up->push_front(ce);
		}
		else{
			FreqLL* newup = ce_original_freqll->add_new_freqll_up();
			newup->push_front(ce);
		}

		if(ce_original_freqll->empty()){
			ce_original_freqll->remove_from_ll();
			delete ce_original_freqll;
		}
	}

	void remove_lfu(){
		FreqLL* lfu_freqll = fltail->up;
		CEntry* toremove = lfu_freqll->cetail->prev;

		toremove->remove_from_ll();
		kv.erase(toremove->key);
		delete toremove;

		if(lfu_freqll->empty()){
			lfu_freqll->remove_from_ll();
			delete lfu_freqll;
		}
	}

	int capacity;
	int count;
	FreqLL* flhead;
	FreqLL* fltail;
	std::unordered_map<int, CEntry*> kv;
};

int main(int argc, char** argv){
	LFUCache lfu(2);
	lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
	lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
	std::cout << lfu.get(1) << std::endl;      // return 1
					 // cache=[1,2], cnt(2)=1, cnt(1)=2
	lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
					 // cache=[3,1], cnt(3)=1, cnt(1)=2
	std::cout << lfu.get(2) << std::endl;      // return -1 (not found)
	std::cout << lfu.get(3) << std::endl;      // return 3
					 // cache=[3,1], cnt(3)=2, cnt(1)=2
	lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
					 // cache=[4,3], cnt(4)=1, cnt(3)=2
	std::cout << lfu.get(1) << std::endl;      // return -1 (not found)
	std::cout << lfu.get(3) << std::endl;      // return 3
					 // cache=[3,4], cnt(4)=1, cnt(3)=3
	std::cout << lfu.get(4) << std::endl;      // return 4
}