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

#define SET_BIT(arr, i) arr[(i>>6)] |= (1ULL << (i & 0x3F));

char A[200001];
char B[200001];
int Alen, Blen, Wlen;

unsigned long long bA[3126];
unsigned long long bB[3126];

void get_input(){
    scanf("%s",A);
    scanf("%s",B);
    Alen = strlen(A);
    Blen = strlen(B);
    Wlen = (Alen & 0x3F) ? (Alen >> 6) + 1 : (Alen >> 6);
}

void shift_array_left(unsigned long long* arr){
    for(int w=0; w<Wlen; ++w){
        arr[w] = arr[w] >> 1;
        arr[w] |= (arr[w+1] & 0x1ULL) << 63;
    }
}

bool get_bit(unsigned long long* arr, int i){
    int ai = i >> 6;
    int bi = i & 0x3F;
    if(arr[ai] & (1ULL << bi))
        return true;
    else
        return false;
}

void print_bit_arr(unsigned long long* arr, int blen){
    for(int i=0; i<blen; ++i){
        if(get_bit(arr,i))
            printf("M");
        else
            printf("F");
    }
    printf("\n");
}

void solve(){
    int cnt = 0;
    memset(bA,0,sizeof(bA));
    memset(bB,0,sizeof(bB));

    for(int i=0; i<Alen; ++i){
        if(A[i] == 'M'){
            SET_BIT(bA,i);
        }
    }
    for(int i=0; i<Alen; ++i){
        if(B[i] == 'M'){
            SET_BIT(bB,i);
        }
    }

    for(int it = Alen; it <= Blen; ++it){
        //print_bit_arr(bB,Alen);

        bool is_allzero = true;
        for(int w=0; w<Wlen; ++w){
            if(bA[w] & bB[w]){
                is_allzero = false;
                break;
            }
        }
        if(is_allzero)
            ++cnt;

        if(it < Blen){
            shift_array_left(bB);
            if(B[it] == 'M'){
                SET_BIT(bB,Alen-1);
            }
        }
    }

    printf("%d\n",cnt);
}

int main(int argc, char** argv){
    int c=0;
    scanf("%d", &c);
    for(int i=0; i<c; ++i){
        get_input();
        solve();
    }
}