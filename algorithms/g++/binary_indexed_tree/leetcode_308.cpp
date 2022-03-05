class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        unsigned int row_cnt = matrix.size();
        unsigned int col_cnt = matrix[0].size();

        raw_arr.resize(row_cnt+1);
        bit_arr.resize(row_cnt+1);
        for(int r=0; r<=row_cnt; ++r){
            raw_arr[r].resize(col_cnt+1,0);
            bit_arr[r].resize(col_cnt+1,0);
        }

        for(int zr = 0; zr < row_cnt; ++zr){
            for(int zc = 0; zc < col_cnt; ++zc){
                update(zr, zc, matrix[zr][zc]);
            }
        }
    }
    
    void update(int zrow, int zcol, int val) {
        unsigned int row = zrow+1;
        unsigned int col = zcol+1;

        int delta = val - raw_arr[row][col];
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

    int cumulative_sum(const unsigned int zrow, const unsigned int zcol){
        unsigned int row = zrow+1;
        unsigned int col = zcol+1;

        int result = 0;
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
    
    int sumRegion(int beg_zrow, int beg_zcol, int end_zrow, int end_zcol) {
        int result = cumulative_sum(end_zrow, end_zcol);
        if(beg_zrow != 0) result -= cumulative_sum(beg_zrow-1, end_zcol);
        if(beg_zcol != 0) result -= cumulative_sum(end_zrow, beg_zcol-1);
        if((beg_zrow != 0) && (beg_zcol != 0)) result += cumulative_sum(beg_zrow-1, beg_zcol-1);
        return result;
    }

private:
    std::vector<std::vector<int>> raw_arr;
    std::vector<std::vector<int>> bit_arr;
};