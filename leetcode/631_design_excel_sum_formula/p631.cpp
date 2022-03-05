#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

struct Cell{
	Cell(): value(0) {}
	int value;
	std::unordered_multiset<unsigned int> in_rc;	
	std::unordered_multiset<unsigned int> out_rc;
};

class Excel {
public:
	Excel(int _height, char _width) : height(_height), width(_width) {
		_cellarr = new Cell[height*width];
	}
	
	void set(int row, char column, int val) {
		int r = row-1;
		int c = column-'A';
		int cellkey = (r << 8) | c;
		Cell& cell = at(r,c);
		int delta = val - cell.value;
		cell.value = val;

		if(!cell.in_rc.empty()){
			remove_sum(cell, cellkey);
		}
			
		for(auto outkey : cell.out_rc){
			add_delta((outkey & 0xFF00) >> 8, outkey & 0xFF, delta);
		}
	}

	void remove_sum(Cell& cell, int cellkey){
		for(auto inkey : cell.in_rc){
			Cell& icell = at((inkey & 0xFF00) >> 8, inkey & 0xFF);
			icell.out_rc.erase(cellkey);
		}
		cell.in_rc.clear();
	}

	void add_delta(int r, int c, int delta){
		Cell& cell = at(r,c);
		cell.value += delta;
		for(auto outkey : cell.out_rc){
			add_delta((outkey & 0xFF00) >> 8, outkey & 0xFF, delta);	
		}
	}
	
	int get(int row, char column) {
		return at(row-1, column-'A').value;
	}
	
	int sum(int row, char column, std::vector<std::string> numbers) {
		int r = row-1;
		int c = column-'A';
		int cellkey = (r << 8) | c;
		Cell& cell = at(r,c);
		cell.value = 0;

		if(!cell.in_rc.empty()){
			remove_sum(cell, cellkey);
		}
		for(auto token : numbers){
			if(token.size() > 3){
				int r1,c1,r2,c2;
				convert_colrow(token,r1,c1,r2,c2);
				for(int rr = r1; rr <= r2; ++rr){
					for(int cc = c1; cc <= c2; ++cc){
						cell.in_rc.insert((rr << 8) | cc);
						Cell& icell = at(rr,cc);
						icell.out_rc.insert(cellkey);
						cell.value += icell.value;
					}
				}
			}
			else{
				int cc = token[0]-'A';
				int rr = (token.size() == 2) ? token[1] - '1' : (token[1]-'0')*10 + (token[2]-'0') - 1;
				cell.in_rc.insert((rr << 8) | cc);
				Cell& icell = at(rr,cc);
				icell.out_rc.insert(cellkey);
				cell.value += icell.value;
			}
		}

		return cell.value;
	}
private:
	const int height;
	const int width;
	Cell* _cellarr;

	inline Cell& at(int r, int c) {return _cellarr[(r*height)+c];}
	inline void convert_colrow(std::string& cr, int& r1, int& c1, int& r2, int& c2){
		if(cr[2] == ':'){
			c1 = cr[0]-'A';
			r1 = cr[1]-'1';
			if(cr.size() == 5){
				c2 = cr[3]-'A';
				r2 = cr[4]-'1';
			}
			else{
				c2 = cr[3]-'A';
				r2 = (cr[4]-'0')*10 + (cr[5]-'0') - 1;
			}
		}
		else{
			c1 = cr[0]-'A';
			r1 = (cr[1]-'0')*10 + (cr[2]-'0') - 1;
			if(cr.size() == 6){
				c2 = cr[4]-'A';
				r2 = cr[5]-'1';
			}
			else{
				c2 = cr[4]-'A';
				r2 = (cr[5]-'0')*10 + (cr[6]-'0') - 1;
			}
		}
	}
};