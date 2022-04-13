#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int T,N,Q;

void insert_at(int* arr, int cur_arrlen, int ins_idx, int val){
    for(int i=cur_arrlen; i>ins_idx; --i){
        arr[i] = arr[i-1];
    }
    arr[ins_idx] = val;
}

void print_arr(int* arr, int arrlen){
    for(int i=0; i<arrlen; ++i){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void solve(){
    int A[50];
    int Alen = 0;
    int med = 0;
    int a = 0;
    int correct;

    A[0] = 1;
    A[1] = 2;
    A[2] = 3;
    printf("1 2 3\n"); fflush(stdout);
    scanf("%d", &med);
    swap(A[med-1],A[1]);

    for(int n=3; n<N; ++n){
        int v = n+1;
        int l = 0;
        int r = n-1;
        int d,ll,rr;

        while(true){
            d = (r-l+1)/3;
            if(d*3 == (r-l+1)){
                ll = l+d-1;
                rr = r-d+1;
            }
            else{
                ll = l+d;
                rr = r-d;
            }
            printf("%d %d %d\n", A[ll], A[rr], v); fflush(stdout);
            scanf("%d", &med);

            if(med == A[ll]){
                if(ll == l){
                    insert_at(A,n,l,v);
                    break;
                }
                else{
                    r = ll - 1;
                    if(l == r)
                        r++;
                }
            }
            else if(med == A[rr]){
                if(rr == r){
                    insert_at(A,n,r+1,v);
                    break;
                }
                else{
                    l = rr + 1;
                    if(l == r)
                        --l;
                }
            }
            else{ // med == v
                if(rr-ll == 1){
                    insert_at(A,n,rr,v);
                    break;
                }
                else{
                    l = ll+1;
                    r = rr-1;
                    if(l == r)
                        ++r;
                }
            }
        }

        // print_arr(A,n+1);
    }

    for(int i=0; i<N; ++i)
        printf("%d ", A[i]);
    printf("\n");
    fflush(stdout);

    scanf("%d", &correct);
}

int main(int argc, char** argv){
    scanf("%d%d%d", &T, &N, &Q);
    for(int i=0; i<T; ++i){
        solve();
    }
}