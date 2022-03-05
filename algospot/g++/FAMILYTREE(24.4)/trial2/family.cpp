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

int N,Q;
int P[100000];
vector<int> Child[100000];

vector<int> RMQDat;
int Lv[100000];
int IdxToOrigin[100000];
int OriginToIdx[100000];
int StartIdx[100000];

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

void print_arr(int* arr, int size){
	for(int i=0; i<N; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void print_vec(vector<int>& vec){
	for(int v:vec){
		printf("%d ", IdxToOrigin[v]);
	}
	printf("\n");
}

void get_input(){
	scanf("%d%d",&N,&Q);
	for(int i=0; i<N; ++i)
		Child[i].clear();
	for(int i=1; i<N; ++i)
		scanf("%d", &P[i]);
}

void rec_build_rmqdat(int cur){
	if(Child[cur].empty()){
		RMQDat.push_back(OriginToIdx[cur]);
	}
	else{
		for(int c:Child[cur]){
			rec_build_rmqdat(c);
			RMQDat.push_back(OriginToIdx[cur]);
		}
	}
}

void build_graph(){
	int idx = 0;
	int l = 0;
	queue<int> q1, q2;
	queue<int> *curq, *nxtq;

	curq = &q1;
	nxtq = &q2;

	for(int i=1; i<N; ++i)
		Child[P[i]].push_back(i);

	curq->push(0);
	while(true){
		while(!curq->empty()){
			int cur = curq->front(); curq->pop();
			// printf("%d %d\n",l,cur);
			Lv[cur] = l;
			OriginToIdx[cur] = idx;
			IdxToOrigin[idx] = cur;
			++idx;

			for(int c:Child[cur])
				nxtq->push(c);
		}

		if(nxtq->empty())
			break;

		++l;
		swap(curq,nxtq);
	}

	RMQDat.clear();
	rec_build_rmqdat(0);

	memset(StartIdx,0xFF,N*sizeof(int));

	for(int i=0; i<RMQDat.size(); ++i){
		int o = IdxToOrigin[RMQDat[i]];
		if(StartIdx[o] == -1){
			StartIdx[o] = i;
		}
	}
}

void solve(){
	int a,b;

	build_graph();

	// print_arr(Lv,N);
	// print_arr(OriginToIdx,N);
	// print_arr(IdxToOrigin,N);
	// print_vec(RMQDat);
	// print_arr(StartIdx,N);

	RMQ<int> rmq(&RMQDat[0], RMQDat.size());

	for(int i=0; i<Q; ++i){
		scanf("%d%d",&a,&b);

		int l = StartIdx[a];
		int r = StartIdx[b];

		if(l > r)
			swap(l,r);

		// printf("a:%d b:%d l:%d r:%d\n",a,b,l,r);

		int rmqres = rmq.query(l,r);

		// printf("rmqres : %d\n",rmqres);

		int c = IdxToOrigin[rmqres];

		int c_lv = Lv[c];
		int l_lv = Lv[a];
		int r_lv = Lv[b];

		printf("%d\n",(l_lv-c_lv)+(r_lv-c_lv));
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