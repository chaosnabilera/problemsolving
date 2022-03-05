#include <iostream>
#include <bitset>
#include <set>
#include <vector>

class SummaryRanges {
public:
	/** Initialize your data structure here. */
	SummaryRanges() {
		memset(exist, 0, sizeof(exist));
		memset(begend, 0, sizeof(begend));
		memset(endbeg, 0, sizeof(endbeg));
	}
	
	void addNum(int val) {
		int vbi = val+1;
		int newbeg = -1;
		int newend = -1;

		if(!exist[vbi]){
			exist[vbi] = true;

			if(exist[vbi-1]){
				newbeg = endbeg[val-1];
				if(exist[vbi+1]){
					newend = begend[val+1];
					beg.erase(val+1);
				}
				else{
					newend = val;
				}
			}
			else if(exist[vbi+1]){
				newbeg = val;
				newend = begend[val+1];
				beg.erase(val+1);
				beg.insert(val);
			}
			else{
				beg.insert(val);
				newbeg = val;
				newend = val;
			}
			
			begend[newbeg] = newend;
			endbeg[newend] = newbeg;
		}
	}
	
	std::vector<std::vector<int>> getIntervals() {
		std::vector<std::vector<int>> ret;
		for(auto b : beg){
			ret.push_back({b,begend[b]});
		}
		return ret;
	}

private:
	bool exist[10001];
	int begend[10001];
	int endbeg[10001];
	std::set<int> beg;
};


int main(int argc, char** argv){
}