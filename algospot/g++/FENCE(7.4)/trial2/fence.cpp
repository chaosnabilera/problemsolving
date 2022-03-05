#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> H;

void get_input(){
	int a;

	scanf("%d", &N);
	H.clear();
	H.reserve(N+1);
	for(int i=0; i<N; ++i){
		scanf("%d", &a);
		H.push_back(a);
	}
}

void solve(){
	vector<int> stack;
	vector<int> LR(N,0);
	vector<int> RL(N,0);
	int maxarea = 0;

	// printf("1\n");

	// L->R
	H.push_back(0);
	stack.clear();
	for(int i=0; i<H.size(); ++i){
		// printf("%d\n",i);
		while(!stack.empty() && H[i] < H[stack.back()]){
			int th = H[stack.back()];
			int ti = stack.back();
			// printf("%d %d\n",th,ti);
			stack.pop_back();
			// printf("ssize:%d\n",stack.size());
			LR[ti] = th*(i-ti);
		}
		stack.push_back(i);
	}

	// printf("2\n");

	// R->L
	H.pop_back();
	reverse(H.begin(),H.end());
	H.push_back(0);
	stack.clear();
	for(int i=0; i<H.size(); ++i){
		while(!stack.empty() && H[i] < H[stack.back()]){
			int th = H[stack.back()];
			int ti = stack.back();
			stack.pop_back();
			RL[N-1-ti] = th*(i-ti);
		}
		stack.push_back(i);
	}

	// printf("3\n");

	H.pop_back();
	reverse(H.begin(),H.end());

	for(int i=0; i<N; ++i)
		maxarea = max(maxarea,LR[i]+RL[i]-H[i]);

	printf("%d\n",maxarea);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}