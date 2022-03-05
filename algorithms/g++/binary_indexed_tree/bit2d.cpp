#include <iostream>
#include <vector>

using namespace std;

template <typename T> // Since we use delta, T must be signed type!
class BinaryIndexedTree2D{
public:
	// if necessary, replace T** with T iarr[][N] for fixed size 2d-array
	BinaryIndexedTree2D(T** iarr, unsigned int row_cnt, unsigned int col_cnt){
		raw_arr.resize(row_cnt+1);
		bit_arr.resize(row_cnt+1);
		for(int r=0; r<=row_cnt; ++r){
			raw_arr[r].resize(col_cnt+1,0);
			bit_arr[r].resize(col_cnt+1,0);
		}

		for(int zr = 0; zr < row_cnt; ++zr){
			for(int zc = 0; zc < col_cnt; ++zc){
				update(zr, zc, iarr[zr][zc]);
			}
		}
	}
	// input index is 0-based, but our internal representation is 1-based
	void update(const unsigned int zrow, const unsigned int zcol, T val){
		unsigned int row = zrow+1;
		unsigned int col = zcol+1;

		T delta = val - raw_arr[row][col];
		raw_arr[row][col] = val;

		unsigned int r = row;
		unsigned int c = col;
		unsigned int rlim = bit_arr.size();
		unsigned int clim = bit_arr[0].size();

		while(r < rlim){
			c = col;
			while(c < clim){
				bit_arr[r][c] += delta;
				c += (c & -c);
			}
			r += (r & -r);
		}
	}

	T cumulative_sum(const unsigned int zrow, const unsigned int zcol){
		unsigned int row = zrow+1;
		unsigned int col = zcol+1;

		T result = 0;
		unsigned int r = row;
		unsigned int c = col;
		unsigned int rlim = bit_arr.size();
		unsigned int clim = bit_arr[0].size();

		while(r){
			c = col;
			while(c){
				result += bit_arr[r][c];
				c &= (c-1);
			}
			r &= (r-1);
		}

		return result;
	}

	T range_sum(const unsigned int beg_zrow, const unsigned int beg_zcol, const unsigned int end_zrow, const unsigned int end_zcol){
		T result = cumulative_sum(end_zrow, end_zcol);
		if(beg_zrow != 0) result -= cumulative_sum(beg_zrow-1, end_zcol);
		if(beg_zcol != 0) result -= cumulative_sum(end_zrow, beg_zcol-1);
		if((beg_zrow != 0) && (beg_zcol != 0)) result += cumulative_sum(beg_zrow-1, beg_zcol-1);
		return result;
	}

	void print_bit(){
		unsigned int rlim = bit_arr.size();
		unsigned int clim = bit_arr[0].size();

		for(int r=0; r<rlim; ++r){
			for(int c=0; c<clim; ++c){
				printf("%d ", bit_arr[r][c]);
			}
			printf("\n");
		}
	}
private:
	vector<vector<T>> raw_arr;
	vector<vector<T>> bit_arr;
};

int main(int argc, char** argv){
	int** iarr = new int*[16];
	for(int i=0; i<16; ++i){
		iarr[i] = new int[16];
		for(int j=0; j<16; ++j) iarr[i][j] = 1;
	}

	BinaryIndexedTree2D<int> bit2d(iarr, 16, 16);
	bit2d.print_bit();
}