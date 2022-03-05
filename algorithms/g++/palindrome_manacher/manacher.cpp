#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <cstring>

int* manacher_odd(char* istr, int istrlen){
	int R = 0;
	int p = 0;
	int* plen = new int[istrlen];
	memset(plen, 0, sizeof(int)*istrlen);

	for(int i=0; i<istrlen; ++i){
		int li = (i < R) ? std::min(plen[2*p-i], R-i) : 0;
		int init_li = li;

		while((i-li-1 >= 0) && (i+li+1 < istrlen) && (istr[i-li-1] == istr[i+li+1])){
			++li;
		}
		plen[i] = li;

		// printf("%d: %d -> %d\n", i, init_li, li);

		if(i+plen[i] > R){
			p = i;
			R = i+plen[i];
		}
	}

	return plen;
}

int* manacher_even(char* istr, int istrlen){
	int R = 0;
	int p = 0;
	int* plen = new int[istrlen];
	memset(plen, 0, sizeof(int)*istrlen);

	for(int i=0; i<istrlen; ++i){
		int li = (i < R) ? std::min(plen[2*p-i], R-i) : 0;
		int init_li = li;

		while((i-li-1 >= 0) && (i+li < istrlen) && (istr[i-li-1] == istr[i+li])){
			++li;
		}
		plen[i] = li;

		// printf("%d: %d -> %d\n", i, init_li, li);

		if(i+plen[i] > R){
			p = i;
			R = i+plen[i];
		}
	}

	return plen;
}

void print_iarr(int* arr, int arrlen){
	for(int i=0; i<arrlen; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void print_carr(char* arr, int arrlen){
	for(int i=0; i<arrlen; ++i){
		printf("%c", arr[i]);
	}
	printf("\n");
}

int main(int argc, char** argv){
	char istr[] = "abcbadabcbazxwpqrqpzpqrpprqpzpqrqpwxz";
	// char istr[] = "babad";
	// char istr[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	int istrlen = strlen(istr);

	int* ans_odd = manacher_odd(istr, istrlen);

	print_iarr(ans_odd, istrlen);
	for(int i=0; i<istrlen; ++i){
		if(ans_odd[i] > 0){
			print_carr(&istr[i-ans_odd[i]], ans_odd[i]*2+1);
		}
	}

	int* ans_even = manacher_even(istr, istrlen);
	print_iarr(ans_even, istrlen);
	for(int i=0; i<istrlen; ++i){
		if(ans_even[i] > 0){
			print_carr(&istr[i-ans_even[i]], ans_even[i]*2);
		}
	}

	return 0;
}