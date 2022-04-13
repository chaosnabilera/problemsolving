#include <iostream>
#include <tuple>
#include <map>

long long intpow(long long N, int P);

std::map<std::tuple<long long,long long,long long>,std::tuple<int, int, int>> angle_to_time;

const long long NANOSECOND = intpow(10,9);
const long long ROUND = 12*60*60*NANOSECOND;
const long long TICK_TO_DEGREE = 12*intpow(10,10);

long long intpow(long long N, int P){
	if(P == 0){
		return 1;
	}
	long long res = N;
	for(int p=1; p<P; ++p){
		res *= N;
	}
	return res;
}

bool try_solve(long long hn, long long mn, long long sn){
	bool result = false;
	for(long long _h=0; _h<12; ++_h){
		long long h = _h;
		long long hmdiff = hn-mn;
		long long n11 = (h*3600*NANOSECOND)-hmdiff;
		if (n11 % 11 != 0) {
			continue;
		}
		long long n = n11/11;

		// if(n < 0){
		// 	h = (h > 0) ? h-1 : 11;
		// 	n = (30*TICK_TO_DEGREE) + n;
		// }

		long long ref_hn = (h*3600*NANOSECOND)+n;
		long long ref_mn = (12*((n+ROUND)%ROUND))%ROUND;
		long long ref_sn = (720*((n+ROUND)%ROUND))%ROUND;

		long long delta = ref_hn-hn;
		long long dhn = (hn+delta+ROUND)%ROUND;
		long long dmn = (mn+delta+ROUND)%ROUND;
		long long dsn = (sn+delta+ROUND)%ROUND;

		// printf("<%lld> %lld %lld %lld\n", h, dhn/TICK_TO_DEGREE, dmn/TICK_TO_DEGREE, dsn/TICK_TO_DEGREE);
		// printf("       %lld %lld %lld\n", dhn, dmn, dsn);
		// printf("       %lld %lld %lld\n", ref_hn, ref_mn, ref_sn);

		if((ref_hn == dhn) && (ref_mn == dmn) && (ref_sn == dsn)){
			long long hh = (ref_hn / (3600*NANOSECOND)) % 12;
			long long mm = (ref_hn / (60*NANOSECOND)) % 60;
			long long ss = (ref_hn / NANOSECOND) % 60;
			long long nn = ref_hn % NANOSECOND;

			printf("%lld %lld %lld %lld\n",hh,mm,ss,nn);
			result = true;
			break;
		}
	}
	return result;
}

void solve(long long A, long long B, long long C){
	do{
		if(try_solve(A,B,C)) break;
		if(try_solve(A,C,B)) break;
		if(try_solve(B,A,C)) break;
		if(try_solve(B,C,A)) break;
		if(try_solve(C,A,B)) break;
		if(try_solve(C,B,A)) break;
	} while(0);
}

int main(int arbc, char** argv){
	int T;
	long long A,B,C;
	scanf("%d", &T);
	for(int t=0; t<T; ++t){
		scanf("%lld %lld %lld", &A, &B, &C);
		printf("Case #%d: ",t+1);
		solve(A,B,C);
	}
}