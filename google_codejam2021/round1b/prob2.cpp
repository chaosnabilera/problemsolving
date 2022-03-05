#include <iostream>
#include <numeric>
#include <cstring>
#include <algorithm>

int gcd(int a, int b){
	if(a < b){
		std::swap(a,b);
	}

    if(b == 0){
        return a;
    }else{
        return gcd(b, a%b);
    }
}

void print_intarr(int* arr, int len){
	for(int i=0; i<len; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

bool try_solve(int M, int* U, int N, int A, int B){
	int Z[501] = {0};
	Z[M] = 1;

	for(int i=M; i>0; --i){
		//print_intarr(Z,11);
		//print_intarr(U,11);
		if(Z[i] == 0)
			continue;

		if((i > N) || (U[i] == 0)){
			if(i-A > 0){
				Z[i-A] += Z[i];
			}
			if(i-B > 0){
				Z[i-B] += Z[i];
			}
			Z[i] = 0;
		}
		else{
			int sub = std::min(U[i],Z[i]);
			U[i] -= sub;
			Z[i] -= sub;
			if(Z[i]){
				if(i-A > 0){
					Z[i-A] += Z[i];
				}
				if(i-B > 0){
					Z[i-B] += Z[i];
				}		
			}
		}
	}

	int remain = 0;
	for(int i=0; i<=N; ++i){
		remain += U[i];
	}

	return (remain == 0);
}

int solve(int* U, int N, int A, int B){
	int G = gcd(A,B);
	int K = -1;
	int i=1;
	while(i<=N){
		if(U[i] > 0){
			K = i%G;
			break;
		}
		++i;
	}
	//printf("N:%d A:%d B:%d G:%d K:%d\n",N,A,B,G,K);
	while(i<=N){
		if(U[i]>0 && (i%G)!=K){
			return -1;
		}
		++i;
	}
	for(int m=K; m<=500; m+=G){
		//printf("m:%d\n",m);
		int UU[21] = {0};
		memcpy(UU,U,sizeof(UU));
		if(try_solve(m,UU,N,A,B)){
			return m;
		}
	}

	return -1;
}

int main(int argc, char** argv){
	int T,N,A,B;
	int U[21];
	scanf("%d",&T);
	for(int t=0; t<T; ++t){
		scanf("%d %d %d",&N,&A,&B);
		memset(U,0,sizeof(U));
		for(int u=1; u<=N; ++u){
			scanf("%d", &U[u]);
		}
		//print_intarr(U,21);
		int res = solve(U,N,A,B);
		if(res == -1){
			printf("Case #%d: IMPOSSIBLE\n", t+1);
		}
		else{
			printf("Case #%d: %d\n", t+1, res);
		}
	}
}