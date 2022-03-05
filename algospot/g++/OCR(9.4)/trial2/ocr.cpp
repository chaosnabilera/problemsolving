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
#include <cmath>

using namespace std;

int M,Q;

char Word[500][11];

double Init[500];
double Trans[500][500];
double Inter[500][500];

map<string, int> WordToIdx;
vector<int> Sentence;

double INF = 987654321;
double NEGINF = -numeric_limits<double>::max();
double DP[100][500];

int choice[100][500];

void get_input(){
	scanf("%d %d", &M, &Q);

	WordToIdx.clear();
	for(int i=0; i<M; ++i){
		scanf("%s", Word[i]);
		WordToIdx[Word[i]] = i;
	}

	for(int i=0; i<M; ++i)
		scanf("%lf", &Init[i]);

	for(int i=0; i<M; ++i)
		for(int j=0; j<M; ++j)
			scanf("%lf", &Trans[i][j]);

	for(int i=0; i<M; ++i)
		for(int j=0; j<M; ++j)
			scanf("%lf", &Inter[i][j]);
}

void to_log(){
	for(int i=0; i<M; ++i)
		Init[i] = (Init[i] == 0) ? NEGINF : log(Init[i]);

	// for(int i=0; i<M; ++i)
	// 	printf("%lf ",Init[i]);

	for(int i=0; i<M; ++i)
		for(int j=0; j<M; ++j)
			Trans[i][j] = (Trans[i][j] == 0) ? NEGINF : log(Trans[i][j]);

	for(int i=0; i<M; ++i)
		for(int j=0; j<M; ++j)
			Inter[i][j] = (Inter[i][j] == 0) ? NEGINF: log(Inter[i][j]);
}

int get_max_i(double* arr){
	double maxval = arr[0];
	int maxi = 0;
	for(int i=1; i<M; ++i){
		if(arr[i] > maxval){
			maxval = arr[i];
			maxi = i;
		}
	}
	return maxi;
}

void print_arr(double* arr, int len){
	for(int i=0; i<len; ++i){
		printf("%.8lf ", arr[i]);
	}
	printf("\n");
}

double rec_solve(int i, int w){
	if(DP[i][w] != INF)
		return DP[i][w];

	double val = NEGINF;
	int r = Sentence[i];
	double cand;

	if(i == 0){
		for(int nw=0; nw<M; ++nw){
			cand = Init[w]+Inter[w][r]+Trans[w][nw]+rec_solve(i+1,nw);
			if(val < cand){
				val = cand;
				choice[i][w] = nw;
			}
		}
	}
	else{
		for(int nw=0; nw<M; ++nw){
			cand = Inter[w][r]+Trans[w][nw]+rec_solve(i+1,nw);
			if(val < cand){
				val = cand;
				choice[i][w] = nw;
			}
		}
	}
	// printf("%d %d : %lf\n",i,w,val);
	DP[i][w] = val;
	return val;
}

void rec_print(int i, int w){
	printf("%s ", Word[w]);
	if(i+1 < Sentence.size()){
		rec_print(i+1, choice[i][w]);
	}
}

void solve(){
	for(int i=0; i<Sentence.size(); ++i)
		for(int w=0; w<M; ++w)
			DP[i][w] = INF;

	for(int w=0; w<M; ++w)
		DP[Sentence.size()-1][w] = Inter[w][Sentence[Sentence.size()-1]];

	memset(choice,0,sizeof(choice));

	double maxval = rec_solve(0,0);
	int mw = 0;
	for(int w=1; w<M; ++w){
		double curval = rec_solve(0,w);
		if(maxval < curval){
			maxval = curval;
			mw = w;
		}
	}

	// printf("%lf\n",maxval);
	rec_print(0,mw);
	printf("\n");
}

int main(int argc, char** argv){
	int n;
	char word[0x10];
	
	get_input();
	to_log();
	for(int i=0; i<Q; ++i){
		// printf("<%d>\n",i);
		scanf("%d", &n);
		Sentence.clear();
		Sentence.reserve(n);
		for(int j=0; j<n; ++j){
			scanf("%s", word);
			Sentence.push_back(WordToIdx[word]);
		}
		// for(int s:Sentence){
		// 	printf("%d ",s);
		// }
		// printf("\n");
		solve();
	}
}