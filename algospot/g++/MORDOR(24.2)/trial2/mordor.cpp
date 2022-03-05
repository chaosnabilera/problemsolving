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

// Range Min Query. Segment tree의 일종. array based binary tree로 구현됨
// 총 데이터가 x개라고 하면 2*(2^n), (2^n) >= x 짜리 array를 만들어 여기에 저장한다
// index 1이 root이며 (0 아님!) 아래로 내려갈수록 2,3 -> 4,5,6,7 이렇게 피라미드가 되는 식
// leaf level max가 p개이면 그 parent는 p-1개 이니까 저렇게 해도 됨

template <typename T>
class RMQ{
public:
	RMQ(T* idata, int idatalen) {
		data.resize(idatalen);
		for(int i=0; i<idatalen; ++i) data[i] = idata[i];

		int rangemin_size = 1;
		while(rangemin_size < data.size())
			rangemin_size <<= 1;
		rangemin_size <<= 1;

		//printf("rangemin_size : %d\n", rangemin_size);

		rangemin.resize(rangemin_size,0);
		recursive_init(0, data.size()-1, 1);
	}
	T query(int left, int right){
		return recursive_query(left, right, 1, 0, data.size()-1);
	}
	T update(int idx, T val){
		T retval = recursive_update(idx, val, 1, 0, data.size()-1);
		data[idx] = val;
		return retval;
	}
	void print_data(){
		for(auto it=data.begin(); it != data.end(); ++it){
			printf("%d ", *it);
		}
		printf("\n");
	}
	void print_rangemin(){
		for(auto it=rangemin.begin(); it != rangemin.end(); ++it){
			printf("%d ", *it);
		}
		printf("\n");
	}
private:
	T recursive_init(int left, int right, int node){
		// printf("%d %d %d\n",left,right,node);
		if(left == right){
			rangemin[node] = data[left];
		}
		else{
			int mid = (left+right) >> 1;
			T leftmin = recursive_init(left,   mid,   node*2);
			T rightmin= recursive_init(mid+1, right, node*2+1);
			rangemin[node] = min(leftmin, rightmin);
		}
		return rangemin[node];
	}
	T recursive_query(int left, int right, int node, int nodeleft, int noderight){
		//printf("%d %d %d %d %d\n",left,right,node,nodeleft,noderight);
		if((right < nodeleft) || (noderight < left)){
			return numeric_limits<T>::max();
		}
		if((left <= nodeleft) && (noderight <= right)){
			return rangemin[node];
		}
		int mid = (nodeleft + noderight) >> 1;
		T leftmin  = recursive_query(left, right, node*2,   nodeleft, mid);
		T rightmin = recursive_query(left, right, node*2+1, mid+1, noderight);
		return min(leftmin, rightmin);
	}
	T recursive_update(int idx, T val, int node, int nodeleft, int noderight){
		if((idx < nodeleft) || (noderight < idx)){
			return rangemin[node];
		}
		if(nodeleft == noderight){
			rangemin[node] = val;
		}
		else{
			int mid = (nodeleft + noderight) >> 1;
			T leftmin = recursive_update(idx, val, node*2,   nodeleft, mid);
			T rightmin= recursive_update(idx, val, node*2+1, mid+1, noderight);
			rangemin[node] = min(leftmin, rightmin);
		}
		return rangemin[node];
	}
	vector<T> data;
	vector<T> rangemin;
};

int N,Q;
int PH[100000];
int NH[100000];

void get_input(){
	scanf("%d%d", &N, &Q);
	for(int i=0; i<N; ++i){
		scanf("%d", &PH[i]);
		NH[i] = -PH[i];
	}
}

void solve(){
	int a,b;
	RMQ<int> max_rmq(NH, N);
	RMQ<int> min_rmq(PH, N);

	for(int i=0; i<Q; ++i){
		scanf("%d%d",&a,&b);
		int maxh = -max_rmq.query(a,b);
		int minh = min_rmq.query(a,b);
		printf("%d\n",maxh-minh);
	}
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}