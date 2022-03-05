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

const int MODNUM = 1000000007;

char E[16];
int Elen;
int M;
char O[16];
int DP[(1<<15)][20][2];

int NumBits[(1<<15)];

void precompute(){
	int ilim = 1<<15;
	for(int i=0; i<ilim; ++i){
		NumBits[i] = 0;
		for(int b=0; b<15; ++b)
			if(i & (1<<b))
				++NumBits[i];
	}
}

int rec_solve(int available, int target_mod, int status){
	if(DP[available][target_mod][status] != -1)
		return DP[available][target_mod][status];

	if(available == 0){
		if(target_mod == 0)
			if(status == 0)
				DP[available][target_mod][status] = 0;
			else
				DP[available][target_mod][status] = 1;
		else
			DP[available][target_mod][status] = 0;

		// printf("1 DP[%d][%d][%d] = %d\n",available,target_mod,status, DP[available][target_mod][status]);
		return DP[available][target_mod][status];
	}

	vector<int> bits;
	// printf("Elen:%d\n",Elen);
	for(int b=0; b<Elen; ++b){
		if(available & (1<<b)){
			// printf("?b:%d\n",b);
			bits.push_back(b);
		}
		// printf("!b:%d\n",b);
	}
	// printf("%lu %d\n",bits.size(), available);

	// for(int b:bits)
	// 	printf("%d ",b);
	// printf("\n");

	int val = 0;
	int ei = NumBits[(1<<Elen)-1] - NumBits[available];
	long long factor10 = 1;
	for(int i=ei; i<Elen-1; ++i)
		factor10 *= 10;

	if(status == 0){ // same. so the number we choose must be less or equal to E[ei]
		for(int i=0; i<bits.size(); ++i){
			int b = bits[i];

			if( (i == 0 || O[bits[i]] != O[bits[i-1]]) && (O[b] <= E[ei]) ){
				long long curfront = O[b]*factor10;
				int next_target_mod = (target_mod - (curfront % M) + M) % M;
				if(O[b] == E[ei])
					val = (val + rec_solve(available ^ (1<<b), next_target_mod, 0)) % MODNUM;
				else
					val = (val + rec_solve(available ^ (1<<b), next_target_mod, 1)) % MODNUM;
			}
		}
	}
	else{ // already smaller
		for(int i=0; i<bits.size(); ++i){
			int b = bits[i];
			if(i==0 || O[bits[i]] != O[bits[i-1]]){
				long long curfront = O[b]*factor10;
				int next_target_mod = (target_mod - (curfront % M) + M) % M;
				val = (val + rec_solve(available ^ (1<<b), next_target_mod, 1)) % MODNUM;
			}
		}
	}

	DP[available][target_mod][status] = val;
	// printf("2 DP[%d][%d][%d] = %d\n",available,target_mod,status,DP[available][target_mod][status]);
	return val;
}

void solve(){
	Elen = strlen(E);
	for(int i=0; i<Elen; ++i)
		E[i] -= '0';

	memcpy(O,E,sizeof(E));
	sort(&O[0],&O[Elen]);

	// printf("Elen: %d\n",Elen);
	// printf("E: ");
	// for(int i=0; i<Elen; ++i)
	// 	printf("%d ",E[i]);
	// printf("\n");
	// printf("O: ");
	// for(int i=0; i<Elen; ++i)
	// 	printf("%d ",O[i]);
	// printf("\n");

	memset(DP,0xFF,sizeof(DP));

	printf("%d\n", rec_solve((1<<Elen)-1, 0, 0));
}

int main(int argc, char** argv){
	int c;
	precompute();
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		scanf("%s %d", E, &M);
		solve();
	}
}