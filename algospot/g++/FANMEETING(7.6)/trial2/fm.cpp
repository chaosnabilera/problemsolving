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
#include <cstring>

using namespace std;

unsigned long long Member[3200];
int Memberlen;
int MemberBuflen;
unsigned long long Fan[3200];
int Fanlen;
int FanBuflen;

void convert_to_bit(char* line, int linelen, unsigned long long* buf){
	int bm_cnt = (linelen >> 6)+2;

	for(int i=0; i<bm_cnt; ++i)
		buf[i] = ~(0ULL);

	for(int i=0; i<linelen; ++i){
		int bmi = i >> 6;
		unsigned long long bi = 1ULL << (63 - (i & 0x3F));
		if(line[i] == 'M'){
			buf[bmi] ^= bi;
		}
	}
}

void shift_one_bit(unsigned long long* buf, int buflen){
	const unsigned long long ZeroLastBit = 0xFFFFFFFFFFFFFFFE;
	const unsigned long long AllBit = 0xFFFFFFFFFFFFFFFF;
	unsigned long long choice[2] = { 0, 1 };

	for(int i=0; i<buflen; ++i){
		buf[i] <<= 1;
		buf[i] &= ZeroLastBit;
		buf[i] |= choice[((buf[i+1] >> 63) & 1)];
	}
}

void get_input(){
	char line[200001];	
	scanf("%s", line);
	Memberlen = strlen(line);
	MemberBuflen = Memberlen >> 6;
	if(Memberlen & 0x3F)
		MemberBuflen++;
	convert_to_bit(line, Memberlen, Member);

	scanf("%s", line);
	Fanlen = strlen(line);
	FanBuflen = Fanlen >> 6;
	if(Fanlen & 0x3F)
		FanBuflen++;
	convert_to_bit(line, Fanlen, Fan);
}

void print_bit(unsigned long long* buf, int numbit){
	int bm_cnt = numbit >> 6;
	if(numbit & 0x3F)
		bm_cnt++;

	for(int bmi=0; bmi<bm_cnt; ++bmi){
		for(int i=63; i>=0; --i){
			if(buf[bmi] & (1ULL<<i))
				printf("1");
			else
				printf("0");
		}
	}
	printf("\n");
}

void solve(){
	const unsigned long long AllBit = 0xFFFFFFFFFFFFFFFF;
	int cnt = 0;
	int ilim = Fanlen - Memberlen + 1;
	for(int i=0; i<ilim; ++i){
		bool alltrue = true;
		for(int j=0; j<MemberBuflen; ++j){
			if((Member[j] | Fan[j]) != AllBit){
				alltrue = false;
				break;
			}
		}
		if(alltrue)
			++cnt;
		if(i<ilim-1)
			shift_one_bit(Fan,FanBuflen);
	}

	printf("%d\n",cnt);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}