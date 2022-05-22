#include <iostream>
#include <algorithm>
#include <vector>

int N,M;
std::vector<std::vector<int>> A;

void get_input(){
    scanf("%d%d",&N,&M);

    A.clear();
    A.resize(N);
    for(int i=0; i<N; ++i)
        A[i].resize(M);

    for(int r=0; r<N; ++r)
        for(int c=0; c<M; ++c)
            scanf("%d", &A[r][c]);
}

void solve(){
    std::vector<int> sort_row(M);
    std::vector<int> diff_idx;
    bool diff_exist = false;

    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c)
            sort_row[c] = A[r][c];

        std::sort(sort_row.begin(), sort_row.end());
        diff_idx.clear();
        for(int c=0; c<M; ++c)
            if(A[r][c] != sort_row[c])
                diff_idx.push_back(c);
        
        if(diff_idx.size() > 0){
            diff_exist = true;
            break;
        }
    }

    if(!diff_exist){
        printf("1 1\n");
        return;
    }

    if(diff_idx.size() > 2){
        printf("-1\n");
        return;
    }

    for(int r=0; r<N; ++r)
        std::swap(A[r][diff_idx[0]], A[r][diff_idx[1]]);

    for(int r=0; r<N; ++r){
        for(int c=0; c<M-1; ++c)
            if(A[r][c] > A[r][c+1]){
                printf("-1\n");
                return;
            }
    }

    printf("%d %d\n", diff_idx[0]+1, diff_idx[1]+1);
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        solve();
    }
}