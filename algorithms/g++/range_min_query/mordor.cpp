#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

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
			rangemin[node] = std::min(leftmin, rightmin);
		}
		return rangemin[node];
	}
	T recursive_query(int left, int right, int node, int nodeleft, int noderight){
		//printf("%d %d %d %d %d\n",left,right,node,nodeleft,noderight);
		if((right < nodeleft) || (noderight < left)){
			return std::numeric_limits<T>::max();
		}
		if((left <= nodeleft) && (noderight <= right)){
			return rangemin[node];
		}
		int mid = (nodeleft + noderight) >> 1;
		T leftmin  = recursive_query(left, right, node*2,   nodeleft, mid);
		T rightmin = recursive_query(left, right, node*2+1, mid+1, noderight);
		return std::min(leftmin, rightmin);
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
			rangemin[node] = std::min(leftmin, rightmin);
		}
		return rangemin[node];
	}
	std::vector<T> data;
	std::vector<T> rangemin;
};

int main(int argc, char** argv){
	int C, N, Q;
	int heights[100000];
	int heights_neg[100000];

	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d %d", &N, &Q);
		// printf("N:%d Q:%d\n",N,Q);
		for(int n=0; n<N; ++n){
			scanf("%d", &heights[n]);
		}
		for(int n=0; n<N; ++n){
			heights_neg[n] = -heights[n];
		}

		RMQ<int> rmq_min(heights, N);
		// rmq_min.print_data();
		RMQ<int> rmq_max(heights_neg, N);
		// rmq_max.print_data();

		int a, b;
		int min_range, max_range;

		for(int q=0; q<Q; ++q){
			scanf("%d %d", &a, &b);
			min_range =  rmq_min.query(a,b);
			max_range = -rmq_max.query(a,b);
			// printf("%d %d %d %d\n", a, b, min_range, max_range);
			printf("%d\n", max_range-min_range);
		}
	}
}