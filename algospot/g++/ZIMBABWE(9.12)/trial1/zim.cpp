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

const int MODNUM = 1000000007;
const unsigned long long ALREADY_SMALL = (unsigned long long)1 << 63;

unsigned long long Base10[16];

// 2**15 = 32768
int C;
char E[16];
int lenE;
unsigned long long E_lastdigits[16];
int M;
unordered_map<unsigned long long, int> dp;

void precompute(){
	Base10[0] = 1;
	for(int i=1; i<16; ++i){
		Base10[i] = Base10[i-1]*10;
	}
}

void key_to_cntarr(unsigned long long key, int* arr){
	for(int i=0; i<10; ++i){
		arr[i] = key & 0xF;
		key >>= 4;
	}
}

int key_to_modval(unsigned long long key){
	unsigned long long remove_already_small_bit = (0xFFFFFFFFFFFFFFFF ^ ALREADY_SMALL);
	return ((key & remove_already_small_bit) >> 40);
}

unsigned long long modval_cntarr_to_key(int modval, int* arr, bool is_small){
	unsigned long long key = 0;
	for(int i=0; i<10; ++i){
		key |= arr[i] * ((unsigned long long)1 << (i*4));
	}
	key |= modval * ((unsigned long long)1 << 40);

	if(is_small)
		key |= ALREADY_SMALL;

	return key;
}

int num_left_digits(int* dcnt){
	int cnt = 0;
	for(int i=0; i<10; ++i)
		if(dcnt[i])
			++cnt;
	return cnt;
}

int first_left_digit(int* dcnt){
	for(int i=0; i<10; ++i)
		if(dcnt[i])
			return i;
	return -1; //should not come here though...
}

int rec_solve(unsigned long long key){
	if(dp.find(key) != dp.end())
		return dp[key];

	int dcnt[10] = {0};
	int modval = 0;
	int dcnt_sum = 0;
	int res = 0;

	key_to_cntarr(key, dcnt);
	modval = key_to_modval(key);

	for(int d=0; d<10; ++d)
		dcnt_sum += dcnt[d];

	for(int d=0; d<10; ++d){
		if(dcnt[d] == 0)
			continue;

		bool is_small = true;
		int d_e = E[lenE-dcnt_sum]-'0';
		if((key & ALREADY_SMALL) == 0){
			if(d > d_e){
				continue;
			}
			else if(d == d_e){
				is_small = false;
			}
		}

		dcnt[d] -= 1;

		if(d == 0){
			res += rec_solve(modval_cntarr_to_key(modval,dcnt,is_small));
		}
		else{
			unsigned long long headval = d * Base10[dcnt_sum-1];
			int left_digits = num_left_digits(dcnt);

			if(left_digits <= 1){
				int ld = first_left_digit(dcnt);
				unsigned long long tailval = 0;
				for(int t=0; t<dcnt_sum-1; ++t){
					tailval += ld*Base10[t];
				}

				unsigned long long totalval = headval+tailval;

				// printf("totalval: %lld  modval:%d  is_small: %d  ", totalval, modval, is_small);
				if(is_small){
					if(totalval % M == modval){
						// printf("match!\n");
						++res;
					}
					else{
						// printf("no match\n");
					}
				}
				else{
					if(totalval < E_lastdigits[dcnt_sum] && totalval % M == modval){
						// printf("match!\n");
						++res;
					}
					else{
						// printf("no match\n");
					}
				}
			}
			else{
				int target_modval = (M + modval - (headval % M)) % M;
				// printf("headval: %lld  target_modval: %d is_small:%d\n", headval, target_modval, is_small);
				res += rec_solve(modval_cntarr_to_key(target_modval,dcnt,is_small));
			}
		}

		dcnt[d] += 1;

		res %= MODNUM;
	}

	dp[key] = res;

	return dp[key];
}

void solve(){
	unsigned long long key = 0;
	int dcnt[10] = {0};
	lenE = strlen(E);
	dp.clear();

	for(int i=0; i<lenE; ++i)
		dcnt[E[i]-'0']++;

	for(int i=0; i<10; ++i){
		key |= dcnt[i]*((unsigned long long)1<<(i*4));
	}

	E_lastdigits[0] = 0;
	for(int i=1; i<=lenE; ++i){
		unsigned long long curdigit = E[lenE-i]-'0';
		E_lastdigits[i] = E_lastdigits[i-1] + (curdigit*Base10[i-1]);
	}

	// for(int i=0; i<=lenE; ++i){
	// 	printf("%lld\n", E_lastdigits[i]);
	// }
	// printf("%016llx\n",key);

	printf("%d\n", rec_solve(key));
}

int main(int argc, char** argv){
	precompute();

	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%s %d", E, &M);
		solve();
	}
}