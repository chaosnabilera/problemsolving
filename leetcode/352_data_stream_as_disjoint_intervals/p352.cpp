#include <iostream>
#include <bitset>
#include <map>
#include <vector>

class SummaryRanges {
public:
	/** Initialize your data structure here. */
	SummaryRanges() {
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
					begend.erase(val+1);
				}
				else{
					newend = val;
				}
			}
			else if(exist[vbi+1]){
				newbeg = val;
				newend = begend[val+1];
				begend.erase(val+1);
			}
			else{
				newbeg = val;
				newend = val;
			}
			
			begend[newbeg] = newend;
			endbeg[newend] = newbeg;
		}
	}
	
	std::vector<std::vector<int>> getIntervals() {
		std::vector<std::vector<int>> ret;
		for(auto it : begend){
			std::vector<int> cur;
			ret.push_back({it.first,it.second});
		}
		return ret;
	}

private:
	std::bitset<16384> exist;
	std::map<int,int> begend;
	std::map<int,int> endbeg;
};


int main(int argc, char** argv){
}