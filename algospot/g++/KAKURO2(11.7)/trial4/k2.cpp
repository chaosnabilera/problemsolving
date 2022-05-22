#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <utility>

struct HintData{
    int y;
    int x;
    int dir;
    int sum;
    int taken;
    int cnt;
};

int N,Q;

bool Board[20][20];
short HNo[20][20];
short VNo[20][20];
int Avail[(1<<10)][10][46];
int BitCnt[(1<<10)];
int SumVal[(1<<10)];
int Answer[20][20];

std::vector<HintData> Hint;

void get_input(){
    int v,y,x,d,s;

    scanf("%d", &N);
    memset(Board,0,sizeof(Board));
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            scanf("%d", &v);
            Board[r][c] = (v == 1);
        }
    }

    Hint.clear();
    scanf("%d", &Q);
    for(int i=0; i<Q; ++i){
        scanf("%d%d%d%d", &y, &x, &d, &s);
        --y; --x;
        HintData hd = {y,x,d,s,0,0};
        Hint.push_back(hd);
    }
}

void set_hint_number(){
    memset(HNo, 0xFF, sizeof(HNo));
    memset(VNo, 0xFF, sizeof(VNo));

    for(int i=0; i<Hint.size(); ++i){
        HintData& h = Hint[i];
        int r,c;

        if(h.dir == 0){ // horizontal
            r = h.y;
            c = h.x+1;
            while(c < N && Board[r][c]){
                HNo[r][c] = i;
                ++c;
                ++h.cnt;
            }
        }
        else{ // vertical
            r = h.y+1;
            c = h.x;
            while(r < N && Board[r][c]){
                VNo[r][c] = i;
                ++r;
                ++h.cnt;
            }
        }
    }
}

void precompute_availability(){
    for(int elem = (1<<1); elem < (1<<10); elem += 2){
        BitCnt[elem] = 0;
        SumVal[elem] = 0;
        for(int b=1; b<10; ++b){
            if((1<<b) & elem){
                ++BitCnt[elem];
                SumVal[elem] += b;
            }
        }
    }

    for(int elem = (1<<1); elem < (1<<10); elem += 2){
        int subset = elem;
        while(subset > 0){
            Avail[elem][BitCnt[subset]][SumVal[subset]] |= subset; 
            subset = (subset - 1) & elem;
        }
    }
}

void print_table(short table[][20]){
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            printf("%3d",table[r][c]);
        }
        printf("\n");
    }
}

int get_candidate(int r, int c){
    HintData& hh = Hint[HNo[r][c]];
    HintData& vh = Hint[VNo[r][c]];

    int avail_h = 0x3FE ^ hh.taken;
    int cnt_h = hh.cnt - BitCnt[hh.taken];
    int sum_h = hh.sum - SumVal[hh.taken];

    int avail_v = 0x3FE ^ vh.taken;
    int cnt_v = vh.cnt - BitCnt[vh.taken];
    int sum_v = vh.sum - SumVal[vh.taken];

    return Avail[avail_h][cnt_h][sum_h] & Avail[avail_v][cnt_v][sum_v];
}

void put_num(int r, int c, int num){
    Answer[r][c] = num;
    Hint[HNo[r][c]].taken |= (1<<num);
    Hint[VNo[r][c]].taken |= (1<<num);
}

void cancel_num(int r, int c, int num){
    Answer[r][c] = 0;
    Hint[HNo[r][c]].taken &= ~(1<<num);
    Hint[VNo[r][c]].taken &= ~(1<<num);
}

bool rec_solve(){
    std::vector<std::pair<int,int>> to_put;
    int best_candidate = 0x3FE;
    int br = -1; int bc = -1;

    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            if(Board[r][c] && Answer[r][c] == 0){
                to_put.push_back(std::make_pair(r,c));
            }
        }
    }

    if(to_put.empty()){
        return true;
    }

    for(std::pair<int,int>& p: to_put){
        int r = p.first; int c = p.second;
        int cand = get_candidate(r,c);

        if(BitCnt[cand] <= BitCnt[best_candidate]){
            best_candidate = cand;
            br = r;
            bc = c;
        }
    }

    if(best_candidate > 0){
        for(int b=1; b<10; ++b){
            if(best_candidate & (1<<b)){
                put_num(br,bc,b);
                bool res = rec_solve();
                if(res){
                    return true;
                }
                cancel_num(br,bc,b);
            }
        }
    }

    return false;
}

void solve(){
    set_hint_number();
    memset(Answer,0,sizeof(Answer));
    rec_solve();
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            printf("%d ", Answer[r][c]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv){
    int t;
    precompute_availability();
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        solve();
    }
}