#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <utility>
#include <queue>
#include <array>
#include <string>
#include <deque>

using namespace std;

const unsigned long long BIT63 = ((unsigned long long)1)<<63;

char A[200002];
char B[200002];
int lenA, lenB;

unsigned long long bitA[4000];
unsigned long long bitB[4000];
int bitlen;

inline void set_bit(unsigned long long* bitarr, int offset){
	bitarr[(offset >> 6)] |= ((unsigned long long)1)<<(offset & 0x3F);
}

inline int get_bit(unsigned long long* bitarr, int offset){
	return (bitarr[(offset >> 6)] & (((unsigned long long)1)<<(offset & 0x3F)));
}

void shift_left(unsigned long long* bitarr, int bitarrlen){
	for(int i=bitarrlen; i > 0; --i){
		bitarr[i] <<= 1;
		bitarr[i] |= (bitarr[i-1] >> 63);
	}
	bitarr[0] <<= 1;
}

unsigned long long arr_and(int bitarrlen){
	unsigned long long and_sum = 0;
	for(int i=0; i<bitarrlen; ++i)
		and_sum += (bitA[i] & bitB[i]);
	// printf("arr_and: %llu\n",and_sum);
	return and_sum;
}

void print_bitarr(unsigned long long* bitarr, int bitarrlen){
	for(int i=bitarrlen-1; i>=0; --i){
		for(int j=63; j>=0; --j){
			if(bitarr[i] & (((unsigned long long)1)<<j))
				printf("1");
			else
				printf("0");
		}
	}
	printf("\n");
}

void solve(){
	int cnt = 0;

	scanf("%s", A);
	scanf("%s", B);
	lenA = strlen(A);
	lenB = strlen(B);

	bitlen = (lenA >> 6);
	bitlen = (lenA & 0x3F) ? bitlen+1 : bitlen;

	for(int i=0; i<bitlen; ++i){
		bitA[i] = 0;
		bitB[i] = 0;
	}

	for(int i=0; i<lenA; ++i){
		if(A[i] == 'M')
			set_bit(bitA, lenA-1-i);
	}
	for(int i=0; i<lenA; ++i){
		if(B[i] == 'M')
			set_bit(bitB, lenA-1-i);
	}

	// print_bitarr(bitA, bitlen);
	// print_bitarr(bitB, bitlen);
	// printf("bitlen: %d\n", bitlen);

	if(!arr_and(bitlen))
		cnt++;

	for(int i=lenA; i<lenB; ++i){
		shift_left(bitB, bitlen);
		// printf("i: %d  B[%d]:%c\n", i, i, B[i]);
		if(B[i] == 'M'){
			bitB[0] |= 1;
		}

		// print_bitarr(bitA, bitlen);
		// print_bitarr(bitB, bitlen);

		if(!arr_and(bitlen))
			cnt++;		
	}

	printf("%d\n", cnt);
}

int main(int argc, char** argv){
	int C;

	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		solve();
	}
}